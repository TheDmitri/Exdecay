modded class PlayerBase
{
	protected ref LocalParticleVFX m_LocalParticleVFX;
	protected ref UndergroundVFX m_UndergroundVFX;

	override void Init()
	{	
		super.Init();

		if ( !GetGame().IsServer() || !GetGame().IsMultiplayer() )
		{
			m_LocalParticleVFX = new LocalParticleVFX( this );
			string worldName = "empty";
			GetGame().GetWorldName( worldName );
			worldName.ToLower();
			if ( worldName == "exdecay" )
			{
				m_UndergroundVFX = new UndergroundVFX( this );
			}
		}
	}

	override void OnPlayerLoaded()
	{
		super.OnPlayerLoaded();

		if ( m_Hud && IsControlledPlayer() )
		{
			PPEffects.SetEyeAccUnderground( 1.0 );
		}
	}

	override void CommandHandler(float pDt, int pCurrentCommandID, bool pCurrentCommandFinished)	
	{	
		super.CommandHandler( pDt, pCurrentCommandID, pCurrentCommandFinished );
	
		if ( GetInstanceType() == DayZPlayerInstanceType.INSTANCETYPE_CLIENT || !GetGame().IsMultiplayer() )
		{
			if ( m_LocalParticleVFX )
			{
				m_LocalParticleVFX.ParticleTimeUpdate( pDt );
			}
			if ( m_UndergroundVFX )
			{
				m_UndergroundVFX.UndergroundTimeUpdate( pDt );
			}
		}
	}
};
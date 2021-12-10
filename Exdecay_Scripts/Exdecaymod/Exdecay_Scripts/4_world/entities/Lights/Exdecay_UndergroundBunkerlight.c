class Land_Exdecay_UndergroundBunkerlight extends BuildingSuper
{
    Exdecay_UndergroundBunkerlightLight m_Light;
   
   
	override void EEInit()
	{
		super.EEInit();
		
		if ( !GetGame().IsMultiplayer() || GetGame().IsClient() )
		{
			// object creation - create effects (light, particles, sound)
			
			// light
			if ( !m_Light )
			{
				m_Light = Exdecay_UndergroundBunkerlightLight.Cast( ScriptedLightBase.CreateLight( Exdecay_UndergroundBunkerlightLight, Vector(0,0,0), 0.08 ) );
				m_Light.AttachOnMemoryPoint(this, "beamstart","beamend");
			}
			
		}
	}
	
	override void EEDelete( EntityAI parent )
	{
		super.EEDelete( parent );

		if ( !GetGame().IsMultiplayer() || GetGame().IsClient() )
		{
			// outside of bubble - do effects cleanup (light, particles, sound)
			
			// light
			if ( m_Light )
				m_Light.FadeOut();
			
		}
	}	
}

// this shit makes the game cosy as fuck boyssssss
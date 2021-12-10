class LocalParticleVFX
{

/*

	This class is responsible for managing local VFX around local player.
	It is called from CommandHandler method (instance being in PlayerBase).

  * nam_p_debris_meadows (nam_grass)
   * object based particle
   * grass/leaves debris flying low above the grass
   * frequency of appereance depends on the wind intensity

  * nam_p_debris_forest (nam_forest)
   * player based particle
   * pieces of branches flying against the player from higher position
   * frequency of appereance does not depend on wind intensity

  * nam_p_snowdust_fast (nam_seaice)
   * object based particle
   * bigger chunks of snow dust moving on flat land
   * frequency of appereance depends on the wind intensity

  * nam_p_snowdust_slow (nam_snow)
   * object based particle
   * small "devils" staying on one place
   * frequency of appereance depends on wind intensity

*/

	protected PlayerBase m_Player;
	protected vector m_PlayerPos;
	protected float m_PrimaryTimer;
	protected float m_ObjectBasedTimer;
	protected Weather m_Weather;
	protected float m_WindSpeed;
	protected const int M_CLOSEUPOBJCNT = 20;
	protected string m_ActiveSurface;
	protected bool m_PlayerBasedForest, m_PlayerBasedMeadows;
	protected float m_ObjectBasedWait;
	protected EntityAI m_ObjectBasedList[M_CLOSEUPOBJCNT];
	protected Particle m_PlayerBased;
	protected int m_ObjectBasedIndex;

	void LocalParticleVFX( PlayerBase pPlayer )
	{
		m_Player = pPlayer;
		m_Weather = GetGame().GetWeather();
		m_PlayerBasedForest = false;
		m_PlayerBasedMeadows = false;
		m_ObjectBasedIndex = 0;
		m_ObjectBasedWait = 0.0;
		m_PrimaryTimer = 0.0;
		m_ObjectBasedTimer = 0.0;
		m_WindSpeed = 1.0;
	}

	void ParticleTimeUpdate( float pDt )
	{
		m_PrimaryTimer += pDt;
		m_ObjectBasedTimer += pDt;
		ParticleUpdate();
	}

	private bool SlopeCheck( vector vfx_dir )
	{
		if ( ( ( vfx_dir[0] < 0.10 ) && ( vfx_dir[0] > -0.10 ) ) && ( ( vfx_dir[1] < 0.10 ) && ( vfx_dir[1] > -0.10 ) ) )
			return true;
		else
			return false;
	}

	private void ObjectBasedSpawn( string ClassToSpawn )
	{
		vector offset = Vector( Math.RandomFloat( -15.0, 15.0 ), 0.0, Math.RandomFloat( -15.0, 15.0 ) );
		m_ObjectBasedList[m_ObjectBasedIndex] = EntityAI.Cast(GetGame().CreateObjectEx(ClassToSpawn, m_PlayerPos + offset, ECE_LOCAL));
		float x = (m_PlayerPos + offset)[0];
		float z = (m_PlayerPos + offset)[2];
		vector transform[4];
		vector surface_normal = GetGame().SurfaceGetNormal(x, z);
		vector local_ori = m_ObjectBasedList[m_ObjectBasedIndex].GetDirection();

		m_ObjectBasedList[m_ObjectBasedIndex].GetTransform(transform);
		transform[0] = surface_normal * local_ori;
		transform[1] = surface_normal;
		transform[2] = surface_normal * (local_ori * vector.Up);
		transform[3][1] = GetGame().SurfaceY(transform[3][0], transform[3][2]);
		m_ObjectBasedList[m_ObjectBasedIndex].SetTransform(transform);
		m_ObjectBasedList[m_ObjectBasedIndex].Update();

		vector vfx_dir = m_ObjectBasedList[m_ObjectBasedIndex].GetDirection();
		if ( ( ( ClassToSpawn == "vfx_snowdust_fast" ) && SlopeCheck( vfx_dir ) ) || ( ClassToSpawn == "vfx_snowdust_slow" ) )
		{
			GenericVFX object_vfx = GenericVFX.Cast( m_ObjectBasedList[m_ObjectBasedIndex] );
			object_vfx.vfx_start();
		}
		m_ObjectBasedIndex++;
	}

	private void ObjectBasedCleanup()
	{
		for ( int i = 0; i < M_CLOSEUPOBJCNT; i++ )
		{
			if ( m_ObjectBasedList[i] != NULL )
				GetGame().ObjectDelete( m_ObjectBasedList[i] );
		}
	}

	private void ParticleUpdate()
	{
		if ( m_PrimaryTimer > 1.0 )
		{
			m_ActiveSurface = m_Player.GetSurfaceType();
			m_PlayerPos = m_Player.GetPosition();
			m_WindSpeed = Math.Max( m_Weather.GetWindSpeed(), 1 );
			m_PrimaryTimer = 0.0;
			m_ObjectBasedTimer = 0.0;

			if ( m_PlayerBasedForest && ( m_ActiveSurface != "nam_forest" ) )
			{
				m_PlayerBased.Stop();
				m_PlayerBasedForest = false;
			}
			if ( m_PlayerBasedMeadows && ( m_ActiveSurface != "nam_grass" ) )
			{
				m_PlayerBased.Stop();
				m_PlayerBasedMeadows = false;
			}
		}

		switch ( m_ActiveSurface )
		{
			case "nam_seaice":
			{
				m_ObjectBasedWait = ( Math.Max( ( 200.0 * 1.0 / m_WindSpeed ), 10.0 ) ) / 1000.0;

				// rapid spawning (with interval defined by m_ObjectBasedTimer and m_ObjectBasedWait)
				if ( ( m_ObjectBasedTimer > m_ObjectBasedWait ) && ( m_ObjectBasedIndex < M_CLOSEUPOBJCNT ) )
				{
					m_ObjectBasedTimer = 0.0;

					// altitude check (dont spawn it too close to the sea)
					if ( m_PlayerPos[1] > 1.5 )
					{
						ObjectBasedSpawn( "vfx_snowdust_fast" );
					}
				}
				// removal
				if ( m_ObjectBasedIndex >= M_CLOSEUPOBJCNT )
				{
					ObjectBasedCleanup();
					m_ObjectBasedIndex = 0;
				}
				break;
			}
			case "nam_snow":
			{
				m_ObjectBasedWait = ( Math.Max( ( 200.0 * 1.0 / m_WindSpeed ), 10.0 ) ) / 1000.0;

				// rapid spawning (with interval defined by m_ObjectBasedTimer and m_ObjectBasedWait)
				if ( ( m_ObjectBasedTimer > m_ObjectBasedWait ) && ( m_ObjectBasedIndex < M_CLOSEUPOBJCNT ) )
				{
					m_ObjectBasedTimer = 0.0;

					// altitude check (dont spawn it too close to the sea)
					if ( m_PlayerPos[1] > 1.5 )
					{
						ObjectBasedSpawn( "vfx_snowdust_slow" );
					}
				}
				// removal
				if ( m_ObjectBasedIndex >= M_CLOSEUPOBJCNT )
				{
					ObjectBasedCleanup();
					m_ObjectBasedIndex = 0;
				}
				break;
			}
			case "nam_forest":
			{
				if ( !m_PlayerBasedForest )
				{
					m_PlayerBasedForest = true;
					m_PlayerBased = Particle.PlayOnObject( ParticleList.NAM_P_DEBRIS_FOREST, m_Player, vector.Zero );
				}
				break;
			}
			case "nam_grass":
			{
				if ( !m_PlayerBasedMeadows )
				{
					m_PlayerBasedMeadows = true;
					m_PlayerBased = Particle.PlayOnObject( ParticleList.NAM_P_DEBRIS_MEADOWS, m_Player, vector.Zero );
				}
				break;
			}
			default: {
				break;
			}
		}
	}
}
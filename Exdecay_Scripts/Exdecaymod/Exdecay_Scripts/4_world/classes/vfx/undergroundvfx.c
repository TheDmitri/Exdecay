class UndergroundVFX
{
	private PlayerBase m_Player;
	private vector m_PlayerPos;
	private string m_PlayerPosSurface;
	private float m_PrimaryTimer;
	private float m_ExposureDt;
	private float m_ExposureDtTarget;
	private float m_ExposureDtTargetPrev;
	private float m_ExposureAcc;
	private float m_ExposureAccRange;
/* 	TVectorArray darkZones=
	{ 
		"5196.73 0 2122.63", "5175.68 0 2129",
		"5196.73 0 2122.63", "5175.68 0 2129"
	}; */



	void UndergroundVFX( PlayerBase pPlayer )
	{
		m_Player = pPlayer;
		m_PlayerPos = vector.Zero;
		m_PlayerPosSurface = "";
		m_PrimaryTimer = 0.0;
		m_ExposureDt = 1.0;
		m_ExposureDtTarget = 1.0;
		m_ExposureDtTargetPrev = 1.0;
		m_ExposureAcc = 25.0;
		m_ExposureAccRange = 1.0;
	}

	void ShowUndergroundDebugInfo( bool enabled )
	{
		int windowPosX = 10;
		int windowPosY = 100;

		Object obj;

		DbgUI.Begin( "Underground VFX", windowPosX, windowPosY );
		if ( enabled )
		{
			DbgUI.Text( "PlayerPos: " + m_PlayerPos.ToString() );
			DbgUI.Text( "PlayerPosSurf: " + m_PlayerPosSurface );
			DbgUI.Text( "ExposureDt: " + m_ExposureDt.ToString() + " (acc=" + (m_ExposureAccRange / m_ExposureAcc).ToString() + ", rng=" + m_ExposureAccRange.ToString() + ", tgt=" + m_ExposureDtTarget.ToString() + ")" );
		}
		DbgUI.End();
	}

	// this method is called from PlayerBase
	void UndergroundTimeUpdate( float pDt )
	{
		m_PrimaryTimer += pDt;
		UndergroundUpdate();
	}

	private void UndergroundUpdate()
	{
		UndergroundExposure();

		// do necessary checks every 1/3 of a second
		if ( m_PrimaryTimer > 0.33 )
		{
			m_PrimaryTimer = 0.0;
			m_PlayerPos = m_Player.GetPosition();
			m_PlayerPosSurface = m_Player.GetSurfaceType();
			UndergroundCheck();
			if ( m_ExposureDtTargetPrev != m_ExposureDtTarget )
			{
				m_ExposureAccRange = Math.AbsFloat( m_ExposureDtTarget - m_ExposureDtTargetPrev );
				m_ExposureDtTargetPrev = m_ExposureDtTarget;
			}
		}
	}

	private void UndergroundExposure()
	{
		if ( m_ExposureDt != m_ExposureDtTarget )
		{
			if ( m_ExposureDt > m_ExposureDtTarget )
			{
				m_ExposureDt = Math.Max( m_ExposureDtTarget, ( m_ExposureDt - ( m_ExposureAccRange / m_ExposureAcc ) ) );
				PPEffects.SetEyeAccUnderground( m_ExposureDt );
			}
			if ( m_ExposureDt < m_ExposureDtTarget )
			{
				m_ExposureDt = Math.Min( m_ExposureDtTarget, ( m_ExposureDt + ( m_ExposureAccRange / m_ExposureAcc ) ) );
				PPEffects.SetEyeAccUnderground( m_ExposureDt );
			}
		}
	}

	private void UndergroundCheck()
	//flatlands bunker lvl1
	{
		if ( ( ( m_PlayerPos[0] ) > 4669 ) && ( ( m_PlayerPos[0] ) < 4672 ) )
		{
			if ( ( ( m_PlayerPos[2] ) > 8009 ) && ( ( m_PlayerPos[2] ) < 8020 ) )
			{
				if ( ( m_PlayerPos[1] ) < 40 )
				{
					m_ExposureDtTarget = 0.1;
					return;
				}
			}
		}
		if ( ( ( m_PlayerPos[0] ) > 4511 ) && ( ( m_PlayerPos[0] ) < 5030 ) )
		{
			if ( ( ( m_PlayerPos[2] ) > 7955 ) && ( ( m_PlayerPos[2] ) < 8009) )
			{
				if ( ( m_PlayerPos[1] ) < 34 )
				{
					m_ExposureDtTarget = 0.0;
					return;
				}
			}
		}
		//BunkerSystem
		if ( ( ( m_PlayerPos[0] ) > 759 ) && ( ( m_PlayerPos[0] ) < 1205) )
		{
			if ( ( ( m_PlayerPos[2] ) > 19692) && ( ( m_PlayerPos[2] ) < 19925 ) )
			{
				if ( ( m_PlayerPos[1] ) < 65 )
				{
					m_ExposureDtTarget = 0.0;
					return;
				}
			}
		}
		m_ExposureDtTarget = 1.0;
		return;
	}
}
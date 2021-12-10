modded class PPEffects
{
	// COLORIZE IDs
	//static const int COLORIZE_DYNEVENT = 200;

	// EYEACC IDs
	static const int EYEACC_NV = 100;
	static const int EYEACC_UNDERGROUND = 200;

	// array for eyeacc effects
	static ref map<int, float> m_EyeAccEffects;

	static void Init()
	{
		//Print("---Init PPEffects---");
		if ( m_BlurValues )
		{
			delete m_BlurValues;
		}
		if ( m_ChromAbbValues )
		{
			delete m_ChromAbbValues;
		}
		if ( m_VignetteEffects )
		{
			delete m_VignetteEffects;
		}
		if ( m_VignetteValues )
		{
			delete m_VignetteValues;
		}
		if ( m_ColorEffect )
		{
			delete m_ColorEffect;
		}
		
		m_MatColors = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/glow");
		m_RadialBlur = GetGame().GetWorld().GetMaterial("graphics/materials/postprocess/radialblur");
		m_BlurValues = new array<float>;
		m_ChromAbbValues = new array<float>;
		m_VignetteEffects = new array<int>;
		m_VignetteValues = new map<int, ref array<float>>;
		
		// add new blur effects here
		m_BlurInventory		= RegisterBlurEffect();
		m_BlurDrunk			= RegisterBlurEffect();
		m_BlurFever			= RegisterBlurEffect();
		m_BlurMenu			= RegisterBlurEffect();
		m_BlurOptics 		= RegisterBlurEffect();
		m_BlurFlashbang		= RegisterBlurEffect();
		
		// add chromatic abberation effects here
		m_ChromAbbOptic 	= RegisterChromAbbEffect();
		//m_ChromAbbShock 	= RegisterChromAbbEffect();
		
		// add vignette effects here
		m_VignetteUnconscious 	= RegisterVignetteEffect();
		m_VignetteShock 		= RegisterVignetteEffect();
		m_VignetteTunnel 		= RegisterVignetteEffect();
		m_VignetteMenu 			= RegisterVignetteEffect();
		
		m_ColorEffect = new array<float>;
		m_ColorValues = new map<int, ref array<float>>;
		
		// add new color effects here
		m_BurlapBlindness 	= RegisterColorEffect();
		m_DyingEffect 		= RegisterColorEffect();
		m_ShockEffect 		= RegisterColorEffect();
		
		// ------------------------NV-related stuff below------------------------
		ref array<float> colorizeDefault = {0.0, 0.0, 0.0};
		m_ColorizeEffects = new map<int, ref array<float>>;
		
		// colorize: r, g, b
		// colorize effects registration
		m_ColorizeEffects.Set(PPEffects.COLORIZE_NV, colorizeDefault);
		SetNVParams(1.0, 0.0, 2.35, 2.75); //default values
		// ------------------------End of NV-related stuff------------------------


		// MODDED PART
		m_EyeAccEffects = new map<int, float>;

		// colorize: r, g, b
		// colorize effects registration
		//m_ColorizeEffects.Set( PPEffects.COLORIZE_DYNEVENT, colorizeDefault );

		// eyeacc: value
		// eyeacc effects registration
		m_EyeAccEffects.Set( PPEffects.EYEACC_NV, 1.0 );
		m_EyeAccEffects.Set( PPEffects.EYEACC_UNDERGROUND, 1.0 );
	}
	
	// appropriate parts of the code will call these functions
	/*static void SetColorizationDynEvent( float r, float g, float b )
	{
		ref array<float> colorizeArray = { r, g, b };
		m_ColorizeEffects.Set( PPEffects.COLORIZE_DYNEVENT, colorizeArray );
		UpdateColorize();
	}*/

	// appropriate parts of the code will call these functions
	static void SetEyeAccNV( float value )
	{
		m_EyeAccEffects.Set( PPEffects.EYEACC_NV, value );
		UpdateEyeAcc();
	}
	static void SetEyeAccUnderground( float value )
	{
		m_EyeAccEffects.Set( PPEffects.EYEACC_UNDERGROUND, value );
		UpdateEyeAcc();
	}
	static void UpdateEyeAcc()
	{
		bool foundActiveEffect = false;
		int lowestKey = 1000000;
		float chosenValue = 1.0;
		// search for active effect with highest priority (lower value of key better)
		for ( int i = 0; i < m_EyeAccEffects.Count(); i++ )
		{
			int currentKey = m_EyeAccEffects.GetKey( i );
			float eyeAccValue = m_EyeAccEffects.Get( currentKey );
			// check for active effect
			if ( eyeAccValue != 1.0 )
			{
				if ( currentKey < lowestKey )
				{
					chosenValue = eyeAccValue;
					lowestKey = currentKey;
					foundActiveEffect = true;
				}
				
			}
		}
		if ( foundActiveEffect )
		{
			// active effect found
			GetGame().GetWorld().SetEyeAccom( chosenValue );
		} else {
			// no active event found, reset effect to default
			ResetEyeAcc();
		}
	}
	static void ResetEyeAcc()
	{
		GetGame().GetWorld().SetEyeAccom( 1.0 );
	}

	static void ResetAll()
	{
		// ORIGINAL PART OF RESETALL (super cannot be called)
		ResetBlurEffects();
		ResetColorEffects();
		ResetVignettes();
		ResetPPMask();
		ResetDOFOverride();
		ResetLensEffect();
		SetBloodSaturation( 1 );
		//RemoveUnconsciousnessVignette();
		ResetColorize();

		// modded
		ResetEyeAcc();
	}
};
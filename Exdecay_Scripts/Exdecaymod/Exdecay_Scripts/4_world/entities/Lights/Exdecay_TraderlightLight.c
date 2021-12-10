class Exdecay_TraderlightLight extends SpotLightBase
{
	private static float m_DefaultRadius = 30; // 30 default
	private static float m_DefaultBrightness = 7; // 6 default
	private static float m_DefaultAngle = 160; // 120 default

	void Exdecay_TraderlightLight()
	{
		SetVisibleDuringDaylight(false);
		SetRadiusTo(m_DefaultRadius);
		SetSpotLightAngle(m_DefaultAngle);
		SetCastShadow(false);
		EnableSpecular(true);
		//SetFlickerAmplitude(0.85); //If greater than 1, it will make the light disappear randomly. 
		//SetFlickerSpeed(1.25); // Fuck knows.
		SetBrightnessTo(m_DefaultBrightness);
		SetFlareVisible(false);
		SetFadeOutTime(0.5);
		SetAmbientColor(1.0, 0.7, 0.4); //Standard orange fluroesant light
		SetDiffuseColor(1.0, 0.7, 0.4);
	}
	
	void SetIntensity( float coef, float time )
	{
		FadeBrightnessTo(m_DefaultBrightness * coef, time);
	}
}
class Land_ExDecay_Streetlight extends BuildingSuper
{
    ExDecay_StreetlightLight m_Light;
    
    
    static int        REFLECTOR_ID = 1;
    static int        GLASS_ID = 0;
    
    static string     LIGHT_OFF_GLASS     = "DZ\\weapons\\attachments\\optics\\data\\lensglass_clearer.rvmat"; // Make sure you have the "\\" instead of "\" when calling the rvmats for the materials.
    static string     LIGHT_OFF_REFLECTOR = "ExdecayMod\\Exdecay_models\\Lamps\\Data\\ExDecay_Streetlight.rvmat";
    static string     LIGHT_ON_GLASS      = "DZ\\gear\\tools\\data\\flashlight_glass_on.rvmat";
    static string     LIGHT_ON_REFLECTOR  = "ExdecayMod\\Exdecay_models\\Lamps\\Data\\ExDecay_Streetlight_on.rvmat";


	void Land_ExDecay_Streetlight()
	{
        if ( !GetGame().IsServer()  ||  !GetGame().IsMultiplayer() ) // Client side
        {
                GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(SetLight, 10000, true);
        }		
	}
   

    void SetLight()
    {
        if (g_Game.GetWorld().GetSunOrMoon() < 1 && m_Light == NULL)
        {
            TurnOn();
        }
        if (g_Game.GetWorld().GetSunOrMoon() >= 1)
            TurnOff();
        
    }
    
    void TurnOn()
    {
            m_Light = ExDecay_StreetlightLight.Cast(ScriptedLightBase.CreateLight(ExDecay_StreetlightLight, "0 0 0", 0.08)  ); // Position is zero because light is attached on parent immediately.
            m_Light.AttachOnMemoryPoint(this, "beamstart","beamend");
            SetObjectMaterial(GLASS_ID, LIGHT_ON_GLASS);
            SetObjectMaterial(REFLECTOR_ID, LIGHT_ON_REFLECTOR);
    }
    void TurnOff()
    {
        if (m_Light)
            m_Light.FadeOut();
		SetObjectMaterial(GLASS_ID, LIGHT_OFF_GLASS);
        SetObjectMaterial(REFLECTOR_ID, LIGHT_OFF_REFLECTOR);
    }
    override void EEDelete( EntityAI parent )
    {
        if ( !GetGame().IsServer()  ||  !GetGame().IsMultiplayer() ) // Client side
        {
            if (m_Light)
                m_Light.FadeOut();
            
            m_Light = NULL;            
        }
        
    }
}

// this shit makes the game cosy as fuck boyssssss
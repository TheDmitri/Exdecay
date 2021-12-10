class Land_Exdecay_Traderlight extends BuildingSuper
{
    Exdecay_TraderlightLight m_Light;
    
    
    static int        REFLECTOR_ID = 0;
    
 // Make sure you have the "\\" instead of "\" when calling the rvmats for the materials.
    static string     LIGHT_OFF_REFLECTOR = "ExdecayMod\\Exdecay_models\\Lamps\\Data\\Exdecay_Traderlight.rvmat";
    static string     LIGHT_ON_REFLECTOR  = "ExdecayMod\\Exdecay_models\\Lamps\\Data\\Exdecay_Traderlight_on.rvmat";


	void Land_Exdecay_Traderlight()
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
            m_Light = Exdecay_TraderlightLight.Cast(ScriptedLightBase.CreateLight(Exdecay_TraderlightLight, "0 0 0", 0.08)  ); // Position is zero because light is attached on parent immediately.
            m_Light.AttachOnMemoryPoint(this, "beamStart","beamEnd");
            SetObjectMaterial(REFLECTOR_ID, LIGHT_ON_REFLECTOR);
    }
    void TurnOff()
    {
        if (m_Light)
            m_Light.FadeOut();
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
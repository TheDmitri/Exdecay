modded class DayZPlayerCameraBase
{
	override void SetNVPostprocess(int NVtype)
	{
		//Print("+++Setting NV type: " + NVtype + " +++");
		switch (NVtype)
		{
			case NVTypes.NONE:
				//PPEffects.SetEVValuePP(0);
				PPEffects.SetEyeAccNV(1);
				PPEffects.SetColorizationNV(1.0, 1.0, 1.0);
				PPEffects.SetNVParams(1.0, 0.0, 2.35, 2.75); //default values
			break;
			
			case NVTypes.NV_OPTICS_ON:
				//PPEffects.SetEVValuePP(7);
				PPEffects.SetEyeAccNV(7);
				PPEffects.SetColorizationNV(0.0, 1.0, 0.0);
				PPEffects.SetNVParams(3.0, 2.0, 9.0, 1.0);
			break;
			
			case NVTypes.NV_OPTICS_OFF:
				//PPEffects.SetEVValuePP(-7);
				PPEffects.SetEyeAccNV(-1);
				PPEffects.SetColorizationNV(0.0, 0.0, 0.0);
				PPEffects.SetNVParams(1.0, 0.0, 2.35, 2.75); //default values
			break;
			
			case NVTypes.NV_GOGGLES:
				//PPEffects.SetEVValuePP(7);
				PPEffects.SetEyeAccNV(7);
				PPEffects.SetColorizationNV(0.0, 1.0, 0.0);
				PPEffects.SetNVParams(2.0, 1.0, 10.0, 1.0);
			break;
		}

		if (PlayerBaseClient.Cast(m_pPlayer))
		{
			PlayerBaseClient.Cast(m_pPlayer).SwitchPersonalLight(NVtype < 1); //TODO 
		}
	}

	override void OnActivate(DayZPlayerCamera pPrevCamera, DayZPlayerCameraResult pPrevCameraResult)
	{
		//PrintString("OnActivate DayZPlayerCameraBase");
		PlayerBase player = PlayerBase.Cast(m_pPlayer);
		player.OnCameraChanged(this);
		SetCameraPPDelay(pPrevCamera);
		
		if (DayZPlayerCameraBase.Cast(pPrevCamera) && DayZPlayerCameraBase.Cast(pPrevCamera).IsCameraNV())
		{
			//PPEffects.SetNVValueEV(0); //sets EV value immediately to avoid bright flashes at night

			// modded
			PPEffects.SetEyeAccNV(1.0);
		}
		
		GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(SetCameraPP,m_CameraPPDelay*1000,false,true,this); // this takes care of weapon/optics postprocessing
		DayZPlayerCameraOptics optic_camera;
		if (DayZPlayerCamera.CastTo(optic_camera,pPrevCamera))
		{
			GetGame().GetCallQueue(CALL_CATEGORY_GUI).Call(PlayerBase.Cast(m_pPlayer).HideClothing,null,false);
		}
	}
}
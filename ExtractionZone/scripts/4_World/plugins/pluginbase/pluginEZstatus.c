class PluginEZStatus : PluginBase
{
	void CloseEZUI()
  {
		Mission mission = GetGame().GetMission();
		if (mission)
		{
			Hud hud = mission.GetHud();
			if (hud)
			{
    		hud.CloseEZUI();
			}
		}
  }

  void DisplayExtractionStatus(int i, bool show)
  {
		Mission mission = GetGame().GetMission();
		if (mission)
		{
			Hud hud = mission.GetHud();
			if (hud)
			{
    		hud.DisplayExtractionStatus(i, show);
			}
		}
  }
};

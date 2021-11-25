modded class IngameHud
{
  ref ExtractionUI m_ExtractionUI = NULL;

	override void Init(Widget hud_panel_widget)
	{
		super.Init(hud_panel_widget);
		m_ExtractionUI = new ExtractionUI(hud_panel_widget);
	}

  void CloseEZUI()
  {
    m_ExtractionUI.CloseUI();
  }

  void DisplayExtractionStatus(int i, bool show)
  {
    m_ExtractionUI.DisplayExtractionStatus(i,show);
  }
};

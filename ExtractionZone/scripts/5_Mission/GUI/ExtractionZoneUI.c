class ExtractionUI extends UIScriptedMenu
{
  private Widget m_EZlayoutRoot;
  private ImageWidget m_ExtractionLogo;
  private TextWidget m_EZText;

  private int m_countdown;
  private int m_startcountdown;

  void ExtractionUI(Widget parent)
  {
		m_EZlayoutRoot   = GetGame().GetWorkspace().CreateWidgets("ExtractionZone/gui/EZUI.layout",parent);
	  m_EZText         = TextWidget.Cast( m_EZlayoutRoot.FindAnyWidget("EZText") );
    m_ExtractionLogo = ImageWidget.Cast(m_EZlayoutRoot.FindAnyWidget("ExtractionLogo"));
    m_EZlayoutRoot.Show(false);
  }

  void ~ExtractionUI()
  {
    GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(CountdownUpdate);
    GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(Close);
  }

  void CloseUI()
  {
    m_EZlayoutRoot.Show(false);
    GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(CountdownUpdate);
    GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(Close);
  }

  void DisplayExtractionStatus(int i, bool show)
  {
    m_EZlayoutRoot.Show(show);
    m_countdown = i;
    m_startcountdown = i;
    m_EZText.SetText(m_countdown.ToString());
    GetGame().GetCallQueue (CALL_CATEGORY_GUI).CallLater(CountdownUpdate, 1000, true);
  }

  void CountdownUpdate()
  {
    m_countdown--;
    m_EZText.SetText(m_countdown.ToString());
    if(m_countdown == 0)
    {
      m_countdown = m_startcountdown;
      GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(CountdownUpdate);
    }
  }
};

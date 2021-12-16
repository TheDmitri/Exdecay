class ExdecayTeleporterMenu extends UIScriptedMenu
{
  private   GridSpacerWidget  m_MapsGrid;
  private   Widget            m_MapPanel;
  private   Widget            m_MapWrapper;
  private   Widget            m_ConfirmationPanel;
  private   ButtonWidget      m_BttnYes;
  private   ButtonWidget      m_BttnNo;
  private   ButtonWidget      m_CloseBttn;
  private   ButtonWidget      m_SpawnButton;
  private   RichTextWidget    m_MapDescription;
  private   TextListboxWidget m_SpawnPointList;
  private   ImageWidget       m_Population;
  private   int               selectedRow;
  private   int               selectedMap;
  private   int               position;
  private   float             UIUpdate=0.0;

  private   ref TIntArray         m_NumberPlayerPerMap;
  private   ref TIntArray         m_Countdowns;

  private ref map<Widget, int>	m_WidgetMapsList;


  void ExdecayTeleporterMenu()
  {
    selectedRow = -1;
    selectedMap = -1;
    m_NumberPlayerPerMap = new TIntArray;
    m_Countdowns = new TIntArray;
    m_WidgetMapsList = new map<Widget, int>();
    GetGame().GetCallQueue(CALL_CATEGORY_GUI).CallLater(UpdateRequest, 60000, true);
  }

  override Widget Init()
    {
		    layoutRoot = GetGame().GetWorkspace().CreateWidgets( "ExdecayTeleporter/gui/ExdecayTeleporter.layout" );
        m_MapsGrid = GridSpacerWidget.Cast( layoutRoot.FindAnyWidget( "MapsGrid" ) );
        m_MapPanel = Widget.Cast( layoutRoot.FindAnyWidget( "MapPanel" ) );
        m_MapDescription = RichTextWidget.Cast( layoutRoot.FindAnyWidget( "MapDescription" ) );
        m_MapWrapper = Widget.Cast( layoutRoot.FindAnyWidget( "MapWrapper" ) );
        m_CloseBttn = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "CloseBttn" ) );
        m_SpawnButton = ButtonWidget.Cast( layoutRoot.FindAnyWidget( "SpawnButton" ) );
        m_SpawnPointList = TextListboxWidget.Cast(layoutRoot.FindAnyWidget( "SpawnPointList" ));
        m_ConfirmationPanel = Widget.Cast( layoutRoot.FindAnyWidget( "ConfirmationPanel" ) );
        m_BttnYes= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "BttnYes" ) );
        m_BttnNo= ButtonWidget.Cast( layoutRoot.FindAnyWidget( "BttnNo" ) );
        m_ConfirmationPanel.Show(false);
        layoutRoot.Show(false);
        m_MapsGrid.Show(true);
        m_MapPanel.Show(false);
        return layoutRoot;
    }

  void UIHandle()
  {
	   initMaps();
  }

  void UpdateRequest()
  {
    GetRPCManager().SendRPC("ExdecayTeleporter", "GetExdecayTeleporterMenuRequest",  NULL, true, NULL);
  }

  void initMaps()
  {
    m_MapsGrid.Show(true);
    m_MapPanel.Show(false);
    DestroyAllChildren(m_MapsGrid);
    m_WidgetMapsList.Clear();
    for(int i=0;i<4;i++)
    {
      Widget widget;
      ImageWidget population;
      ImageWidget landImage;
      widget = GetGame().GetWorkspace().CreateWidgets( "ExdecayTeleporter/gui/ExdecayTeleporterCard.layout", m_MapsGrid);
      if (!widget) return;
      landImage = ImageWidget.Cast( widget.FindAnyWidget( "LandImage" ) );
      population = ImageWidget.Cast( widget.FindAnyWidget( "Population" ) );
      landImage.LoadImageFile(0, GetClientMaps().Get(i).ImagePath);
      string populationImagePath = GetPopulationImagePathBasedOnPlayerPopulation(m_NumberPlayerPerMap[i],GetClientMaps().Get(i).MaxPlayer);
      population.LoadImageFile(0, populationImagePath);
      m_WidgetMapsList.Insert(widget, i);
    }
  }

  string GetPopulationImagePathBasedOnPlayerPopulation(int currentPopulation, int maxPopulation)
	{
		float coefficient = (currentPopulation*1.0)/(maxPopulation*1.0);

		if(coefficient == 1.0)
		{
			return "ExdecayTeleporter/gui/full.edds";
		}
		else if(coefficient < 1.0 && coefficient > 0.70)
		{
			return "ExdecayTeleporter/gui/high.edds";
		}
		else if(coefficient < 0.70 && coefficient > 0.40)
		{
			return "ExdecayTeleporter/gui/medium.edds";
		}
		else(coefficient < 0.40)
		{
			return "ExdecayTeleporter/gui/low.edds";
		}

		return "ExdecayTeleporter/gui/low.edds";
	}

  void SetDataPerMap(TIntArray numberPlayerPerMap, TIntArray countdowns)
  {
    m_NumberPlayerPerMap.Clear();
    m_Countdowns.Clear();
    m_NumberPlayerPerMap = numberPlayerPerMap;
    m_Countdowns = countdowns;
  }

  void DestroyAllChildren(Widget w)
	{
		while(w.GetChildren())
		{
			w.RemoveChild(w.GetChildren());
		}
	}

  void initSelectedMapPanel()
  {
    if(GetClientMaps().Get(selectedMap).IsDisable)
      return;

    m_MapsGrid.Show(false);
    m_MapPanel.Show(true);

    Widget widget;
    ImageWidget population;
    ImageWidget landImage;

    DestroyAllChildren(m_MapWrapper);
    widget = GetGame().GetWorkspace().CreateWidgets( "ExdecayTeleporter/gui/ExdecayTeleporterCard.layout", m_MapWrapper);
    if (!widget) return;
    landImage = ImageWidget.Cast( widget.FindAnyWidget( "LandImage" ) );
    population = ImageWidget.Cast( widget.FindAnyWidget( "Population" ) );
    landImage.LoadImageFile(0, GetClientMaps().Get(selectedMap).ImagePath);
    string populationImagePath = GetPopulationImagePathBasedOnPlayerPopulation(m_NumberPlayerPerMap[selectedMap],GetClientMaps().Get(selectedMap).MaxPlayer);
    population.LoadImageFile(0, populationImagePath);

    m_MapDescription.SetText(GetClientMaps().Get(selectedMap).MapDescription);

    if(GetClientMaps().Get(selectedMap).IsFreshySpawn)
        m_SpawnPointList.Show(false);

    m_SpawnPointList.ClearItems();
    for(int i=0; i<GetClientMaps().Get(selectedMap).Positions.Count();i++)
    {
      m_SpawnPointList.AddItem(GetClientMaps().Get(selectedMap).Positions.Get(i).PointName, NULL, 0);
    }
  }

  override bool OnClick (Widget w, int x, int y, int button)
  {
    if(w.GetUserID() == 18011998)
    {
      int i,j;
      if(m_WidgetMapsList.Find(w.GetParent(),i))
      {
        selectedMap = i;
        PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
        if(player) player.PlayExdecayTeleporterSound(1);
        initSelectedMapPanel();
        return true;
      }
      else
      {
        selectedMap = -1;
      }
      return true;
    }

    switch(w)
    {
      case m_CloseBttn: CloseBttnHandler();
      return true;
      break;

      case m_SpawnPointList: SpawnPointListHandler();
      return true;
      break;

      case m_SpawnButton: SpawnButtonHandler();
      return true;
      break;

      case m_BttnYes: YesButtonHandler();
      return true;
      break;

      case m_BttnNo: OnHide();
      return true;
      break;
    }
    return false;
  }

  void YesButtonHandler()
  {
    int interval = GetETPTimeStamp() - m_Countdowns[selectedMap];
    int countdown= GetClientMaps().Get(selectedMap).Countdown * 60;
    int timeleft = countdown - interval;
    if( interval < countdown)
    {
      GetRPCManager().SendRPC("ExdecayTeleporter", "GetExdecayTeleporterMsgRequest",  new Param1<int>(timeleft), true, NULL);
      OnHide();
      return;
    }

    PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
    if(player) player.PlayExdecayTeleporterSound(2);
    GetRPCManager().SendRPC("ExdecayTeleporter", "GetExdecayTeleporterRequest",  new Param3<string,vector, bool>(GetClientMaps().Get(selectedMap).MapName,GetClientMaps().Get(selectedMap).Positions.GetRandomElement().PointPosition, true), true, NULL);
    OnHide();
  }

  void CloseBttnHandler()
  {
    m_MapsGrid.Show(true);
    m_MapPanel.Show(false);
  }

  void SpawnPointListHandler()
  {
    selectedRow = m_SpawnPointList.GetSelectedRow();
    if(selectedRow == -1)return;
  }

  override void Update(float timeslice)
	{
		super.Update(timeslice);

		if (UIUpdate >= 0.1)
		{
      SpawnPointListHandler();
			UIUpdate = 0;
		}
		else
		{
			UIUpdate = UIUpdate + timeslice;
		}
	}

  void SpawnButtonHandler()
  {
    if(GetClientMaps().Get(selectedMap).IsFreshySpawn)
    {
      m_MapsGrid.Show(false);
      m_MapPanel.Show(false);
      m_ConfirmationPanel.Show(true);
      return;
    }

    if(selectedRow == -1)
      return;

    int interval = GetETPTimeStamp() - m_Countdowns[selectedMap];
    int countdown= GetClientMaps().Get(selectedMap).Countdown * 60;
    int timeleft = countdown - interval;
    if( interval < countdown)
    {
      GetRPCManager().SendRPC("ExdecayTeleporter", "GetExdecayTeleporterMsgRequest",  new Param1<int>(timeleft), true, NULL);
      OnHide();
      return;
    }

    PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());
    if(player) player.PlayExdecayTeleporterSound(2);
    GetRPCManager().SendRPC("ExdecayTeleporter", "GetExdecayTeleporterRequest",  new Param3<string,vector,bool>(GetClientMaps().Get(selectedMap).MapName,GetClientMaps().Get(selectedMap).Positions.Get(selectedRow).PointPosition, false), true, NULL);
    OnHide();
  }

  override void OnHide()
	{
		super.OnHide();
		PPEffects.SetBlurMenu(0);
		GetGame().GetInput().ResetGameFocus();
    GetGame().GetUIManager().ShowUICursor(false);
    GetGame().GetMission().GetHud().Show(true);
    GetGame().GetCallQueue(CALL_CATEGORY_GUI).Remove(UpdateRequest);
		Close();
	}

	override void OnShow()
	{
		super.OnShow();
		PPEffects.SetBlurMenu(0.5);
		GetGame().GetInput().ChangeGameFocus(1);
    GetGame().GetUIManager().ShowUICursor(true);
    GetGame().GetMission().GetHud().Show(false);
		SetFocus(layoutRoot);
    UIHandle();
	}
};

class EZExtractionZoneClient
{
  bool						EZStatut = false;
	string          EZName="";
  bool            HasStarted = false;

  ref ExtractionLocations m_ExtractionLocations;

  private PluginEZStatus m_EZModuleEZStatus;

  private ref array<ref Particle> m_MovingParticles;

	void EZExtractionZoneClient()
  {
      m_EZModuleEZStatus = PluginEZStatus.Cast(GetPlugin(PluginEZStatus));
      m_MovingParticles = new array<ref Particle>;

      #ifdef EZDEBUG
			GetEZLogger().LogInfo("EZExtractionZoneClient started!");
			#endif
  }

  void ~EZExtractionZoneClient(){
  }


  void StartEZCheck()
  {
      #ifdef EZDEBUG
      GetEZLogger().LogInfo("StartEZCheck");
      #endif
      HasStarted = true;
      StartParticlesEffect();
      GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(ExtractionZoneCheck, 2000, true);
  }

  void StartParticlesEffect()
  {
    for(int i = 0; i<m_ExtractionLocations.Positions.Count();i++)
    {
      if(!m_ExtractionLocations.EnableParticles[i])continue;
      vector position = m_ExtractionLocations.Positions.Get(i);
      position = snapToGround(position);
      Particle m_MovingParticle = Particle.PlayInWorld(GetParticleChoice(m_ExtractionLocations.ParticleNames[i]),position);
      m_MovingParticles.Insert(m_MovingParticle);
    }
  }

  int GetParticleChoice(string choice)
  {
    switch(choice)
    {
      case "Green":return ParticleList.GRENADE_M18_GREEN_LOOP;
      break;

      case "Purple":return ParticleList.GRENADE_M18_PURPLE_LOOP;
      break;

      case "White":return ParticleList.GRENADE_RDG2_WHITE_LOOP;
      break;

      case "Red":return ParticleList.GRENADE_M18_RED_LOOP;
      break;

      case "Yellow":return ParticleList.GRENADE_M18_YELLOW_LOOP;
      break;

      case "Black":return ParticleList.GRENADE_RDG2_BLACK_LOOP;
      break;

      default:return ParticleList.GRENADE_M18_GREEN_LOOP;
      break;
    }

    return ParticleList.GRENADE_M18_GREEN_LOOP;
  }

  private vector snapToGround(vector pos)
    {
        float pos_x = pos[0];
        float pos_z = pos[2];
        float pos_y = GetGame().SurfaceY( pos_x, pos_z );
        vector tmp_pos = Vector( pos_x, pos_y, pos_z );
        tmp_pos[1] = tmp_pos[1] + pos[1];

        return tmp_pos;
    }

  private void ExtractionZoneCheck()
	{
      PlayerBase m_player = PlayerBase.Cast(GetGame().GetPlayer());
      if(m_player)
      {
          if( m_ExtractionLocations )
          {
          	for(int i = 0 ; i<m_ExtractionLocations.Positions.Count() ; i++)
          	{
          			ExtractionZoneRound(m_player,m_player.GetPosition(),i);
          	}
          }
      }
      else
      {
          EZStatut = false;
          EZName = "";
          m_ExtractionLocations = NULL;
      }
	}

  void ExtractionZoneRound(PlayerBase m_player , vector pos, int i)
  {
    vector center = m_ExtractionLocations.Positions.Get(i);
    center[1]=0;
    pos[1]=0;
    float dist = vector.Distance(center, pos);
    if ( dist <= m_ExtractionLocations.Radius.Get(i) )
		{
      if (EZName!=m_ExtractionLocations.ZoneNames.Get(i) && !EZStatut) //Already in zone
			{
        EZName=m_ExtractionLocations.ZoneNames.Get(i);
        EZStatut=true;
        if(m_ExtractionLocations.IsNotificationMsgActive)
        {
          NotificationSystem.AddNotificationExtended( 1.5, m_ExtractionLocations.ZoneNames.Get(i), m_ExtractionLocations.MsgOnEnterExtraction, "ExtractionZone/images/EZlogo.paa" );
        }
        DisplayExtractionStatus(m_ExtractionLocations.Countdowns.Get(i),m_ExtractionLocations.DisableUIs[i]);
        GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(SendExtractionTeleporationRequest, 1000*m_ExtractionLocations.Countdowns.Get(i), false, i);
      }
    }
    else
			{
        if (EZName==m_ExtractionLocations.ZoneNames.Get(i) && EZStatut)
				{
          EZName="";
          EZStatut=false;
          CloseEZUI();
          GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).Remove(SendExtractionTeleporationRequest);
          if(m_ExtractionLocations.IsNotificationMsgActive)
          {
            NotificationSystem.AddNotificationExtended( 1.5, m_ExtractionLocations.ZoneNames.Get(i), m_ExtractionLocations.MsgOnLeaveExtraction, "ExtractionZone/images/EZlogo.paa" );
          }
        }
			}
  }

    void GetEZConfigResponse(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
    {
        if (!GetGame().IsClient())
            return;
        Param1<ref ExtractionLocations> data;
        if (!ctx.Read(data))
            return;
        m_ExtractionLocations = data.param1;

        #ifdef EZDEBUG
        GetEZLogger().LogInfo("GetEZConfigResponse");
        #endif

        //JsonFileLoader<ExtractionLocations>.JsonSaveFile(EZ_CONFIG, m_ExtractionLocations);
        if(!HasStarted)
        StartEZCheck();
    }

    void SendExtractionTeleporationRequest(int i)
    {
      #ifdef EZDEBUG
      GetEZLogger().LogInfo("SendExtractionZoneStatut");
      #endif

      GetRPCManager().SendRPC("EZExtractionZone", "GetTPRequest",  new Param1<vector>(m_ExtractionLocations.Destinations.Get(i)), true, NULL);
    }

    //-----------------Helpers function to deal with the EZ icon in the ingamehug-----------------------//
    void CloseEZUI()
    {
      if(m_EZModuleEZStatus)
      {
        m_EZModuleEZStatus.CloseEZUI();
      }
    }

    void DisplayExtractionStatus(int i, bool show)
    {
      if(m_EZModuleEZStatus)
      {
        m_EZModuleEZStatus.DisplayExtractionStatus(i, show);
      }
    }
    //-------------------------------------------------------------------------------------------------//
};

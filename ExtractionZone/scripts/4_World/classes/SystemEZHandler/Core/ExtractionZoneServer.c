class EZExtractionZoneServer
{
  ref ExtractionLocations m_ExtractionLocations;

  void EZExtractionZoneServer()
  {
      GetEZLogger().LogInfo("EZExtractionZoneServer - Started");
      GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(InitEZExtractionZoneServer, 1000);
  }

  void InitEZExtractionZoneServer()
  {
    //We convert our ExtractionZone config so we can send it to client
    m_ExtractionLocations = new ExtractionLocations;
    m_ExtractionLocations.InitExtractionLocations(GetEZConfig());
  }

  void  ~EZExtractionZoneServer()
  {

  }

  void SendEZConfigToClient(PlayerIdentity sender)
  {
      if(m_ExtractionLocations)
      {
          #ifdef EZDEBUG
    			GetEZLogger().LogInfo("GetEZConfigResponse server to client");
    			#endif
          GetRPCManager().SendRPC("EZExtractionZone", "GetEZConfigResponse", new Param1<ref ExtractionLocations>(m_ExtractionLocations), true, sender);
      }
  }

  void TeleportationHandler(PlayerBase player, vector destination)
  {
      destination = snapToGround(destination);
      player.SetPosition(destination);
      thread SetExtractingStatus(player);
  }

  void SetExtractingStatus(PlayerBase player)
  {
    Sleep(10000);
    if(player)
    {
      player.IsExtracting = false;
    }
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

  //-----------------------------------RPC called on server-------------------------------------//
  void GetTPRequest(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
  {
   if (!GetGame().IsServer())
     return;

    Param1<vector> data;
     if (!ctx.Read(data))
       return;
     PlayerBase player = EZGetPlayerByIdentity(sender);
     vector destination = data.param1;

     if(player.IsUnconscious() || !player.IsAlive())return;

     player.IsExtracting = true;
     TeleportationHandler(player, destination);

     #ifdef EZDEBUG
     GetEZLogger().LogInfo("[EZStatut] : PlayerName:"+ sender.GetName());
     #endif
  }
  //---------------------------------------------------------------------------------------------------------//
};

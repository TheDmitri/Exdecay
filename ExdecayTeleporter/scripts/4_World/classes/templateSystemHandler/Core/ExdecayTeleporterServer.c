class ExdecayTeleporterServer
{
  int lastTimeStamp = 0;

  ref TIntArray numberOfPlayersPerMap;

  void ExdecayTeleporterServer()
  {
    numberOfPlayersPerMap = new TIntArray;
    GetETPLogger().LogInfo("ExdecayTeleporterServer - Started");

    //I usually make a small delay to make sure that my static config class is available
    GetGame().GetCallQueue(CALL_CATEGORY_SYSTEM).CallLater(initExdecayTeleporterServer, 500);
  }

  void initExdecayTeleporterServer()
  {
    /*Do your code here*/
    SetNPCSpawner();
  }

  void SetNPCSpawner()
  {
    array<ref StaticObjectNPC>NPCs = GetExdecayTeleporterConfig().NPCs;
    for(int i = 0;i<NPCs.Count();i++)
    {
      string objetName = NPCs.Get(i).Classname;
      Object obj = GetGame().CreateObject(objetName, vector.Zero, false, false);
      if (!obj) return;
      GetETPLogger().LogInfo("obj created: "+objetName);

      PlayerBase npcPlayer = PlayerBase.Cast(obj);
      if (npcPlayer)
      {
        GetETPLogger().LogInfo("Npc created and added!: ");
        npcPlayer.SetupExdecayTeleporterNPC(NPCs.Get(i));
        continue;
      }

      BuildingBase npcBuilding = BuildingBase.Cast(obj);
      if (npcBuilding)
      {
        GetETPLogger().LogInfo("TraderStatic created and added!: ");
        npcBuilding.SetupExdecayTeleporterNPC(NPCs.Get(i));
      }else GetETPLogger().LogInfo("TraderStatic was NOT created ! Make sure your static object extends BuildingBase as the documentation tells you!");
    }
  }

  void  ~ExdecayTeleporterServer()
  {

  }

  //check every 5min if the number of player per map when someone tries to access the teleporter menu
  void CheckAndGetNumberOfPlayerPerMap(PlayerIdentity sender)
  {
    int currentTimeStamp = GetETPTimeStamp();
    if(lastTimeStamp == 0 || currentTimeStamp - lastTimeStamp > 300)
    {
      #ifdef ETPDEBUG
      GetETPLogger().LogInfo("CheckAndGetNumberOfPlayerPerMap start count"); //sender.GetName() = player.GetIdentity().GetName()
      #endif
      numberOfPlayersPerMap.Clear();
      for(int i=0;i<GetExdecayTeleporterConfig().Maps.Count();i++)
        numberOfPlayersPerMap.Insert(0);

      lastTimeStamp = currentTimeStamp;
      array<Man> m_Players = new array<Man>;
      GetGame().GetPlayers(m_Players);
      foreach(PlayerBase player: m_Players)
      {
        vector pos = player.GetPosition();
        for(int j=0;j<GetExdecayTeleporterConfig().Maps.Count();j++)
        {
          ExdecayMap exMap = GetExdecayTeleporterConfig().Maps[j];
          if ( pos[0] > exMap.X1 && pos[0] < exMap.X2 && pos[2] > exMap.Y1 && pos[2] < exMap.Y2 )
          {
            numberOfPlayersPerMap[j]=numberOfPlayersPerMap[j]+1;
            #ifdef ETPDEBUG
            GetETPLogger().LogInfo("count map:"+j + " count:"+numberOfPlayersPerMap[j]); //sender.GetName() = player.GetIdentity().GetName()
            #endif
          }
        }
      }
    }

    string steamID = sender.GetPlainId();
    ExdecayTeleporterData data = ExdecayTeleporterData.Load(sender.GetName(), steamID);
    TIntArray countdowns = new TIntArray;
    if(data)
    {
      int currentTime = GetETPTimeStamp();
      for(int k=0;k<GetExdecayTeleporterConfig().Maps.Count();k++)
      {
          if(data.Maps.Contains(GetExdecayTeleporterConfig().Maps[k].MapName))
          {
            countdowns.Insert(data.Maps.Get(GetExdecayTeleporterConfig().Maps[k].MapName));
          }
          else
          {
            countdowns.Insert(0);
          }
      }
    }
    GetRPCManager().SendRPC("ExdecayTeleporter", "GetExdecayTeleporterMenuResponse",  new Param2<ref TIntArray,ref TIntArray>(numberOfPlayersPerMap,countdowns), true, sender);
  }

  void TeleporterRequest(PlayerBase player, PlayerIdentity sender, string mapName, vector position)
  {
    string steamID = sender.GetPlainId();
    ExdecayTeleporterData data = ExdecayTeleporterData.Load(sender.GetName(), steamID);
    if(data)
    {
      int currentTime = GetETPTimeStamp();
      if(data.Maps.Contains(mapName))
      {
          int interval = currentTime - data.Maps.Get(mapName);
          int countdown = ExdecayTeleporterHelper.GetCountdownByMapName(mapName)*60;
          #ifdef ETPDEBUG
          GetETPLogger().LogInfo("TeleporterRequest interval:"+interval + " countdown:"+countdown); //sender.GetName() = player.GetIdentity().GetName()
          #endif
          if( interval > countdown)
          {
            int mapIndex = ExdecayTeleporterHelper.GetMapArrayPositionByMapName(mapName);
            if(mapIndex != -1)
            {
              if(numberOfPlayersPerMap[mapIndex] < GetExdecayTeleporterConfig().Maps[mapIndex].MaxPlayer)
              {
                numberOfPlayersPerMap[mapIndex] = numberOfPlayersPerMap[mapIndex] + 1;
                player.SetPosition(snapToGround(position));
                data.Maps.Set(mapName, currentTime);
                data.Save(steamID);
                return;
              }
              NotificationSystem.SendNotificationToPlayerIdentityExtended(sender, 3, "Exdecay Teleporter", GetExdecayTeleporterConfig().MaxPlayerReachedMsg, "ExdecayTeleporter/images/teleport.paa");
              return;
            }
          }
          int timeleft = countdown - interval;
          NotificationSystem.SendNotificationToPlayerIdentityExtended(sender, 3, "Exdecay Teleporter", GetExdecayTeleporterConfig().CountdownMsg + timeleft + "s", "ExdecayTeleporter/images/teleport.paa");
        }
        else
        {
          data.Maps.Set(mapName, currentTime);
          data.Save(steamID);
        }
      }
  }

  vector snapToGround(vector pos)
   {
  		 if(pos[1]>0)return pos;
  		 float pos_x = pos[0];
  		 float pos_z = pos[2];
  		 float pos_y = GetGame().SurfaceY( pos_x, pos_z );
  		 vector tmp_pos = Vector( pos_x, pos_y, pos_z );
  		 tmp_pos[1] = tmp_pos[1] + pos[1];

  		 return tmp_pos;
   }

  //-------------------------------------------RPC PART--------------------------------------------------------//
  void GetExdecayTeleporterMenuRequest(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
  {
   if (!GetGame().IsServer())
     return;

     PlayerBase player = ETPGetPlayerByIdentity(sender);

     CheckAndGetNumberOfPlayerPerMap(sender);

     #ifdef ETPDEBUG
     GetETPLogger().LogInfo("GetExdecayTeleporterMenuRequest by player:"+sender.GetName()); //sender.GetName() = player.GetIdentity().GetName()
     #endif
  }

  void GetExdecayTeleporterRequest(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
  {
   if (!GetGame().IsServer())
     return;

   Param2<string, vector> data;
      if (!ctx.Read(data))
        return;

     PlayerBase player = ETPGetPlayerByIdentity(sender);
     TeleporterRequest(player, sender, data.param1, data.param2);

     #ifdef ETPDEBUG
     GetETPLogger().LogInfo("GetExdecayTeleporterMenuRequest by player:"+sender.GetName()); //sender.GetName() = player.GetIdentity().GetName()
     #endif
  }

  void GetExdecayTeleporterMsgRequest(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
  {
   if (!GetGame().IsServer())
     return;

   Param1<int> data;
      if (!ctx.Read(data))
        return;

     NotificationSystem.SendNotificationToPlayerIdentityExtended(sender, 3, "Exdecay Teleporter", GetExdecayTeleporterConfig().CountdownMsg + data.param1 + "s", "ExdecayTeleporter/images/teleport.paa");

     #ifdef ETPDEBUG
     GetETPLogger().LogInfo("GetExdecayTeleporterMsgRequest by player:"+sender.GetName()); //sender.GetName() = player.GetIdentity().GetName()
     #endif
  }
  //---------------------------------------------------------------------------------------------------------//
};

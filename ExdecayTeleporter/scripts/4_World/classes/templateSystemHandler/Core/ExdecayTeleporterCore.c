class ExdecayTeleporterCore
{
	ref ExdecayTeleporterSettings m_ExdecayTeleporterSettings;

  ref ExdecayTeleporterServer m_ExdecayTeleporterServer;

	ref array<ref ExdecayMap> m_Maps;

	ref ExdecayTeleporterMenu m_TeleporterMenu;

	void ExdecayTeleporterCore()
  {
		GetETPLogger().LogInfo("ExdecayTeleporterCore - Started !");
		#ifdef ETPDEBUG
		GetETPLogger().LogInfo("DEBUG MODE ENABLED");
		#endif

		/*We load every config, class that will run on server side here*/
		if (GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			//LOADING CONFIG FILES...
			m_ExdecayTeleporterSettings = ExdecayTeleporterSettings.Load();

			//Creating server side part
			if(m_ExdecayTeleporterSettings.IsTeleporterActive)
				m_ExdecayTeleporterServer = new ExdecayTeleporterServer;
		}
		else
		{
			m_Maps = new array<ref ExdecayMap>;
		}
		//we call our function that will initiaze our NPC
		InitRPC();
  }

	void ~ExdecayTeleporterCore(){
  }

	void InitRPC()
		{
			if (GetGame().IsServer())
			{
				//Server calls
				//GetRPCManager().AddRPC("ModName (try to be as specific as you can)", "NameOfYourRPCFunction", function where the RPC will be called, SingeplayerExecutionType.Client (Client when you do client to server));
				GetRPCManager().AddRPC("ExdecayTeleporter", "GetExdecayTeleporterMenuRequest", m_ExdecayTeleporterServer, SingeplayerExecutionType.Client);
				GetRPCManager().AddRPC("ExdecayTeleporter", "GetExdecayTeleporterRequest", m_ExdecayTeleporterServer, SingeplayerExecutionType.Client);
				GetRPCManager().AddRPC("ExdecayTeleporter", "GetExdecayTeleporterMsgRequest", m_ExdecayTeleporterServer, SingeplayerExecutionType.Client);
			}
			else
			{
				//Client calls
				//GetRPCManager().AddRPC("ModName (try to be as specific as you can)", "NameOfYourRPCFunction", function where the RPC will be called, SingeplayerExecutionType.Server (Server when you do Server to Client));
				GetRPCManager().AddRPC("ExdecayTeleporter", "GetExdecayTeleporterMenuResponse", this, SingeplayerExecutionType.Server);
				GetRPCManager().AddRPC("ExdecayTeleporter", "GetExdecayTeleporterClientConfig", this, SingeplayerExecutionType.Server);
			}
		}


		void TransfertExdecayTeleporterConfigToClient(PlayerIdentity sender = NULL)
		{
				for(int i=0; i<m_ExdecayTeleporterSettings.Maps.Count();i++)
				{
					if(i==0)
					{
						GetRPCManager().SendRPC("ExdecayTeleporter", "GetExdecayTeleporterClientConfig",  new Param2<bool, ref ExdecayMap>(true, m_ExdecayTeleporterSettings.Maps[i]), true, sender);
						continue;
					}
					GetRPCManager().SendRPC("ExdecayTeleporter", "GetExdecayTeleporterClientConfig",  new Param2<bool, ref ExdecayMap>(false,m_ExdecayTeleporterSettings.Maps[i]), true, sender);
				}

		}

		/*RPC Function called on client*/
		void GetExdecayTeleporterClientConfig(CallType type, ParamsReadContext ctx,  PlayerIdentity sender,  Object target)
		{
			if(!GetGame().IsClient())return;

			Param2<bool, ref ExdecayMap> data;
	     if (!ctx.Read(data))
	       return;

			if(data.param1)
				m_Maps.Clear();

			m_Maps.Insert(data.param2);

			Print("GetExdecayTeleporterClientConfig count:" + m_Maps.Count() );
		}

		void GetExdecayTeleporterMenuResponse(CallType type, ParamsReadContext ctx,  PlayerIdentity sender,  Object target)
		{
			if(!GetGame().IsClient())return;

			Param2<ref TIntArray,ref TIntArray> data;
			 if (!ctx.Read(data))
				 return;

			if(m_TeleporterMenu)
			{
				m_TeleporterMenu.SetDataPerMap(data.param1, data.param2);
				m_TeleporterMenu.UIHandle();
			}

			if ( g_Game.GetUIManager().GetMenu() == NULL )
		 	{
		 			m_TeleporterMenu = new ExdecayTeleporterMenu;
		 			m_TeleporterMenu.Init();
					m_TeleporterMenu.SetDataPerMap(data.param1, data.param2);
		 			GetGame().GetUIManager().ShowScriptedMenu( m_TeleporterMenu, NULL );
		 	}
		}
	};

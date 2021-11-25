class EZExtractionZoneCore
{
	ref ExtractionAreaSettings m_ActiveExtractionAreaSettings;
	ref ExtractionLocations m_ExtractionLocations;

  ref EZExtractionZoneClient m_EZExtractionZoneClient;
  ref EZExtractionZoneServer m_EZExtractionZoneServer;

	void EZExtractionZoneCore()
  {
		GetEZLogger().LogInfo("EZExtractionZoneCore - Started ! => Loading config...");
		#ifdef EZDEBUG
		GetEZLogger().LogInfo("DEBUG MODE ENABLED");
		#endif
		if (GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			//LOADING CONFIG FILES...
			m_ActiveExtractionAreaSettings = ExtractionAreaSettings.Load();

			//Creating server side part of ExtractionZone
			if(m_ActiveExtractionAreaSettings.IsExtractionZoneActive)
			{
				m_EZExtractionZoneServer = new EZExtractionZoneServer;
			}
		}
		else
		{
			m_EZExtractionZoneClient = new EZExtractionZoneClient;
		}
		InitRPC();
  }

	void ~EZExtractionZoneCore(){
  }

	void InitRPC()
		{
			if (GetGame().IsServer())	{
				//Server calls
				GetRPCManager().AddRPC("EZExtractionZone", "GetTPRequest", m_EZExtractionZoneServer, SingeplayerExecutionType.Client);
			}
			else	{
				//Client calls
				GetRPCManager().AddRPC("EZExtractionZone", "GetEZConfigResponse", m_EZExtractionZoneClient, SingeplayerExecutionType.Server);
			}
		}

		//----------------------------------RPC PART---------------------------------------------------//
};

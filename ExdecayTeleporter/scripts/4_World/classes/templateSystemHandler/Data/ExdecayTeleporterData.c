class ExdecayMapCountdown
{
  string MapName;
  int    Time;

  void ExdecayMapCountdown(string name, int time)
  {
    MapName = name;
    Time = time;
  }
}

class ExdecayTeleporterData
{
	//Define your configs variables there
  string PlayerName;
	ref TStringIntMap Maps;

	void ExdecayTeleporterData()
	{
    Maps = new TStringIntMap;
	}

  void DefaultConfig(string name, string id)
  {
    PlayerName = name;
    for(int i=0;i<GetExdecayTeleporterConfig().Maps.Count();i++)
    {
      Maps.Set(GetExdecayTeleporterConfig().Maps[i].MapName,GetExdecayTeleporterConfig().Maps[i].Countdown);
    }
    Save(id);
  }

	void Save(string id)
	{
		string path = ETP_DATA_CONFIG + id + ".json";
		JsonFileLoader<ExdecayTeleporterData>.JsonSaveFile(path, this);
	}

	static ref ExdecayTeleporterData Load(string name, string id)	{
		ExdecayTeleporterData Data = new ExdecayTeleporterData();

		//we check if config folders exist, if not we create them
		if ( !FileExist( ETP_DB_DIR_SERVER ) )
		{
			MakeDirectory( ETP_DB_DIR_SERVER );
		}

		string path = ETP_DATA_CONFIG + id + ".json";
		//Now we check if config exist, if yes, we load it. if no, we call function defaultExdecayTeleporterData that will initialize default value
		if (FileExist(path)) {
			//Print("file exist ! loading...");
			#ifdef ETPDEBUG
			GetETPLogger().LogInfo("ExdecayTeleporterData file exist ! loading..."); //sender.GetName() = player.GetIdentity().GetName()
			#endif
			//TraderPlusJsonLoader<ExdecayTeleporterData>.LoadFromFile(path, Data);
			JsonFileLoader<ExdecayTeleporterData>.JsonLoadFile(path, Data);
			Data.Save(id);
		}
		else {
			//Print("file doesn't exist ! creating...");
			#ifdef ETPDEBUG
			GetETPLogger().LogInfo("ExdecayTeleporterData doesn't exist ! creating..."); //sender.GetName() = player.GetIdentity().GetName()
			#endif
			Data.DefaultConfig(name, id);
		}
		return Data;
	}
}

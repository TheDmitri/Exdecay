class ExdecayTeleporterSettings
{
	/*Define your configs variables there*/
	bool IsTeleporterActive;
	ref  array<ref ExdecayMap>Maps;
	ref array<ref StaticObjectNPC>NPCs;
	string CountdownMsg = "You can't teleport that soon to this map! You need to wait:";
	string MaxPlayerReachedMsg = "This max reached its player's capacity ! Come back later !";

	void ExdecayTeleporterSettings()
	{
		/*initiaze your arrays here*/
		Maps = new array<ref ExdecayMap>;
		NPCs = new array<ref StaticObjectNPC>;
	}

	void DefaultExdecayTeleporterSettings()
	{
		/*initialize default value of your config file if not generated*/
		IsTeleporterActive=true;
		Maps.Insert(new ExdecayMap("IceLand", false, 10, 30, "ExdecayTeleporter/gui/ICELAND.edds","This is a description frame to talk about your map features", 10722, 11866, 15241, 15100));
		Maps[0].AddPosition("SPAWNPOINT ALPHA",Vector(13195,0,13332));
		Maps[0].AddPosition("SPAWNPOINT BETA",Vector(13024,0,13414));
		Maps[0].AddPosition("SPAWNPOINT GAMMA",Vector(12138,0,13943));
		Maps.Insert(new ExdecayMap("ForestLand", false, 20, 30, "ExdecayTeleporter/gui/forestland.edds","This is a description frame to talk about your map features", 59, 1444,3411, 4461));
		Maps[1].AddPosition("SPAWNPOINT ALPHA",Vector(952,0,2577));
		Maps[1].AddPosition("SPAWNPOINT BETA",Vector(1615,0,3213));
		Maps[1].AddPosition("SPAWNPOINT GAMMA",Vector(1937,0,2612));
		Maps.Insert(new ExdecayMap("FarmLand", false, 20, 30, "ExdecayTeleporter/gui/farmland.edds","This is a description frame to talk about your map features", 471, 7697,7137, 11096));
		Maps[2].AddPosition("SPAWNPOINT ALPHA",Vector(2027,0,9369));
		Maps[2].AddPosition("SPAWNPOINT BETA",Vector(3131,0,9960));
		Maps[2].AddPosition("SPAWNPOINT GAMMA",Vector(1253,0,9939));
		Maps.Insert(new ExdecayMap("CityLand", false, 20, 30, "ExdecayTeleporter/gui/cityland.edds","This is a description frame to talk about your map features", 7500, 7500,8500, 8500));
		Maps[3].AddPosition("SPAWNPOINT ALPHA",Vector(2027,0,9369));
		Maps[3].AddPosition("SPAWNPOINT BETA",Vector(3131,0,9960));
		Maps[3].AddPosition("SPAWNPOINT GAMMA",Vector(1253,0,9939));
		NPCs.Insert(new StaticObjectNPC("TraderPlusSign",Vector(11622.5048828125,  58.740455627441409,  14678.955078125), Vector(54, 0,			0)));
		//then it saves the file
		JsonFileLoader<ExdecayTeleporterSettings>.JsonSaveFile(ETP_CONFIG, this);
	}

	static ref ExdecayTeleporterSettings Load()	{
		ExdecayTeleporterSettings settings = new ExdecayTeleporterSettings();


		//we check if config folders exist, if not we create them
		if ( !FileExist( ETP_CONFIG_ROOT_SERVER ) )
		{
			MakeDirectory( ETP_CONFIG_ROOT_SERVER );
			if ( !FileExist( ETP_CONFIG_DIR_SERVER ) )
			{
				MakeDirectory( ETP_CONFIG_DIR_SERVER );
			}
			if ( !FileExist( ETP_LOGGER_DIR_SERVER ) )
			{
				MakeDirectory( ETP_LOGGER_DIR_SERVER );
			}
		}

		//Now we check if config exist, if yes, we load it. if no, we call function defaultExdecayTeleportersettings that will initialize default value
		if (FileExist(ETP_CONFIG)) {
			//Print("file exist ! loading...");
			JsonFileLoader<ExdecayTeleporterSettings>.JsonLoadFile(ETP_CONFIG, settings);
		}
		else {
			//Print("file doesn't exist ! creating...");
			settings.DefaultExdecayTeleporterSettings();
		}

		return settings;
	}
}

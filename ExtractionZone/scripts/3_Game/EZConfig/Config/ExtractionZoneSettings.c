class ExtractionAreaSettings
{
	bool			IsExtractionZoneActive;
	bool      IsNotificationMsgActive;
	string    MsgOnEnterExtraction;
	string    MsgOnLeaveExtraction;
	ref array<ref ExtractionZoneLocation> ExtractionAreaLocation;

	void ExtractionAreaSettings() {
		ExtractionAreaLocation = new array<ref ExtractionZoneLocation>;
	}

	void ExtractionAreaDefaultSettings()
	{
		IsExtractionZoneActive = true;
		IsNotificationMsgActive= false;
		MsgOnEnterExtraction = "You are inside an extraction point !";
		MsgOnLeaveExtraction = "You left the extraction point!";
		ExtractionAreaLocation.Insert(new ExtractionZoneLocation("BerezinoToNovod",Vector(12948,0,10172),Vector(11586,0,14698),5, 1.0,30, true,false, "Green"));
		ExtractionAreaLocation.Insert(new ExtractionZoneLocation("SvetloToSevero",Vector(13828,0,13239),Vector(7736,0,12649),5, 1.0,1, true,true, "Green"));
		JsonFileLoader<ExtractionAreaSettings>.JsonSaveFile(EZ_CONFIG, this);
	}

	static ref ExtractionAreaSettings Load()	{
		ExtractionAreaSettings settings = new ExtractionAreaSettings();

		if ( !FileExist( EZ_CONFIG_ROOT_SERVER ) )
		{
			MakeDirectory( EZ_CONFIG_ROOT_SERVER );
			if ( !FileExist( EZ_CONFIG_DIR_SERVER ) )
			{
				MakeDirectory( EZ_CONFIG_DIR_SERVER );
			}
			if ( !FileExist( EZ_LOGGER_DIR_SERVER ) )
			{
				MakeDirectory( EZ_LOGGER_DIR_SERVER );
			}
		}

		if (FileExist(EZ_CONFIG)) {
			JsonFileLoader<ExtractionAreaSettings>.JsonLoadFile(EZ_CONFIG, settings);
		}
		else {
			settings.ExtractionAreaDefaultSettings();
		}

		return settings;
	}
};

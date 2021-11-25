class RandomPresets
{
	string randomPresetName;
	ref array<ref GlobalLootItems>globalLootItems;

	void RandomPresets(string tRandomPresetName)
	{
		randomPresetName = tRandomPresetName;
		globalLootItems = new array<ref GlobalLootItems>;
	}
}

class RandomPresetsSettings
{
	ref array<ref RandomPresets>RPresets;

	void RandomPresetsSettings() {
		RPresets = new array<ref RandomPresets>;
	}

	void RandomPresetsDefaultSettings()	{
		RPresets.Insert(new RandomPresets("Foodspawn"));
		RPresets[0].globalLootItems.Insert(new GlobalLootItems("Apple",0.03,-2));
		RPresets[0].globalLootItems.Insert(new GlobalLootItems("Pear",0.03,-2));
		RPresets[0].globalLootItems.Insert(new GlobalLootItems("Plum",0.03,-2));
		RPresets.Insert(new RandomPresets("MiscCommon"));
		RPresets[1].globalLootItems.Insert(new GlobalLootItems("AntiPestsSpray",0.02,-2));
		RPresets[1].globalLootItems.Insert(new GlobalLootItems("Battery9V",0.02,-2));
		RPresets[1].globalLootItems.Insert(new GlobalLootItems("BatteryCharger",0.02,-2));
		RPresets.Insert(new RandomPresets("Medical"));
		RPresets[2].globalLootItems.Insert(new GlobalLootItems("BandageDressing",0.04,-2));
		RPresets[2].globalLootItems.Insert(new GlobalLootItems("BloodBagEmpty",0.04,-2));
		RPresets[2].globalLootItems.Insert(new GlobalLootItems("BloodBagIV",0.04,-2));
		GLSJsonLoader<RandomPresetsSettings>.SaveToFile(GLS_RANDOMPRESETS_CONFIG, this);
	}

	void ConvertToMap(out map<string, ref array<ref GlobalLootItems>>randomsPresets)
	{
		foreach(RandomPresets rPresets: RPresets)
		{
			randomsPresets.Insert(rPresets.randomPresetName, new array<ref GlobalLootItems>);
			randomsPresets.Set(rPresets.randomPresetName, rPresets.globalLootItems);
		}
	}

	static ref RandomPresetsSettings Load()	{
		RandomPresetsSettings settings = new RandomPresetsSettings();

		if ( !FileExist( GLS_CONFIG_ROOT_SERVER ) )
		{
			MakeDirectory( GLS_CONFIG_ROOT_SERVER );
			if ( !FileExist( GLS_CONFIG_DIR_SERVER ) )
			{
				MakeDirectory( GLS_CONFIG_DIR_SERVER );
			}
			if ( !FileExist( GLS_LOGGER_DIR_SERVER ) )
			{
				MakeDirectory( GLS_LOGGER_DIR_SERVER );
			}
		}

		if (FileExist(GLS_RANDOMPRESETS_CONFIG)) {
			GLSJsonLoader<RandomPresetsSettings>.LoadFromFile(GLS_RANDOMPRESETS_CONFIG, settings);
			//JsonFileLoader<RandomPresetsSettings>.JsonLoadFile(GLS_RANDOMPRESETS_CONFIG, settings);
		}
		else {
			settings.RandomPresetsDefaultSettings();
		}

		return settings;
	}
};

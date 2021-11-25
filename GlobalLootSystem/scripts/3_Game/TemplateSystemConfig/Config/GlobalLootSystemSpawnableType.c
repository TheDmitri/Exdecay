class RandomPreset
{
	float chance;
	string randomPresetName;

	void RandomPreset(float tChance = 0.0 , string tRandomPresetName="")
	{
		chance = tChance;
		randomPresetName = tRandomPresetName;
	}
}

class SpawnableTypes
{
	string type;
	ref array<ref RandomPreset>randomsPresets;

	void SpawnableTypes(string tType)
	{
		type = tType;
		randomsPresets = new array<ref RandomPreset>;
	}
}

class SpawnableTypesSettings
{
	bool 					IsGlobalLootSystemWorking = true;
	ref array<ref SpawnableTypes>Types;

	void SpawnableTypesSettings() {
		Types = new array<ref SpawnableTypes>;
	}

	void SpawnableTypesDefaultSettings()	{
		Types.Insert(new SpawnableTypes("SeaChest"));
		Types[0].randomsPresets.Insert(new RandomPreset(1.0,"Foodspawn"));
		Types.Insert(new SpawnableTypes("Ex_Crate_square"));
		Types[1].randomsPresets.Insert(new RandomPreset(0.55,"Foodspawn"));
		Types.Insert(new SpawnableTypes("Ex_Crate_small"));
		Types[2].randomsPresets.Insert(new RandomPreset(0.40,"MiscCommon"));
		Types[2].randomsPresets.Insert(new RandomPreset(0.35,"Foodspawn"));
		Types.Insert(new SpawnableTypes("Ex_Crate_long"));
		Types[3].randomsPresets.Insert(new RandomPreset(0.35,"MiscCommon"));
		Types[3].randomsPresets.Insert(new RandomPreset(0.40,"Medical"));
		Types[3].randomsPresets.Insert(new RandomPreset(0.25,"Foodspawn"));
		GLSJsonLoader<SpawnableTypesSettings>.SaveToFile(GLS_SPAWNABLETYPES_CONFIG, this);
	}

	void ConvertToMap(out map<string, ref array<ref RandomPreset>>types)
	{
		foreach(SpawnableTypes sType: Types)
		{
			types.Insert(sType.type, new array<ref RandomPreset>);
			types.Set(sType.type, sType.randomsPresets);
		}
	}

	static ref SpawnableTypesSettings Load()	{
		SpawnableTypesSettings settings = new SpawnableTypesSettings();

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

		if (FileExist(GLS_SPAWNABLETYPES_CONFIG)) {
			GLSJsonLoader<SpawnableTypesSettings>.LoadFromFile(GLS_SPAWNABLETYPES_CONFIG, settings);
			//JsonFileLoader<SpawnableTypesSettings>.JsonLoadFile(GLS_SPAWNABLETYPES_CONFIG, settings);
		}
		else {
			settings.SpawnableTypesDefaultSettings();
		}

		return settings;
	}
};

class RPAttachmentsSettings
{
	ref array<ref RandomPresets>Attachments;

	void RPAttachmentsSettings() {
		Attachments = new array<ref RandomPresets>;
	}

	void RPAttachmentsDefaultSettings()	{
		Attachments.Insert(new RandomPresets("AKM"));
		Attachments[0].globalLootItems.Insert(new GlobalLootItems("Mag_AKM_30Rnd",0.03,-2));
		Attachments[0].globalLootItems.Insert(new GlobalLootItems("PSO1Optic",0.03,-2));
		Attachments[0].globalLootItems.Insert(new GlobalLootItems("Mag_AKM_Drum75Rnd",0.03,-2));
		Attachments[0].globalLootItems.Insert(new GlobalLootItems("AK_Suppressor",0.03,-2));
		Attachments[0].globalLootItems.Insert(new GlobalLootItems("AK_PlasticHndgrd",0.03,-2));
		Attachments[0].globalLootItems.Insert(new GlobalLootItems("AK_RailHndgrd_Black",0.03,-2));
		Attachments[0].globalLootItems.Insert(new GlobalLootItems("AK_Bayonet",0.03,-2));
		Attachments[0].globalLootItems.Insert(new GlobalLootItems("AK_FoldingBttstck_Black",0.03,-2));
		Attachments.Insert(new RandomPresets("M4A1"));
		Attachments[1].globalLootItems.Insert(new GlobalLootItems("Mag_STANAG_30Rnd",0.02,-2));
		Attachments[1].globalLootItems.Insert(new GlobalLootItems("Mag_STANAGCoupled_30Rnd",0.02,-2));
		Attachments[1].globalLootItems.Insert(new GlobalLootItems("ACOGOptic",0.02,-2));
		Attachments[1].globalLootItems.Insert(new GlobalLootItems("M4_CarryHandleOptic",0.02,-2));
		Attachments[1].globalLootItems.Insert(new GlobalLootItems("M4_CQBBttstck",0.02,-2));
		Attachments[1].globalLootItems.Insert(new GlobalLootItems("M4_MPBttstck",0.02,-2));
		Attachments[1].globalLootItems.Insert(new GlobalLootItems("M4_MPHndgrd",0.02,-2));
		Attachments[1].globalLootItems.Insert(new GlobalLootItems("M4_RISHndgrd",0.02,-2));
		Attachments[1].globalLootItems.Insert(new GlobalLootItems("M4_Suppressor",0.02,-2));
		Attachments.Insert(new RandomPresets("SVD"));
		Attachments[2].globalLootItems.Insert(new GlobalLootItems("PSO1Optic",0.04,-2));
		Attachments[2].globalLootItems.Insert(new GlobalLootItems("Mag_SVD_10Rnd",0.04,-2));
		Attachments.Insert(new RandomPresets("AK74"));
		Attachments[3].globalLootItems.Insert(new GlobalLootItems("AK_RailHndgrd_Black",0.04,-2));
		Attachments[3].globalLootItems.Insert(new GlobalLootItems("AK74_WoodBttstck",0.04,-2));
		Attachments[3].globalLootItems.Insert(new GlobalLootItems("AK_Bayonet",0.04,-2));
		Attachments[3].globalLootItems.Insert(new GlobalLootItems("AK_FoldingBttstck_Black",0.04,-2));
		Attachments[3].globalLootItems.Insert(new GlobalLootItems("AK_Suppressor",0.04,-2));
		Attachments[3].globalLootItems.Insert(new GlobalLootItems("Mag_AK74_30Rnd",0.04,-2));
		Attachments.Insert(new RandomPresets("FAL"));
		Attachments[4].globalLootItems.Insert(new GlobalLootItems("Fal_FoldingBttstck",0.04,-2));
		Attachments[4].globalLootItems.Insert(new GlobalLootItems("Fal_OeBttstck",0.04,-2));
		Attachments[4].globalLootItems.Insert(new GlobalLootItems("Mag_FAL_20Rnd",0.04,-2));
		Attachments[4].globalLootItems.Insert(new GlobalLootItems("ACOGOptic",0.04,-2));
		GLSJsonLoader<RPAttachmentsSettings>.SaveToFile(GLS_ATTACHMENTS_CONFIG, this);
	}

	void ConvertToMap(out map<string, ref array<ref GlobalLootItems>>randomsPresets)
	{
		foreach(RandomPresets Attachments: Attachments)
		{
			randomsPresets.Insert(Attachments.randomPresetName, new array<ref GlobalLootItems>);
			randomsPresets.Set(Attachments.randomPresetName, Attachments.globalLootItems);
		}
	}

	static ref RPAttachmentsSettings Load()	{
		RPAttachmentsSettings settings = new RPAttachmentsSettings();

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

		if (FileExist(GLS_ATTACHMENTS_CONFIG)) {
			GLSJsonLoader<RPAttachmentsSettings>.LoadFromFile(GLS_ATTACHMENTS_CONFIG, settings);
			//JsonFileLoader<RandomPresetsSettings>.JsonLoadFile(GLS_RANDOMPRESETS_CONFIG, settings);
		}
		else {
			settings.RPAttachmentsDefaultSettings();
		}

		return settings;
	}
};

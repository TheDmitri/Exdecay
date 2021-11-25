class GlobalLootSystemCore
{
	ref SpawnableTypesSettings m_SpawnableTypesSettings;
	ref RandomPresetsSettings m_RandomPresetsSettings;
	ref RPAttachmentsSettings m_RPAttachmentsSettings;

	ref map<string, ref array<ref RandomPreset>>m_Types;
	ref map<string, ref array<ref GlobalLootItems>>m_RandomPresets;
	ref map<string, ref array<ref GlobalLootItems>>m_Attachments;

	void GlobalLootSystemCore()
  {
		GetGLSLogger().LogInfo("GlobalLootSystemCore - Started ! => Loading config...");
		#ifdef GLSDEBUG
		GetGLSLogger().LogInfo("DEBUG MODE ENABLED");
		#endif
		if (GetGame().IsServer() || !GetGame().IsMultiplayer())
		{
			//LOADING CONFIG FILES...
			GetGLSLogger().LogInfo("Current config loading...");
			m_SpawnableTypesSettings = SpawnableTypesSettings.Load();
			m_RandomPresetsSettings = RandomPresetsSettings.Load();
			m_RPAttachmentsSettings = RPAttachmentsSettings.Load();

			m_Types = new map<string, ref array<ref RandomPreset>>;
			m_RandomPresets = new map<string, ref array<ref GlobalLootItems>>;
			m_Attachments = new map<string, ref array<ref GlobalLootItems>>;

			m_SpawnableTypesSettings.ConvertToMap(m_Types);
			m_RandomPresetsSettings.ConvertToMap(m_RandomPresets);
			m_RPAttachmentsSettings.ConvertToMap(m_Attachments);
		}
  }

	void ~GlobalLootSystemCore()
	{
  }

};

modded class MissionServer extends MissionBase
{
	void MissionServer()
	{
		m_EZExtractionZoneCore = NULL;
		GetEZExtractionZoneCore();
	}

	void ~MissionServer() {
	}

	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
	{
		super.InvokeOnConnect(player,identity);
		InitializeEZConfigToPlayer(player,identity);
	}

	void InitializeEZConfigToPlayer(PlayerBase player, PlayerIdentity identity)
	{
		#ifdef EZDEBUG
		GetEZLogger().LogInfo("Start - InitializeConfigToPlayer");
		#endif
		if(!GetEZConfig().IsExtractionZoneActive)return;
		GetEZExtractionZoneCore().m_EZExtractionZoneServer.SendEZConfigToClient(identity);
	}

};

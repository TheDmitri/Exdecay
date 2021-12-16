modded class MissionServer extends MissionBase
{
	void MissionServer()
	{
		/*we create the core class on server in order to have it working on server side*/
		m_ExdecayTeleporterCore = NULL;
		GetExdecayTeleporterCore();
	}

	void ~MissionServer() {
	}

	override void InvokeOnConnect(PlayerBase player, PlayerIdentity identity)
	{
		/*I usually send config data from server to client here when the player join*/
		super.InvokeOnConnect(player,identity);
		GetExdecayTeleporterCore().TransfertExdecayTeleporterConfigToClient(identity);
		if(player){
			player.eTUID = identity.GetPlainId();
			player.eTName = identity.GetName();
		}
	}

	override void InvokeOnDisconnect( PlayerBase player )
	{
		/*When I need to save data on server side in a database, that's where I do it*/
		super.InvokeOnDisconnect(player);
	}
};

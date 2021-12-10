modded class MissionServer
{
	override void PlayerDisconnected(PlayerBase player, PlayerIdentity identity, string uid)
	{
		int shortId = identity.GetPlainId().Substring(8, 9).ToInt();
		for (int i = 0; i < Land_EX_Building_Elevator_Out.GetAll().Count(); i++)
		{
			if (Land_EX_Building_Elevator_Out.GetAll()[i].GetOwner() == shortId)
			{
				Land_EX_Building_Elevator_Out elevator = Land_EX_Building_Elevator_Out.Cast(Land_EX_Building_Elevator_Out.GetAll()[i]);
				elevator.SetOwner(0);
				elevator.ClearHideout();
			}
		}
		super.PlayerDisconnected(player, identity, uid);
	};
	
	void MissionServer()
	{
		GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(StashDebug, 15000, false);
	}
	void StashDebug()
	{
		Print("Stash Debug: Total Stashes: " + ExdecayStashObject.GetAll().Count());
		for (int i = 0; i < ExdecayStashObject.GetAll().Count(); i++)
		{
			ExdecayStashObject currStash = ExdecayStashObject.GetAll()[i];
			Print("Stash Debug: Stash# " + i + " , owned by " + currStash.GetOwner() + " , Current Lifetime: " + currStash.GetLifetime() );
			if (currStash.GetLifetime() < 86400)
				Print("Stash Debug: Stash# " + i + " has less than 24h lifetime!");
		}		
	}
}
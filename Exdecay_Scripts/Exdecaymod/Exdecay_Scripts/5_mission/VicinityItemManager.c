modded class VicinityItemManager
{
	override void AddVicinityItems(Object object)
	{
		if ( ExdecayShouldShowInVicinity(object) )
			super.AddVicinityItems(object);
	}
	bool ExdecayShouldShowInVicinity(Object filtered_object)
	{	
		Print("ExdecayShouldShowInVicinity");
		if (ExdecayStashObject.Cast(filtered_object) && ( !GetGame().IsServer() || !GetGame().IsMultiplayer() ))
		{
			int shortId = GetGame().GetUserManager().GetTitleInitiator().GetUid().Substring(8, 9).ToInt();
			ExdecayStashObject stash = ExdecayStashObject.Cast(filtered_object);
			if (stash.IsLocked() && stash.GetOwner() != shortId)
				return false;
		}
		return true;
	};
}
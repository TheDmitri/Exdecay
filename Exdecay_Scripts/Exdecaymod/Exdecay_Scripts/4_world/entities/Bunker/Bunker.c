class Land_Ex_Building_BunkerEntrance extends BuildingSuper
{	
	override void SetActions()
	{
		super.SetActions();
		
		AddAction(ActionExdecayOpenBunkerDoor);
		AddAction(ActionExdecayCloseBunkerDoor);
	}
};
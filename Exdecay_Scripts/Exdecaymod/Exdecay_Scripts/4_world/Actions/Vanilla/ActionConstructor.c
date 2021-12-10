modded class ActionConstructor
{
	override void RegisterActions(TTypenameArray actions)
	{
		super.RegisterActions(actions);
		actions.Insert(ActionExdecayDebugElevator);
		actions.Insert(ActionExdecaySummonElevator);
		actions.Insert(ActionExdecaySendElevator);
		actions.Insert(ActionExdecaySendElevatorSolo);
		actions.Insert(ActionExdecaySendElevatorUp);
		actions.Insert(ActionExdecayOpenBunkerDoor);
		actions.Insert(ActionExdecayCloseBunkerDoor);
		actions.Insert(ActionExdecayToggleLockingStash);
	};
};
modded class ActionOpenDoors
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if ( target.GetObject().GetType() == "Land_EX_Building_Elevator_In" ||target.GetObject().GetType() == "Land_EX_Building_Elevator_Out" || target.GetObject().GetType() == "Land_Ex_Building_BunkerEntrance"  )
			return false;

		return super.ActionCondition( player, target, item );
	}	
}
modded class ActionCloseDoors
{
	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		if ( target.GetObject().GetType() == "Land_EX_Building_Elevator_In" ||target.GetObject().GetType() == "Land_EX_Building_Elevator_Out" || target.GetObject().GetType() == "Land_Ex_Building_BunkerEntrance" )
			return false;

		return super.ActionCondition( player, target, item );
	}	
}
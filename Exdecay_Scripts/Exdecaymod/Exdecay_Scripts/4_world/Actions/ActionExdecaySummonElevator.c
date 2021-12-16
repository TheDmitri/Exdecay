class ActionExdecaySummonElevator : ActionInteractBase
{

	void ActionExdecaySummonElevator()
	{
		m_CommandUID        = DayZPlayerConstants.CMD_ACTIONMOD_OPENDOORFW;
		m_StanceMask        = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;

	}
	override void CreateConditionComponents()
	{
		m_ConditionItem = new CCINone;
		m_ConditionTarget = new CCTObject(UAMaxDistances.LARGE);
	}
	override string GetText()
	{
		string text = "Call Elevator";
		return text;
	}

	override bool HasProgress()
	{
		return false;
	}


	override bool ActionCondition ( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object target_object = target.GetObject();
		Land_EX_Building_Elevator_In elevator = Land_EX_Building_Elevator_In.Cast( target_object );
		string selection = target_object.GetActionComponentName( target.GetComponentIndex() );
		if ( selection == "call_button" && elevator.GetOwner() == 0 && elevator.GetElevatorState() == StashStates.ELEVATOR_READY)
		{
				return true;
		}
		return false;
	}

	void DelayedReleaseOwner(Land_EX_Building_Elevator_In elevator)
	{
		Sleep(15000);
		elevator.ReleaseOwner();
	}

	override void OnExecuteServer( ActionData action_data )
	{
		PlayerBase player = PlayerBase.Cast( action_data.m_Player);
		Land_EX_Building_Elevator_In elevator = Land_EX_Building_Elevator_In.Cast( action_data.m_Target.GetObject() );
		int shortId = action_data.m_Player.GetIdentity().GetPlainId().Substring(8, 9).ToInt();
		bool hasOtherReservation = false;
		for (int i = 0; i < Land_EX_Building_Elevator_In.GetAll().Count(); i++)
		{
			if (Land_EX_Building_Elevator_In.GetAll()[i].GetOwner() == shortId)
			{
				hasOtherReservation = true;
			}
		}
		if (!hasOtherReservation)
		{
			elevator.SetOwner(shortId);
			elevator.SetElevatorState(StashStates.ELEVATOR_CALLED);
			//GetGame().GetCallQueue(CALL_CATEGORY_GAMEPLAY).CallLater(DelayedReleaseOwner, 15000, false, elevator);
			thread DelayedReleaseOwner();
			elevator.OpenDoors();
		}
	}
}

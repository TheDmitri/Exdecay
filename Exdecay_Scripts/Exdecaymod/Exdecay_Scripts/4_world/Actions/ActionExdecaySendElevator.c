class ActionExdecaySendElevator : ActionInteractBase
{

	void ActionExdecaySendElevator()
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
		string text = "Descend";
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
		int shortId;
		if ( !GetGame().IsServer() || !GetGame().IsMultiplayer() )
			shortId = GetGame().GetUserManager().GetTitleInitiator().GetUid().Substring(8, 9).ToInt();
		else
			shortId = player.GetIdentity().GetPlainId().Substring(8, 9).ToInt();


		if ( elevator.GetOwner() == shortId && selection == "out_button" && elevator.GetDoorState())
			return true;

		return false;
	}

	override void OnExecuteServer( ActionData action_data )
	{
		Land_EX_Building_Elevator_In elevator = Land_EX_Building_Elevator_In.Cast( action_data.m_Target.GetObject() );
		elevator.AssignOutput(false)
	}
}


class ActionExdecaySendElevatorSolo : ActionInteractBase
{

	void ActionExdecaySendElevator()
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
		string text = "Descend (Solo)";
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
		int shortId;
		if ( !GetGame().IsServer() || !GetGame().IsMultiplayer() )
			shortId = GetGame().GetUserManager().GetTitleInitiator().GetUid().Substring(8, 9).ToInt();
		else
			shortId = player.GetIdentity().GetPlainId().Substring(8, 9).ToInt();


		if ( elevator.GetOwner() == shortId && selection == "out_button_solo" && elevator.GetDoorState())
			return true;

		return false;
	}

	override void OnExecuteServer( ActionData action_data )
	{
		Land_EX_Building_Elevator_In elevator = Land_EX_Building_Elevator_In.Cast( action_data.m_Target.GetObject() );
		elevator.AssignOutput(true)
	}
}

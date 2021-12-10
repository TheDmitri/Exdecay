class ActionExdecayDebugElevator : ActionInteractBase
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
		string text = "<<DEBUG>>";
		return text;
	}

	override bool HasProgress()
	{
		return false;
	}
		
		
	override bool ActionCondition ( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object target_object = target.GetObject();
		string selection = target_object.GetActionComponentName( target.GetComponentIndex() );
		int shortId;
		if ( !GetGame().IsServer() || !GetGame().IsMultiplayer() )
			shortId = GetGame().GetUserManager().GetTitleInitiator().GetUid().Substring(8, 9).ToInt();
		else
			shortId = player.GetIdentity().GetPlainId().Substring(8, 9).ToInt();
		
		if ( selection == "debug" && shortId == 18914897) //18914897
			return true;
		
		return false;
	}
		
	override void OnExecuteServer( ActionData action_data )
	{
		Land_EX_Building_Elevator_In elevatorIn = Land_EX_Building_Elevator_In.Cast( action_data.m_Target.GetObject() );
		Land_EX_Building_Elevator_Out elevatorOut = Land_EX_Building_Elevator_Out.Cast( action_data.m_Target.GetObject() );
		int shortId = action_data.m_Player.GetIdentity().GetPlainId().Substring(8, 9).ToInt();
		if (elevatorIn)
		{
			Print("ElevatorDebug: ElevatorIn.GetOwner(): " + elevatorIn.GetOwner());
			if (elevatorIn.GetDestination())
				Print("ElevatorDebug: ElevatorIn.GetDestination().GetOwner(): " + elevatorIn.GetDestination().GetOwner());
			elevatorIn.SetOwner(0);
		}
		if (elevatorOut)
		{
			Print("ElevatorDebug: elevatorOut.GetOwner(): " + elevatorOut.GetOwner());
			if (elevatorOut.GetDestination())
				Print("ElevatorDebug: elevatorOut.GetDestination().GetOwner(): " + elevatorOut.GetDestination().GetOwner());			
		}
	}	
	override void OnExecuteClient( ActionData action_data )
	{
		Land_EX_Building_Elevator_In elevatorIn = Land_EX_Building_Elevator_In.Cast( action_data.m_Target.GetObject() );
		Land_EX_Building_Elevator_Out elevatorOut = Land_EX_Building_Elevator_Out.Cast( action_data.m_Target.GetObject() );
		int shortId = action_data.m_Player.GetIdentity().GetPlainId().Substring(8, 9).ToInt();
		if (elevatorIn)
		{
			elevatorIn.OpenDoors();
			Print("ElevatorDebug: ElevatorIn.GetOwner(): " + elevatorIn.GetOwner());
			if (elevatorIn.GetDestination())
				Print("ElevatorDebug: ElevatorIn.GetDestination().GetOwner(): " + elevatorIn.GetDestination().GetOwner());
		}
		if (elevatorOut)
		{
			elevatorOut.CloseDoors();
			Print("ElevatorDebug: elevatorOut.GetOwner(): " + elevatorOut.GetOwner());
			if (elevatorOut.GetDestination())
				Print("ElevatorDebug: elevatorOut.GetDestination().GetOwner(): " + elevatorOut.GetDestination().GetOwner());			
		}
	}
}
class ActionExdecayOpenBunkerDoor : ActionInteractBase
{

	void ActionExdecayOpenBunkerDoor()
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
		string text = "Toggle Bunker Door";
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
		
		if ( selection == "bunker_panel" )
			return true;
		
		return false;
	}
		
	override void OnExecuteServer( ActionData action_data )
	{
		Land_Ex_Building_BunkerEntrance bunker = Land_Ex_Building_BunkerEntrance.Cast( action_data.m_Target.GetObject() );
		if (!bunker.IsDoorOpen(0))
			bunker.OpenDoor(0);
		else
			bunker.CloseDoor(0);
	}	
	override void OnExecuteClient( ActionData action_data )
	{
		Land_Ex_Building_BunkerEntrance bunker = Land_Ex_Building_BunkerEntrance.Cast( action_data.m_Target.GetObject() );
		if (!bunker.IsDoorOpen(0))
			bunker.OpenDoor(0);
		else
			bunker.CloseDoor(0);
		
	}
}

class ActionExdecayCloseBunkerDoor : ActionInteractBase
{

	void ActionExdecayOpenBunkerDoor()
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
		string text = "Toggle Bunker Door";
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
		
		if ( selection == "bunker_panel2" )
			return true;
		
		return false;
	}
		
	override void OnExecuteServer( ActionData action_data )
	{
		Land_Ex_Building_BunkerEntrance bunker = Land_Ex_Building_BunkerEntrance.Cast( action_data.m_Target.GetObject() );
		if (!bunker.IsDoorOpen(0))
			bunker.OpenDoor(0);
		else
			bunker.CloseDoor(0);
	}	
	override void OnExecuteClient( ActionData action_data )
	{
		Land_Ex_Building_BunkerEntrance bunker = Land_Ex_Building_BunkerEntrance.Cast( action_data.m_Target.GetObject() );
		if (!bunker.IsDoorOpen(0))
			bunker.OpenDoor(0);
		else
			bunker.CloseDoor(0);
		
	}
}
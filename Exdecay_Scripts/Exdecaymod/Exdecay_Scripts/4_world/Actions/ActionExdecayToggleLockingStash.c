class ActionExdecayToggleLockingStash : ActionInteractBase
{

	protected ActionTarget m_ActionTarget;
	
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
		string text = "Toggle Stash Lock";
		if (m_ActionTarget.GetObject())
		{
			ExdecayStashObject stash = ExdecayStashObject.Cast(m_ActionTarget.GetObject());

			if (stash.IsLocked())
				text = "Unlock Stash To Visitors";
			else
				text = "Lock Stash From Visitors";
		};
		return text;
	}

	override bool HasProgress()
	{
		return false;
	}
		
		
	override bool ActionCondition ( PlayerBase player, ActionTarget target, ItemBase item )
	{
		m_ActionTarget = target;
		ExdecayStashObject stash = ExdecayStashObject.Cast(target.GetObject());
		
		int shortId;
		if ( !GetGame().IsServer() || !GetGame().IsMultiplayer() )
			shortId = GetGame().GetUserManager().GetTitleInitiator().GetUid().Substring(8, 9).ToInt();
		else
			shortId = player.GetIdentity().GetPlainId().Substring(8, 9).ToInt();
		
		
		if (shortId != stash.GetOwner() )
			return false
		
		return true;
	}
		
	override void OnExecuteServer( ActionData action_data )
	{
		ExdecayStashObject stash = ExdecayStashObject.Cast( action_data.m_Target.GetObject() );
		if ( stash.IsLocked())
			stash.Unlock();
		else
			stash.Lock();

	}	
}

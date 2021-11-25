class ActionETPMenu: ActionInteractBase
{
	void ActionETPMenu()
	{
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONMOD_INTERACTONCE;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_ERECT | DayZPlayerConstants.STANCEMASK_CROUCH;
		m_HUDCursorIcon = CursorIcons.CloseHood;
	}

    override void CreateConditionComponents()
		{
			m_ConditionTarget = new CCTObject(8);
			m_ConditionItem = new CCINone;
		}

	override string GetText()
	{
		return "Teleporter Menu";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
    {
        if ( GetGame().IsServer() )
            return true;

        PlayerBase ntarget = PlayerBase.Cast( target.GetObject() );
				//Print("ID Target:"+ntarget.TraderID.ToString()+"ntarget.MaxPlayerPerID:"+ntarget.MaxPlayerPerID.ToString());
				if(ntarget && ntarget.ExdecayTeleporterID == -111)
				{
					return true;
				}

				BuildingBase nObject = BuildingBase.Cast( target.GetObject() );
				if(nObject && nObject.ExdecayTeleporterID == -111)
				{
					return true;
				}
				return false;
    }

    override void OnStartClient(ActionData action_data)
    {
				GetRPCManager().SendRPC("ExdecayTeleporter", "GetExdecayTeleporterMenuRequest",  NULL, true, NULL);
    }
}

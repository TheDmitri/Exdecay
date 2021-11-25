class ActionGlobalLootSearchCrateCB : ActionContinuousBaseCB
{
	override void CreateActionComponent()
	{
		int pos = SearchableCrates.Find(m_ActionData.m_Target.GetObject().GetType());
		if(pos != -1)
		{
			int time = ActionLoopingDelay[pos];
			ItemBase item_in_hands = ItemBase.Cast(m_ActionData.m_Player.GetHumanInventory().GetEntityInHands() );
			if(item_in_hands && item_in_hands.GetType().Contains(ToolsCrates[pos]))
			{
				time = time * 0.5;
			}
			m_ActionData.m_ActionComponent = new CAContinuousTime(time);
		}
		else
			m_ActionData.m_ActionComponent = new CAContinuousTime(6);
	}
};

class ActionGlobalLootSearchCrate: ActionContinuousBase
{
	void ActionGlobalLootSearchCrate()
	{
		m_CallbackClass = ActionGlobalLootSearchCrateCB;
		m_CommandUID = DayZPlayerConstants.CMD_ACTIONFB_INTERACT;
		m_FullBody = true;
		m_StanceMask = DayZPlayerConstants.STANCEMASK_CROUCH | DayZPlayerConstants.STANCEMASK_ERECT;
		m_SpecialtyWeight = UASoftSkillsWeight.ROUGH_HIGH;
	}

	override void CreateConditionComponents()
	{
		m_ConditionTarget = new CCTObject(3);
		m_ConditionItem = new CCINone;
	}

	override string GetText()
	{
		return "Search Crate";
	}

	override bool ActionCondition( PlayerBase player, ActionTarget target, ItemBase item )
	{
		Object targetObject = target.GetObject();
		#ifdef GLSDEBUG
		GetGLSLogger().LogInfo("ActionCondition:"+target.GetObject().GetType());
		#endif
		ItemBase tItem = ItemBase.Cast(targetObject);
		if(tItem)
		{
			if (SearchableCrates.Find(tItem.GetType()) != -1)
			{
				if(CheckForCrateCloseBy(tItem.GetType(), tItem.GetPosition()))
					return true;
			}
		}

		return false;
	}

	bool CheckForCrateCloseBy(string classname, vector position)
	{
		array<Object> objects = new array<Object>;
		array<CargoBase> proxyCargos = new array<CargoBase>;
		GetGame().GetObjectsAtPosition(position, 0.5, objects, proxyCargos);
		string typeToFind = classname;
		typeToFind.Replace("_static","");
		if (objects)
		{
			for (int i = 0; i < objects.Count(); i++ )
			{
				ItemBase item = ItemBase.Cast(objects[i]);
				if (item && item.GetType() == typeToFind)
				{
					return false;
				}
			}
		}
		return true;
	}

	override void OnFinishProgressServer( ActionData action_data )
	{
		Object targetObject = action_data.m_Target.GetObject();
		if ( targetObject )
		{
			ItemBase item = ItemBase.Cast(targetObject);
			if(item)
			{
				GenerateCrate(item.GetType(), item.GetPosition(), item.GetOrientation());
			}
		}
	}

	void GenerateCrate(string crateNameStatic, vector p, vector o)
	{
		string crateName = crateNameStatic;
		crateName.Replace("_static","");
		Container_Base crate = Container_Base.Cast(GetGame().CreateObject( crateName, p, false, true, true));
		if(!crate)return;
		crate.SetOrientation(o);

		string type = crateName;
		int count = GetGlobalLootSystemCore().m_Types[type].Count();
		int stop = -1;
		RandomPreset randomPreset;

		int loop = 0;
		while(stop == -1)
		{
			randomPreset = GetGlobalLootSystemCore().m_Types[type].GetRandomElement();
			if( Math.RandomFloatInclusive(0,1) <= randomPreset.chance){
				stop = 1;
			}
			loop++;
		}

		array<ref GlobalLootItems> items = new array<ref GlobalLootItems>;
		items = GetGlobalLootSystemCore().m_RandomPresets[randomPreset.randomPresetName];
		foreach(GlobalLootItems item: items)
		{
			if( Math.RandomFloatInclusive(0,1) <= item.chance)
			{
				ItemBase newItem = ItemBase.Cast(crate.GetInventory().CreateInInventory(item.itemName));
				if(!newItem) continue;
				GlobalLootSystemHelper.SetQuantityBasedOnConfig(newItem, item.quantity);
				array<ref GlobalLootItems> attch = new array<ref GlobalLootItems>;
				if(GetGlobalLootSystemCore().m_Attachments.Find(item.itemName,attch))
				{
					foreach(GlobalLootItems attchitem: attch)
					{
						if( Math.RandomFloatInclusive(0,1) <= attchitem.chance)
						{
							ItemBase newAttach = ItemBase.Cast(crate.GetInventory().CreateInInventory(attchitem.itemName));
							if(!newAttach)continue;
							GlobalLootSystemHelper.SetQuantityBasedOnConfig(newAttach, attchitem.quantity);
						}
					}
				}
			}
		}
	}
};

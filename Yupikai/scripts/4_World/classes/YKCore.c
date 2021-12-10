class YKCore
{
	ref TStringArray playerAttachments = {
		"Head",
		"Shoulder",
		"Melee",
		"Headgear",
		"Mask",
		"Eyewear",
		"Hands",
		"LeftHand",
		"Gloves",
		"Armband",
		"Vest",
		"Body",
		"Back",
		"Hips",
		"Legs",
		"Feet",
		"Splint_Right"
	};

	void YKCore()
  {
		GetYKLogger().LogReport("TraderPlusCore - Started !");
		//we call our function that will initiaze our RPC
		InitRPC();
  }

	void ~YKCore(){
  }

	void InitRPC()
		{
			if (GetGame().IsServer())
			{
				GetRPCManager().AddRPC("YupikaiPauvreCon", "AnalysedReportedPlayer", this, SingeplayerExecutionType.Client);
			}
		}

		//-------------------------------------------RPC PART--------------------------------------------------------//
		void AnalysedReportedPlayer(CallType type, ParamsReadContext ctx, PlayerIdentity sender, Object target)
		{
			if(!GetGame().IsServer())return;

			Param1<vector> data;
	     if (!ctx.Read(data))
	       return;

			GetYKLogger().LogReport("AnalysedReportedPlayer triggered !");

			int	low	 =	0;
	 		int	high =	0;
	 		GetGame().GetPlayerNetworkIDByIdentityID( sender.GetPlayerId(), low, high );
	 		PlayerBase reporter = PlayerBase.Cast( GetGame().GetObjectByNetworkId(low, high ));
			if(reporter.GetLastReport() + 30 > JMDate.Now(true).GetTimestamp())return;

			reporter.SetLastReport(JMDate.Now(true).GetTimestamp());
			GetYKLogger().LogReport("reporter name:"+sender.GetName());
			GetYKLogger().LogReport("reporter pos:"+reporter.GetPosition());
			GetYKLogger().LogReport("reporter targetpos:"+data.param1);

			vector targetpos = data.param1;

			array<Object> nearest_objects = new array<Object>;
			array<CargoBase> proxy_cargos = new array<CargoBase>;

			GetGame().GetObjectsAtPosition3D(targetpos, 0.5, nearest_objects, proxy_cargos);
			if (nearest_objects.Count() < 1) return;

			GetYKLogger().LogReport("=====================================================");
			foreach(Object obj: nearest_objects)
			{
				if(obj && obj.IsInherited(PlayerBase))
				{
					PlayerBase player = PlayerBase.Cast(obj);
					if(player && player.GetIdentity() != sender)
					{
						player.SetYupiFlag(true);
						GetYKLogger().LogReport("Player Name:" + player.GetIdentity().GetName() + "has been flagged!");
						GetYKLogger().LogReport("Player Steam ID:" + player.GetIdentity().GetPlainId());
						GetYKLogger().LogReport("Player position:" + player.GetPosition());
						GetPlayersAttachments(player);
						GetYKLogger().LogReport("All Items:");
						array<EntityAI> itemsArray = new array<EntityAI>;
			  		player.GetInventory().EnumerateInventory(InventoryTraversalType.PREORDER, itemsArray);
			  		foreach(EntityAI ent: itemsArray)
			  		{
							if(ent)
							{
								GetYKLogger().LogReport(ent.GetType());
							}
						}
					}
				}
			}
			GetYKLogger().LogReport("=====================================================");
		}

		void GetPlayersAttachments(PlayerBase player)
		{
			for(int i=0;i<playerAttachments.Count();i++)
			{
				EntityAI ent = player.FindAttachmentBySlotName(playerAttachments[i]);
				if(ent)
				{
					GetYKLogger().LogReport("AttachementSlot:"+playerAttachments[i]+" - Items:"+ent.GetType());
				}
			}
		}
	};

	static ref YKCore m_YKCore;
	static YKCore GetYKCore() {
		if ( !m_YKCore ) {
			m_YKCore = new YKCore;
		}
		return m_YKCore;
	}

modded class PlayerBase extends ManBase
{
	int ExdecayTeleporterID;
	private EffectSound m_ETPSound;

	override void Init()
	{
		super.Init();
		ExdecayTeleporterID = -1;
		RegisterNetSyncVariableInt("ExdecayTeleporterID");
	}

	void SetExdecayTeleporterID(int id)
	{
		ExdecayTeleporterID = id;
		SetSynchDirty();
	}

	void SetupExdecayTeleporterNPC(StaticObjectNPC data)
	{
		SetExdecayTeleporterID(-111);
		SetPosition(data.Position);
		SetOrientation(data.Orientation);
		SetAllowDamage(false);
	}

	override void SetActions()
  {
		super.SetActions();
		AddAction(ActionETPMenu);
  }

	void DressExdecayNPC(array<string> clothes)
	{
		for (int i = 0; i < clothes.Count(); i++)
		{
			if(!clothes.Get(i) || clothes.Get(i) == "")continue;
			GetInventory().CreateInInventory(clothes.Get(i));
		}
	}

	void PlayExdecayTeleporterSound(int id)
	{
		if(m_ETPSound && m_ETPSound.IsSoundPlaying())m_ETPSound.SoundStop();
		if(id == 1)
		{
			PlaySoundSet( m_ETPSound,"ExdecayTeleporter_Sound_Quick_Event_SoundSet" , 0, 0);
		}
		else
		{
			PlaySoundSet( m_ETPSound,"ExdecayTeleporter_Sound_Confirm_SoundSet" , 0, 0);
		}
	}
};

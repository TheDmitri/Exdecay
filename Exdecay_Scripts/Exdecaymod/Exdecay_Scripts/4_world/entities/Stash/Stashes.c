class ExdecayStashObject extends Container_Base
{
	private int m_PlayerID = 0;
	private static ref set< ExdecayStashObject > m_AllStashes = new set< ExdecayStashObject >;
	private static ref map<int, ExdecayStashObject > m_MapAllStashes = new map<int, ExdecayStashObject >;
	private bool m_IsLocked = true;
	void ExdecayStashObject()
	{
		m_AllStashes.Insert(this);
		RegisterNetSyncVariableBool("m_IsLocked");
		RegisterNetSyncVariableInt("m_PlayerID");
	}
	override void EEInit()
	{
		super.EEInit();
		int shortId;
		if ( !GetGame().IsServer() || !GetGame().IsMultiplayer() )
		{
			shortId = GetGame().GetUserManager().GetTitleInitiator().GetUid().Substring(8, 9).ToInt();
			if (shortId != GetOwner() && IsLocked())
				//GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);
		}
	}
	void ~ExdecayStashObject()
	{
		if(m_MapAllStashes && m_MapAllStashes[m_PlayerID])
				m_MapAllStashes.Remove(m_PlayerID);

		int i;

		i = m_AllStashes.Find( this );
		if ( i >= 0 )
		{
			m_AllStashes.Remove( i );
		}
	}

	static set< ExdecayStashObject > GetAll()
	{
		return m_AllStashes;
	}

	static map<int, ExdecayStashObject > GetMapAll()
	{
		return m_MapAllStashes;
	}

	void SetOwner(int id)
	{
		m_PlayerID = id;
		m_MapAllStashes.Set(id, this);
	}

	int GetOwner()
	{
		return m_PlayerID;
	}

	override bool CanPutIntoHands( EntityAI parent )
	{
		return false;
	}
	override bool CanPutInCargo( EntityAI item )
	{
		return false;
	}
	override void OnStoreSave( ParamsWriteContext ctx )
	{
		super.OnStoreSave( ctx );

		ctx.Write( m_PlayerID );
	}

	override bool OnStoreLoad( ParamsReadContext ctx, int version )
	{
		if ( !super.OnStoreLoad( ctx, version ) )
			return false;

		if (ctx.Read( m_PlayerID ))
			m_MapAllStashes.Set(m_PlayerID, this);
		else return false;
		SetPosition("52 1 1282");
		return true;
	}
	bool IsLocked()
	{
		return m_IsLocked;
	}
	void Lock()
	{
		m_IsLocked = true;
		SetSynchDirty();
/* 		int shortId = GetGame().GetUserManager().GetTitleInitiator().GetUid().Substring(8, 9).ToInt();
		if (shortId != GetOwner()) */
				//GetInventory().LockInventory(HIDE_INV_FROM_SCRIPT);
	}
	void Unlock()
	{
		m_IsLocked = false;
		SetSynchDirty();
		//GetInventory().UnlockInventory(HIDE_INV_FROM_SCRIPT);
	}

/* 	override bool CanReceiveItemIntoCargo( EntityAI item )
	{
		int shortId;
		if ( !GetGame().IsServer() || !GetGame().IsMultiplayer() )
		{
			shortId = GetGame().GetUserManager().GetTitleInitiator().GetUid().Substring(8, 9).ToInt();
			if ( IsLocked() )
				return (shortId == GetOwner());
		}
		return !IsLocked();
	}

	override bool CanReleaseCargo( EntityAI attachment )
	{
		int shortId;
		if ( !GetGame().IsServer() || !GetGame().IsMultiplayer() )
		{
			shortId = GetGame().GetUserManager().GetTitleInitiator().GetUid().Substring(8, 9).ToInt();
			if ( IsLocked() )
				return (shortId == GetOwner());
		}

		return !IsLocked();
	} */

	void InitStarterKit()
	{
		GetInventory().CreateInInventory("Glock19");
		GetInventory().CreateInInventory("Mag_Glock_15Rnd");
		GetInventory().CreateInInventory("Mag_Glock_15Rnd");
		GetInventory().CreateInInventory("Mag_Glock_15Rnd");
		GetInventory().CreateInInventory("TaloonBag_Blue");
		GetInventory().CreateInInventory("BandageDressing");
		GetInventory().CreateInInventory("BandageDressing");
		GetInventory().CreateInInventory("TetracyclineAntibiotics");
		GetInventory().CreateInInventory("Morphine");
		GetInventory().CreateInInventory("WeaponCleaningKit");
	};
	override void SetActions()
	{
		super.SetActions();
		AddAction(ActionExdecayToggleLockingStash);
	}

}

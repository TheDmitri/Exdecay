static ref GlobalLootSystemCore m_GlobalLootSystemCore;
static GlobalLootSystemCore GetGlobalLootSystemCore() {
	if ( !m_GlobalLootSystemCore ) {
		m_GlobalLootSystemCore = new GlobalLootSystemCore;
	}
	return m_GlobalLootSystemCore;
}

static int GLSGetTimeStamp()
{
	int year, month, day, hour, minute, second;
	GetHourMinuteSecondUTC(hour, minute, second);
	GetYearMonthDayUTC(year, month, day);
	return JMDate.Timestamp(year,month,day,hour,minute,second);
}

class GlobalLootSystemHelper
{
	static int GetMaxItemQuantityClient(string classname)
  {
    string Vpath = CFG_VEHICLESPATH + " " + classname + " varQuantityMax";
    if ( GetGame().ConfigIsExisting( Vpath ) )
    {
      return g_Game.ConfigGetInt( Vpath );
    }

    string Wpath = CFG_WEAPONSPATH + " " + classname + " varQuantityMax";
    if (GetGame().ConfigIsExisting( Wpath ))
    {
        return g_Game.ConfigGetInt( Wpath );
    }

    string Mpath = CFG_MAGAZINESPATH + " " + classname + " varQuantityMax";
    if(classname.Contains("Ammo_") || classname.Contains("Mag_")){
      Mpath = CFG_MAGAZINESPATH + " " + classname + " count";
    }
    if (GetGame().ConfigIsExisting( Mpath ))
    {
        return g_Game.ConfigGetInt( Mpath );
    }

    return 0;
  }

	static ItemBase SetQuantity(ItemBase item, int quantity)
  {
    Magazine mag = Magazine.Cast(item);
    if (mag)
        mag.ServerSetAmmoCount(quantity);
    else
      item.SetQuantity(quantity);
    return item;
  }

	static ItemBase SetQuantityBasedOnConfig(ItemBase item, int quantity)
	{
		float currentquantity, minquantity, maxquantity;

		if(quantity == -1){
			int qty = GlobalLootSystemHelper.GetMaxItemQuantityClient(item.GetType());
			return SetQuantity(item, maxquantity);
		}

		if(quantity == -2){
			maxquantity = GlobalLootSystemHelper.GetMaxItemQuantityClient(item.GetType());
			if(maxquantity == 0 || maxquantity == 1)return item;
			int randqty = Math.RandomIntInclusive(1,maxquantity);
			return SetQuantity(item, randqty);
		}

		return SetQuantity(item, quantity);
	}

	static Weapon_Base CreateWeaponWithMagazine( string sWeapon, string sMagazine, vector pos)
    {
        Weapon_Base oWpn = Weapon_Base.Cast(GetGame().CreateObject( sWeapon , "0 0 0" ));

        if ( !oWpn )
            return NULL;

        int stateId = -1;

        if ( oWpn.IsInherited( SKS_Base ) )
            return oWpn;
        else if ( oWpn.IsInherited( BoltActionRifle_InnerMagazine_Base ) )
            return oWpn;
        else if ( oWpn.IsInherited( DoubleBarrel_Base ) )
            return oWpn;
        else if ( oWpn.IsInherited( Pistol_Base ) )
            stateId = PistolStableStateID.CLO_DIS_BU0_MA1;
        else if ( oWpn.IsInherited( CZ527_Base ) )
            stateId = CZ527StableStateID.CZ527_CLO_BU0_MA1;
        else if ( oWpn.IsInherited( Repeater_Base ) )
            return oWpn;
        else if ( oWpn.IsInherited( RifleBoltFree_Base ) )
            stateId = RBFStableStateID.RBF_CLO_BU0_MA1;
        else if ( oWpn.IsInherited( RifleBoltLock_Base ) )
            stateId = RBLStableStateID.RBL_CLO_BU0_MA1; //stateId = RBLStableStateID.RBL_OPN_BU0_MA1;
        else if ( oWpn.IsInherited( Mp133Shotgun_Base ) )
            return oWpn;

        InventoryLocation mag_il = new InventoryLocation;
        mag_il.SetAttachment( oWpn, NULL, InventorySlots.MAGAZINE );
        Magazine oMag = Magazine.Cast( SpawnEntity( sMagazine, mag_il, ECE_IN_INVENTORY, RF_DEFAULT ) );
        if ( !oMag )
            return oWpn;

        GetGame().RemoteObjectDelete( oWpn );
        GetGame().RemoteObjectDelete( oMag );


        pushToChamberFromAttachedMagazine( oWpn, oWpn.GetCurrentMuzzle() );

        ScriptReadWriteContext ctx = new ScriptReadWriteContext;
        ctx.GetWriteContext().Write( stateId );
        oWpn.LoadCurrentFSMState( ctx.GetReadContext(), GetGame().SaveVersion() );


        GetGame().RemoteObjectCreate( oWpn );
        GetGame().RemoteObjectCreate( oMag );

        return oWpn;
    }
}

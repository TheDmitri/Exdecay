/* modded class PlayerBase
{
    override void Init()
    {			
		DayzPlayerItemBehaviorCfg 	fireArmsItemBehaviour = new DayzPlayerItemBehaviorCfg;		
		fireArmsItemBehaviour.SetFirearms();
		

		GetDayZPlayerType().AddItemInHandsProfileIK("KS23_Base", "dz/anims/workspaces/player/player_main/weapons/player_main_mp133.asi", fireArmsItemBehaviour, "dz/anims/anm/player/ik/weapons/mp133.anm", "dz/anims/anm/player/reloads/mp133/w_mp133_states.anm");
		
        super.Init();     
    }
		
} */


modded class JMAnimRegister
{
	override void OnRegisterFireArms( DayZPlayerType pType, DayzPlayerItemBehaviorCfg pBehavior )
	{
		super.OnRegisterFireArms( pType, pBehavior );
		
		pType.AddItemInHandsProfileIK("KS23_Base", "dz/anims/workspaces/player/player_main/weapons/player_main_mp133.asi", pBehavior, "dz/anims/anm/player/ik/weapons/mp133.anm", "dz/anims/anm/player/reloads/mp133/w_mp133_states.anm");
		
		
	}
	 override void OnBoneRemapping( DayZPlayerType pType )
    {
        super.OnBoneRemapping( pType );

       array<string> ShotgunBoneRemap ={ "bolt", "Weapon_Bolt", "pump", "Weapon_Bone_01","feedRamp", "Weapon_Bone_02", "trigger", "Weapon_Trigger","bullet", "Weapon_Bullet", "boltrelease", "Weapon_Bone_03"};
	pType.AddItemBoneRemap("KS23_Base", ShotgunBoneRemap);
        
        
    }	

};

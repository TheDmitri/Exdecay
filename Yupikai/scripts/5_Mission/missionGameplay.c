modded class MissionGameplay extends MissionBase
{
	override void OnKeyRelease(int key)
	{
		super.OnKeyRelease(key);
		PlayerBase player = PlayerBase.Cast(GetGame().GetPlayer());

		if ( key == KeyCode.KC_F7 )
		{
			vector targetPos = Vector( 0, 0, 0 );
	    vector rayStart = GetGame().GetCurrentCameraPosition();
	    vector rayEnd = rayStart + GetGame().GetCurrentCameraDirection() * 10000;
	    vector contact_pos;
	    vector contact_dir;
	    int contact_component;

	    if( DayZPhysics.RaycastRV( rayStart, rayEnd, contact_pos, contact_dir, contact_component, NULL, NULL, GetGame().GetPlayer(), false, false, ObjIntersectView, 0.0 ) )
	    {
	        targetPos = contact_pos;
	    }

			GetRPCManager().SendRPC("YupikaiPauvreCon", "AnalysedReportedPlayer",  new Param1<vector>(targetPos), true, NULL);
		}
	}
};

modded class BuildingBase
{
	int	ExdecayTeleporterID;

	void BuildingBase()
	{
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
}

modded class DayZPlayerCommandDeathCallback : HumanCommandDeathCallback
{
	//----------------------------------
	// callbacks

	override void 	OnSimulationEnd()
	{
		//syncDebug//Print("DZPI::OnSimulationEnd - trying to drop item");
	}

	PlayerBase m_pPlayer;
}

modded class DayZPlayerImplement
{
		string eTUID = "";
		string eTName = "";

    override void EEKilled(Object killer)
    {
        super.EEKilled(killer);
				if(GetGame().IsServer())
				{
			    ExdecayTeleporterData data = ExdecayTeleporterData.Load(eTName, eTUID);
			    if(data)
			    {
						string mapName = ExdecayTeleporterHelper.GetMapNameBasedOnPosition(GetPosition());
						if(mapName!="" && data.Maps.Contains(mapName))
						{
							data.Maps.Set(mapName, GetETPTimeStamp());
							data.Save(eTUID);
						}
					}
    		}
		}
}

modded class PlayerBase extends ManBase
{
	private bool m_YupiFlag = false;
	private int m_LastReportFromYou = 0;

	void SetYupiFlag(bool state)
	{
		m_YupiFlag = state;
	}

	int GetLastReport()
	{
		return m_LastReportFromYou;
	}

	void SetLastReport(int timeNow)
	{
		m_LastReportFromYou = timeNow;
	}

	override bool CanReceiveItemIntoCargo(EntityAI item)
	{
		if(GetGame().IsServer() && m_YupiFlag)
			GetYKLogger().LogReport("CanReceiveItemIntoCargo attempts:" + item.GetType() + " id:"+GetIdentity().GetPlainId());

		return super.CanReceiveItemIntoCargo(item);
	}

	override bool CanDropEntity (notnull EntityAI item)
	{
		if(GetGame().IsServer() && m_YupiFlag)
			GetYKLogger().LogReport("drop attempt for item" + item.GetType()+ " id:"+GetIdentity().GetPlainId());

		return super.CanDropEntity(item);
	}
}

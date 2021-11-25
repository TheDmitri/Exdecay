static ref EZLogger g_EZLogger;
static EZLogger GetEZLogger(){
	if (!g_EZLogger) {
		g_EZLogger = new EZLogger();
	}
	return g_EZLogger;
}

static ref EZExtractionZoneCore m_EZExtractionZoneCore;
static EZExtractionZoneCore GetEZExtractionZoneCore() {
	if ( !m_EZExtractionZoneCore ) {
		m_EZExtractionZoneCore = new EZExtractionZoneCore;
	}
	return m_EZExtractionZoneCore;
}

static ref ExtractionAreaSettings GetEZConfig()	{
	return GetEZExtractionZoneCore().m_ActiveExtractionAreaSettings;
}

static ref ExtractionLocations GetEZConfigClient()	{
	return GetEZExtractionZoneCore().m_EZExtractionZoneClient.m_ExtractionLocations;
}

static PlayerBase EZGetPlayerByIdentity(PlayerIdentity sender)
{
	int	low	 =	0;
	int	high =	0;
	GetGame().GetPlayerNetworkIDByIdentityID( sender.GetPlayerId(), low, high );
	return PlayerBase.Cast( GetGame().GetObjectByNetworkId(low, high ));
}

static int EZGetTimeStamp()
{
	int year, month, day, hour, minute, second;
	GetHourMinuteSecondUTC(hour, minute, second);
	GetYearMonthDayUTC(year, month, day);
	return JMDate.Timestamp(year,month,day,hour,minute,second);
}

/*To make things easier for me, I use some static class that can be run from anywhere in my code,
it's very efficient to get config data or access my main class that run my code.
However it can create conflict with other mods if someone use to same name, so if you create some static function, make sure
to make the name specific as much as you can. I usually add Name of my mod in front of my function*/

/*Class that deals with the log system*/
static ref ETPLogger g_ETPLogger;
static ETPLogger GetETPLogger(){
	if (!g_ETPLogger) {
		g_ETPLogger = new ETPLogger();
	}
	return g_ETPLogger;
}

/*Class that deals with my core class, where config, client and server part of my code are created*/
static ref ExdecayTeleporterCore m_ExdecayTeleporterCore;
static ExdecayTeleporterCore GetExdecayTeleporterCore() {
	if ( !m_ExdecayTeleporterCore ) {
		m_ExdecayTeleporterCore = new ExdecayTeleporterCore;
	}
	return m_ExdecayTeleporterCore;
}

static ref ExdecayTeleporterMenu GetTeleporterMenu()
{
	return GetExdecayTeleporterCore().m_TeleporterMenu;
}

static ref array<ref ExdecayMap> GetClientMaps(){
	return GetExdecayTeleporterCore().m_Maps;
}

/*clas that allows me to access the client class */
static ref ExdecayTeleporterSettings GetExdecayTeleporterConfig()	{
	return GetExdecayTeleporterCore().m_ExdecayTeleporterSettings;
}

/*Function that allows to get the player variable from its identity => used for RPC*/
static PlayerBase ETPGetPlayerByIdentity(PlayerIdentity sender)
{
	int	low	 =	0;
	int	high =	0;
	GetGame().GetPlayerNetworkIDByIdentityID( sender.GetPlayerId(), low, high );
	return PlayerBase.Cast( GetGame().GetObjectByNetworkId(low, high ));
}

static int GetETPTimeStamp()
{
	int year, month, day, hour, minute, second;
	GetHourMinuteSecondUTC(hour, minute, second);
	GetYearMonthDayUTC(year, month, day);
	return JMDate.Timestamp(year,month,day,hour,minute,second);
}

class ExdecayTeleporterHelper
{
	static int GetCountdownByMapName(string name)
	{
		int index = GetMapArrayPositionByMapName(name);
		if(index != -1)
		return GetExdecayTeleporterConfig().Maps[index].Countdown;

		return -1;
	}

	static int GetMapArrayPositionByMapName(string name)
	{
		for(int i=0; i< GetExdecayTeleporterConfig().Maps.Count();i++)
		{
			if(GetExdecayTeleporterConfig().Maps[i].MapName == name)
			{
				return i;
			}
		}

		return -1;
	}

	static string GetPopulationImagePathBasedOnPlayerPopulation(int currentPopulation, int maxPopulation)
	{
		float coefficient = (currentPopulation*1.0)/(maxPopulation*1.0);

		if(coefficient == 1.0)
		{
			return "ExdecayTeleporter/gui/full.edds";
		}
		else if(coefficient < 1.0 && coefficient > 0.70)
		{
			return "ExdecayTeleporter/gui/high.edds";
		}
		else if(coefficient < 0.70 && coefficient > 0.40)
		{
			return "ExdecayTeleporter/gui/medium.edds";
		}
		else(coefficient < 0.40)
		{
			return "ExdecayTeleporter/gui/low.edds";
		}

		return "ExdecayTeleporter/gui/low.edds";
	}
}

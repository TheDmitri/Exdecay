enum ExdecayPlayerLocations
{
	MAINTRADER,
	FLATLANDS,
	RESORT,
	URBAN,
	BUNKERTRADER,
	INDUSTRIALTRADER
};
modded class PlayerBase
{
	override void OnPlayerLoaded()
	{
		super.OnPlayerLoaded();
		vector currPos = GetPosition();
		if ((currPos[0] > 34 && currPos[0] < 397) && (currPos[2] > 652 && currPos[2] < 1007))
			SetPosition("218.9 35 395.1");
	}
}

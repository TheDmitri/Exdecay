modded class MissionServer extends MissionBase
{
	void MissionServer()
	{
		/*we create the core class on server in order to have it working on server side*/
		m_YKCore = NULL;
		GetYKCore();
	}
};

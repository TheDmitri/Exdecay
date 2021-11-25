modded class PluginManager
{
	override void Init()
	{
		super.Init();
		RegisterPlugin( "PluginEZStatus",	true, 	false );
	}
};

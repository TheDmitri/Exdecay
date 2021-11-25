modded class PlayerBase extends ManBase
{
	bool IsExtracting;

	override void Init()
	{
		IsExtracting = false;
		super.Init();
	}
}

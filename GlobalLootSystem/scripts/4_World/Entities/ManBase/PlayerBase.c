modded class PlayerBase extends ManBase
{
	override void SetActions(out TInputActionMap InputActionMap)
	{
		super.SetActions(InputActionMap);
		AddAction(ActionGlobalLootSearchCrate, InputActionMap);
	}
};

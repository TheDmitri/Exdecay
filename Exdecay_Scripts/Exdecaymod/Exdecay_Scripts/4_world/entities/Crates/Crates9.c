class Ex_Dufflebag_red extends Container_Base
{
	override bool CanPutIntoHands( EntityAI parent )
	{
		return false;
	}
	override bool CanPutInCargo( EntityAI item )
	{
		return false;
	}
	
}
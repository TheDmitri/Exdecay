class Ex_Box extends Container_Base
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
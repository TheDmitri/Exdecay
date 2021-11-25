class CfgPatches
{
	class GlobalLootSystem_Script
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data",
			"DZ_Structures_Signs"
		};
	};
};
class CfgMods
{
	class GlobalLootSystem
	{
		dir="GlobalLootSystem";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="GlobalLootSystem";
		credits="TheDmitri";
		author="TheDmitri";
		authorID="0";
		version="1.1";
		extra=0;
		type="mod";
		dependencies[]=
		{
			"Game",
			"World",
			"Mission"
		};
		class defs
		{
			class gameScriptModule
			{
				value="";
				files[]=
				{
					"GlobalLootSystem/scripts/Common",
					"GlobalLootSystem/scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"GlobalLootSystem/scripts/Common",
					"GlobalLootSystem/scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"GlobalLootSystem/scripts/Common",
					"GlobalLootSystem/scripts/5_Mission"
				};
			};
		};
	};
};
class CfgVehicles
{
	class HouseNoDestruct;
	class GlobalLootSystemSign: HouseNoDestruct
	{
		scope=1;
		model="\DZ\structures\signs\misc\sign_rail_platformend.p3d";
	};
	class Paper;
	class GlobalLootSystemCreditCard: Paper
	{
		scope=2;
		displayName="$STR_credit_card";
		descriptionShort="$STR_credit_card_des";
    itemSize[] = {1,1};
    itemsCargoSize[] = {0,0};
		model="GlobalLootSystem\Data\money\Debit_Card.p3d";
	};
	class ReceiptBase: Paper
	{
		scope=2;
		displayName="$STR_car_receipt";
		descriptionShort="$STR_car_receipt_des";
		forceFarBubble="true";
		weight=1000;
		itemSize[]={1,1};
		ContinuousActions[]={999837};
		rotationFlags=0;
		itemBehaviour = 2;
		canBeDigged = 0;
		heavyItem = 1;
		physLayer = "item_large";
		bounding = "BSphere";
		carveNavmesh = 1;
		slopeTolerance = 0.2;
		yawPitchRollLimit[] = {12,12,12};
		placement = "ForceSlopeOnTerrain";
		canBeSplit=0;
		varQuantityInit=1;
		varQuantityMin=0;
		varQuantityMax=1;
		varQuantityDestroyOnMin=1;
		varStackMax=0;
		};
		class Receipt:ReceiptBase
		{
			scope=2;
			displayName="$STR_car_receipt";
			hiddenSelections[]=
			 {
					 "zbytek"
			 };
			 hiddenSelectionsTextures[]=
			 {
					 "GlobalLootSystem\images\loot_paperRcpt_co.paa"
			 };
		};
		class Wrench;
		class GlobalLootSystemWrench: Wrench
		{
			scope=2;
			displayName="$STR_packing_wrench";
			descriptionShort="$STR_packing_wrench_des";
		};
};
class CfgSoundShaders
{
	class GlobalLootSystem_Sound_Sell_SoundShader
	{
		samples[]=
		{

			{
				"GlobalLootSystem\sounds\SellSound",
				1
			}
		};
		volume=0.5;
		range=5;
	};
	class GlobalLootSystem_Sound_Buy_SoundShader
	{
		samples[]=
		{

			{
				"GlobalLootSystem\sounds\BuySound",
				1
			}
		};
		volume=0.5;
		range=5;
	};
};
class CfgSoundSets
{
	class GlobalLootSystem_Sound_Buy_SoundSet
	{
		soundShaders[]=
		{
			"GlobalLootSystem_Sound_Buy_SoundShader"
		};
		volumeFactor=1.4;
		volumeCurve="InverseSquare2Curve";
		spatial=1;
		doppler=1;
		loop=0;
		sound3DProcessingType="ExplosionMedium3DProcessingType";
		distanceFilter="explosionDistanceFreqAttenuationFilter";
	};
	class GlobalLootSystem_Sound_Sell_SoundSet
	{
		soundShaders[]=
		{
			"GlobalLootSystem_Sound_Sell_SoundShader"
		};
		volumeFactor=1.4;
		volumeCurve="InverseSquare2Curve";
		spatial=1;
		loop=0;
	};
};

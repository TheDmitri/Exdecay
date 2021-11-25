class CfgPatches
{
	class ExdecayTeleporter_Script
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]=
		{
			"DZ_Data"
		};
	};
};
class CfgMods
{
	class ExdecayTeleporter
	{
		dir="ExdecayTeleporter";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="ExdecayTeleporter";
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
					"ExdecayTeleporter/scripts/Common",
					"ExdecayTeleporter/scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"ExdecayTeleporter/scripts/Common",
					"ExdecayTeleporter/scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"ExdecayTeleporter/scripts/Common",
					"ExdecayTeleporter/scripts/5_Mission"
				};
			};
		};
	};
};
class CfgVehicles
{

};
class CfgSoundShaders
{
	class ExdecayTeleporter_Sound_Quick_Event_SoundShader
	{
		samples[]=
		{

			{
				"ExdecayTeleporter\sounds\quick_event",
				1
			}
		};
		volume=0.5;
		range=5;
	};
	class ExdecayTeleporter_Sound_Confirm_SoundShader
	{
		samples[]=
		{

			{
				"ExdecayTeleporter\sounds\confirm",
				1
			}
		};
		volume=0.5;
		range=5;
	};
};
class CfgSoundSets
{
	class ExdecayTeleporter_Sound_Quick_Event_SoundSet
	{
		soundShaders[]=
		{
			"ExdecayTeleporter_Sound_Quick_Event_SoundShader"
		};
		volumeFactor=1.4;
		volumeCurve="InverseSquare2Curve";
		spatial=1;
		doppler=1;
		loop=0;
		sound3DProcessingType="ExplosionMedium3DProcessingType";
		distanceFilter="explosionDistanceFreqAttenuationFilter";
	};
	class ExdecayTeleporter_Sound_Confirm_SoundSet
	{
		soundShaders[]=
		{
			"ExdecayTeleporter_Sound_Confirm_SoundShader"
		};
		volumeFactor=1.4;
		volumeCurve="InverseSquare2Curve";
		spatial=1;
		loop=0;
	};
};

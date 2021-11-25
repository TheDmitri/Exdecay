class CfgPatches
{
	class ExtractionZone_Script
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
	class ExtractionZone
	{
		dir="ExtractionZone";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="ExtractionZone";
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
					"ExtractionZone/scripts/Common",
					"ExtractionZone/scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"ExtractionZone/scripts/Common",
					"ExtractionZone/scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"ExtractionZone/scripts/Common",
					"ExtractionZone/scripts/5_Mission"
				};
			};
		};
	};
};

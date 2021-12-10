class CfgPatches
{
	class Yupikai_Script
	{
		units[]={};
		weapons[]={};
		requiredVersion=0.1;
		requiredAddons[]={};
	};
};
class CfgMods
{
	class Yupikai
	{
		dir="Yupikai";
		picture="";
		action="";
		hideName=1;
		hidePicture=1;
		name="Yupikai";
		credits="";
		author="";
		authorID="0";
		version="1.0";
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
					"Yupikai/scripts/3_Game"
				};
			};
			class worldScriptModule
			{
				value="";
				files[]=
				{
					"Yupikai/scripts/4_World"
				};
			};
			class missionScriptModule
			{
				value="";
				files[]=
				{
					"Yupikai/scripts/5_Mission"
				};
			};
		};
	};
};

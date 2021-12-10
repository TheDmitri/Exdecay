////////////////////////////////////////////////////////////////////
//DeRap: Exdecay_Scripts\config.bin
//Produced from mikero's Dos Tools Dll version 8.57
//https://mikero.bytex.digital/Downloads
//'now' is Fri Dec 10 11:57:19 2021 : 'file' last modified on Thu Jan 01 01:00:01 1970
////////////////////////////////////////////////////////////////////

#define _ARMA_

class CfgPatches
{
	class Exdecay_scripts
	{
		units[] = {};
		weapons[] = {};
		requiredVersion = 0.1;
		requiredAddons[] = {"DZ_Data"};
	};
};
class CfgMods
{
	class Exdecay
	{
		dir = "Exdecay";
		name = "Exdecay";
		credits = "";
		author = "Kaffeina";
		version = "1.0";
		extra = 0;
		type = "mod";
		dependencies[] = {"Game","World","Mission"};
		class defs
		{
			class gameScriptModule
			{
				files[] = {"Exdecaymod/Exdecay_Scripts/3_Game"};
			};
			class worldScriptModule
			{
				files[] = {"Exdecaymod/Exdecay_Scripts/4_World"};
			};
			class missionScriptModule
			{
				files[] = {"Exdecaymod/Exdecay_Scripts/5_Mission"};
			};
		};
	};
};

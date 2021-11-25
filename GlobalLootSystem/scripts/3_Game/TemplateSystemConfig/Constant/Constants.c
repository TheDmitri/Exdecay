const string GLS_CONFIG_ROOT_SERVER = "$profile:GlobalLootSystem\\";
const string GLS_LOGGER_DIR_SERVER = GLS_CONFIG_ROOT_SERVER + "GLSLogs\\";
const string GLS_LOGGER_PREFIX_SERVER = "GlobalLootSystem_";
const string GLS_CONFIG_DIR_SERVER = GLS_CONFIG_ROOT_SERVER + "GLSConfig\\";
const string GLS_SPAWNABLETYPES_CONFIG = GLS_CONFIG_DIR_SERVER + "SpawnableTypesSettings.json";
const string GLS_RANDOMPRESETS_CONFIG = GLS_CONFIG_DIR_SERVER + "RandomPresetsSettings.json";
const string GLS_ATTACHMENTS_CONFIG = GLS_CONFIG_DIR_SERVER + "AttachmentsSettings.json";

static ref TStringArray SearchableCrates = {
  "Ex_Utility_static",
  "Ex_suitcase_static",
  "Ex_Safelocker_static",
  "Ex_Cargo_crate_static",
  "Ex_Box_static",
  "Ex_Dufflebag_red_static",
  "Ex_Barrels_static",
  "Ex_FirstAid_static",
  "Ex_toolbox_red_static",
  "Ex_crate_mil_1_static",
  "Ex_Crate_mil_SMALL1_static",
  "Ex_Crate_long_static",
  "Ex_Crate_small_static",
  "Ex_Crate_square_static"
}

static ref TStringArray ToolsCrates = {
  "Screwdriver",
  "Screwdriver",
  "Crowbar",
  "Crowbar",
  "Knife",
  "Knife",
  "Screwdriver",
  "Screwdriver",
  "Screwdriver",
  "Crowbar",
  "Crowbar",
  "Crowbar",
  "Crowbar",
  "Crowbar"
}

static ref TIntArray ActionLoopingDelay = {
  6,
  6,
  26,
  16,
  6,
  8,
  8,
  6,
  6,
  16,
  8,
  8,
  8,
  8,
}

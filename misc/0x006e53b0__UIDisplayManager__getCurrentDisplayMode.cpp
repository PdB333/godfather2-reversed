// FUNC_NAME: UIDisplayManager::getCurrentDisplayMode
// Function at 0x006e53b0 - Retrieves current display mode/configuration based on some system state
// Returns one of 4 display modes via param_3 (output pointer)
void getCurrentDisplayMode(undefined4 param_1, undefined4 param_2, undefined4 *outputMode)

{
  undefined4 currentState;
  
  currentState = getSystemState(); // FUN_00806440 - gets current system/UI state
  
  switch(currentState) {
  case 0: // MENU_STATE_MAIN
    *outputMode = 0; // e.g. DISPLAY_MODE_1080I
    return;
  case 1: // MENU_STATE_OPTIONS
    *outputMode = _DAT_00d5780c; // some config value at +0x0c
    return;
  case 2: // MENU_STATE_CREDITS
    *outputMode = DAT_00d5eee4; // some config value at 0x00d5eee4
    return;
  case 3: // MENU_STATE_LOADING
    *outputMode = DAT_00e445ac; // some config value at 0x00e445ac
    return;
  default:
    *outputMode = 0;
    return;
  }
}
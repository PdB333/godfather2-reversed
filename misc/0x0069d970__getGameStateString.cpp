// FUNC_NAME: getGameStateString
const char** getGameStateString(int stateIndex)
{
  const char** stateStrings[4];
  const char* strings[8];
  
  if (stateIndex == 9) {
    stateIndex = getDefaultGameState(); // FUN_0069d8a0
  }
  
  // Array of string pointers for game states
  stateStrings[0] = (const char**)&DAT_00d5a340; // "MainMenu"
  stateStrings[1] = &PTR_LAB_00d5a32c;          // "Playing"
  stateStrings[2] = &PTR_DAT_00d5a30c;          // "Paused"
  stateStrings[3] = &PTR_DAT_00d5a2f0;          // "Loading"
  
  strings[0] = &DAT_00d5a2d0;                   // "Cutscene"
  strings[1] = &DAT_00d5a2a4;                   // "Dialog"
  strings[2] = &DAT_00d5a280;                   // "Menu"
  strings[3] = &DAT_00d5a260;                   // "Transition"
  strings[4] = &DAT_00d5a23c;                   // "Unknown"
  
  return stateStrings[stateIndex];
}
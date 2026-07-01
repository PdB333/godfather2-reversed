// FUNC_NAME: GameStateManager::processMessage
void GameStateManager::processMessage(int param_1) // param_1 likely points to a message struct at +0xC for messageType
{
  undefined4 varOut;
  undefined4 *messageBuffer; // unaff_EDI likely points to a buffer for response messages
  
  // Switch on message type at offset +0xC
  switch(*(undefined4 *)(param_1 + 0xc)) {
  case 0x7b: // 123 - likely MSG_PLAY_INTRO_CUTSCENE or similar
    FUN_0063ec10(param_1); // handles intro sequence
    return;
  default:
    FUN_0063f4f0(param_1); // default message handler
    return;
  case 0x107: // 263 - likely MSG_REQUEST_MAIN_MENU_STATE
    // Set up main menu state request
    messageBuffer[3] = 0xffffffff; // invalid/clear target
    messageBuffer[4] = 0xffffffff; // invalid/clear source
    *messageBuffer = 3;           // state = 3 (main menu)
    messageBuffer[1] = 0;         // substate = 0
    FUN_0063db50();               // send response/state change request
    return;
  case 0x109: // 265 - likely MSG_LOAD_SAVED_GAME
    FUN_0063db50();               // acknowledge
    FUN_0063f080();               // load saved game data
    return;
  case 0x10d: // 269 - likely MSG_LOAD_CHAPTER
    // Set up chapter load state
    messageBuffer[3] = 0xffffffff;
    messageBuffer[4] = 0xffffffff;
    *messageBuffer = 1;           // state = 1 (loading chapter)
    messageBuffer[1] = 0;
    FUN_0063db50();
    return;
  case 0x113: // 275 - likely MSG_REQUEST_INGAME_STATE
    messageBuffer[3] = 0xffffffff;
    messageBuffer[4] = 0xffffffff;
    *messageBuffer = 2;           // state = 2 (in-game)
    messageBuffer[1] = 0;
    FUN_0063db50();
    return;
  case 0x11d: // 285 - likely MSG_INIT_NEW_GAME
    varOut = FUN_00642a70();      // get current save slot count or similar
    messageBuffer[3] = 0xffffffff;
    messageBuffer[4] = 0xffffffff;
    *messageBuffer = 4;           // state = 4 (new game init)
    messageBuffer[1] = varOut;    // store slot count
    FUN_0063db50();
    return;
  case 0x11e: // 286 - likely MSG_START_NEW_GAME
    FUN_0063ddc0();               // finalize new game setup
    FUN_0063db50();
    return;
  }
}
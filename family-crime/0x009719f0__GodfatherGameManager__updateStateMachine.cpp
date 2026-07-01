// FUNC_NAME: GodfatherGameManager::updateStateMachine
void __fastcall GodfatherGameManager::updateStateMachine(GodfatherGameManager* thisPtr)
{
  StateType state;
  char localBuf[80]; // stack buffer for saving/restoring state
  
  FUN_00982c90(); // possibly some pre-update audio or input?
  (**(code **)(*thisPtr + 8))(); // call virtual function at vtable+8 (e.g., onFrameStart)

  // Check if global game manager pointer is valid and its sub-object at +0xC is non-null
  if ((DAT_01223484 != 0) && (*(int*)(DAT_01223484 + 0xC) != 0)) {
    state = thisPtr->currentState; // at offset 0xDC (int)
    thisPtr->flagByte1 = 0; // +0x88
    thisPtr->flagByte2 = 0; // +0x221

    if (state == STATE_MAIN_MENU) { // 1
      FUN_00967d70(1); // probably set some volume or enable music
      thisPtr->flagByte2 = 1;
      FUN_0096cda0(1); // enable something
      FUN_00962740();  // clear/reset something
      FUN_00969880(localBuf); // save current state/stack to localBuf
      FUN_00964580(localBuf); // restore from localBuf (or vice versa)
      FUN_005a04a0("PushHistory", 0, &DAT_00d8cdec, 0); // log push history
      FUN_00970f10(); // possibly load save data or transition to game
    }
    else if ((state == STATE_INGAME) || (state == STATE_PAUSE)) { // 6 or 8
      FUN_0096cda0(0); // disable something
      FUN_008a2dd0(0, 3, 0, 0, 0); // some UI/setup call
      // Zero out local stack variables
      localVar1 = 0;
      localVar2 = 0;
      localVar3 = 0;
      localVar4 = 0;
      localVar5 = 0;
      FUN_00969880(localBuf);
      FUN_00964580(localBuf);
      FUN_005a04a0("PushHistory", 0, &DAT_00d8cdec, 0);
      FUN_0096cd00(); // possibly transition to main menu
    }
  }

  // Reset previous state fields and clear a flag
  thisPtr->previousState = -1; // +0x1A0 (int at 0x68*4)
  thisPtr->previousPreviousState = -1; // +0x19C (int at 0x67*4)
  thisPtr->flags &= ~0x2; // +0x6F4 (int at 0x1BD*4), clear bit 1

  (**(code **)(*thisPtr + 8))(); // call virtual function again (e.g., onFrameEnd)
}
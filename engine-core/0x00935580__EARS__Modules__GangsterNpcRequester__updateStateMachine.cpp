// FUNC_NAME: EARS::Modules::GangsterNpcRequester::updateStateMachine
void __thiscall GangsterNpcRequester::updateStateMachine(undefined4 param_1, char *param_2)
{
  code *pcVar1;
  int *piVar2;
  char cVar3;
  int iStack_4;
  
  piVar2 = DAT_01129928; // Global NPC manager pointer
  pcVar1 = *(code **)(*DAT_01129928 + 8); // vtable offset for update method
  DAT_01129928[0x25] = 0; // Clear some flag at +0x94
  (*pcVar1)(); // Call base update method
  
  if (DAT_01130544 != 3) { // Current state check (STATE_COMPLETED=3)
    DAT_01130544 = 2; // Set to STATE_PROCESSING=2
    cVar3 = FUN_00adc2d0(); // Check if request queue has pending items
    if (cVar3 == '\0') { // No pending requests
      FUN_00ae0ad0(param_1); // Process current request
      if (iStack_4 != 0) { // Request completed successfully
        DAT_01130544 = 1; // Set to STATE_IDLE=1
        *(undefined1 *)(DAT_01129908 + 0x18) = 1; // Set request completion flag at +0x18
        FUN_00935500(1); // Notify observers about completion
      }
    }
    if ((param_2 != (char *)0x0) && (*param_2 != '\0')) { // Error string provided
      FUN_00982c90(); // Log or handle error
      return;
    }
    DAT_01130544 = 0; // Set to STATE_INITIALIZED=0
    DAT_00e5672c = 0x11; // Some global state/error code
    piVar2[0x18] = 0; // Clear request count at +0x60
    if ((DAT_01130590 & 1) == 0) { // First-time initialization check
      FUN_005c0d50(piVar2 + 5, &LAB_00931e00, 0); // Register callback for idle state
      DAT_01130590 = DAT_01130590 | 1; // Mark initialization done
    }
  }
  return;
}
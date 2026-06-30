// FUNC_NAME: BaseVehicle::updateDrivingState
undefined1 __fastcall BaseVehicle::updateDrivingState(int thisPtr)

{
  int iVar1;
  bool bVar2;
  undefined4 uVar3;
  code *pcVar4;
  int iVar5;
  undefined1 local_6;
  undefined4 local_4;
  
  iVar1 = *(int *)(thisPtr + 0x480); // +0x480: previousDrivingState
  uVar3 = 0;
  pcVar4 = (code *)0x0;
  local_6 = 1;
  bVar2 = false;
  local_4 = 0;
  iVar5 = 8;
  if (*(int *)(thisPtr + 0x484) != iVar1) { // +0x484: currentDrivingState
    // Get from global driving state table
    iVar1 = *(int *)(&DAT_00e2b0a0 + (*(int *)(thisPtr + 0x484) + iVar1 * 4 + iVar1) * 4);
    if (iVar1 == 0) {
      local_6 = 0;
    }
    else {
      iVar5 = 8;
      if (iVar1 != 8) {
        // Store state transition callback and data for later execution
        pcVar4 = *(code **)(thisPtr + 0x210); // +0x210: stateTransitionCallback
        uVar3 = *(undefined4 *)(thisPtr + 0x27c); // +0x27c: transitionParam1
        bVar2 = true;
        local_4 = *(undefined4 *)(thisPtr + 0x278); // +0x278: transitionParam2
        iVar5 = iVar1;
        if (iVar1 == 3) {
          // Special handling for driving state 3 (e.g., entering/exiting vehicle)
          FUN_005dbc10(); // Probably some vehicle state cleanup
          if (*(int *)(thisPtr + 0x1fc) == 0) {
            FUN_005dbc10(); // Additional cleanup
            FUN_005e9520(); // Vehicle state update
            FUN_005e8690(); // Animation/handling update
          }
        }
      }
    }
    // Update previous state to current state
    *(undefined4 *)(thisPtr + 0x480) = *(undefined4 *)(thisPtr + 0x484);
    if (bVar2) {
      if (pcVar4 != (code *)0x0) {
        // Execute state transition callback
        (*pcVar4)(uVar3,iVar5,local_4);
      }
      // Notify driving state manager
      FUN_005e25a0(DAT_0122350c,uVar3,iVar5);
    }
    return local_6;
  }
  return 1;
}
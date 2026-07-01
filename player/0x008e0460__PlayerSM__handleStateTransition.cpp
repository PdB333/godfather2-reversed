// FUNC_NAME: PlayerSM::handleStateTransition
void __thiscall PlayerSM::handleStateTransition(int thisPtr, char param_2)

{
  char cVar1;
  float10 fVar2;
  undefined **local_18;
  int local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined ***local_8;
  undefined1 local_4;
  
  *(undefined4 *)(thisPtr + 0x230) = 0xffffffff; // +0x230: stateTimer = -1 (reset)
  *(undefined4 *)(thisPtr + 0x22c) = 1;          // +0x22c: stateFlags |= 1 (entering state)
  fVar2 = (float10)FUN_008dab60();               // getCurrentTime()
  FUN_008de620(*(undefined4 *)(thisPtr + 0x234),(float)fVar2); // setStateStartTime(stateStartTime, time)
  if (*(int *)(thisPtr + 0x248) != 0) {          // +0x248: pendingTransition
    cVar1 = FUN_00481620();                      // isGamePaused()?
    if (cVar1 != '\\0') {
      local_14 = thisPtr + 0x48;                 // +0x48: some list/array
      local_18 = &PTR_FUN_00e31e2c;              // vtable pointer for callback
      local_10 = 0;
      if (local_14 != 0) {
        local_10 = *(undefined4 *)(thisPtr + 0x4c); // +0x4c: previous list head
        *(int **)(thisPtr + 0x4c) = &local_14;      // link new node
      }
      local_c = *(undefined4 *)(thisPtr + 0x248); // pendingTransition
      local_8 = &local_18;
      local_4 = 0;
      FUN_00408a00(&local_c,0);                  // executeTransition(pendingTransition, 0)
      if (local_14 != 0) {
        FUN_004daf90(&local_14);                 // cleanupList(local_14)
      }
    }
  }
  if (param_2 != '\\0') {
    (**(code **)(*(int *)(thisPtr + 0x58) + 0x28))(0x40); // call vtable+0x28 with flag 0x40
    (**(code **)(*(int *)(thisPtr + 0x58) + 0x28))(0x80); // call vtable+0x28 with flag 0x80
    FUN_008dfd20();                              // updateAnimation()
    return;
  }
  FUN_008de4d0(0);                               // updateStateMachine(0)
  FUN_008dfd20();                                // updateAnimation()
  return;
}
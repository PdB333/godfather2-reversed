// FUNC_NAME: StreamManager::updateLoadingState
void __thiscall StreamManager::updateLoadingState(uint this, int newState)

{
  int *globalStatePtr;
  int *objectPtr;
  
  globalStatePtr = DAT_012234d8;
  if (*(int *)(DAT_012234d8 + 0xc) == 5) {
    *(int *)(DAT_012234d8 + 0xc) = newState;
    if (*(int *)(globalStatePtr + 0xc) == 5) {
      *(int *)(globalStatePtr + 4) = 5;
    }
    else {
      *(int *)(globalStatePtr + 4) = *(int *)(globalStatePtr + 0xc);
    }
  }
  if (DAT_01223484[3] != 0) {
    // Call virtual function at offset 0x80 (likely some update or handler)
    (*(code **)(*DAT_01223484[3] + 0x80))();
    objectPtr = DAT_01223484 + 3;
    if (DAT_01223484[3] != 0) {
      // Call destructor/virtual destructor
      (*(code **)(*(int *)DAT_01223484[3]))();
      *objectPtr = 0;
    }
  }
  if (*(int *)(this + 0xc) != 0) {
    int vtableResult = (*(code **)(**(int **)(this + 0xc) + 8))();  // GetStateFunction?
    if (vtableResult == 5) {
      FUN_00568410();  // likely completes transition
      return;
    }
    if ((*(int *)(this + 0xc) != 0) &&
       (vtableResult = (*(code **)(**(int **)(this + 0xc) + 8))(), vtableResult != 0)) {
      return;
    }
  }
  *(uint *)(this + 0x2c) = *(uint *)(this + 0x2c) | 0x400;
  return;
}
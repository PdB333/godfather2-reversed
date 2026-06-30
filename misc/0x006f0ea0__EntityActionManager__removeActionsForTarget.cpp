// FUNC_NAME: EntityActionManager::removeActionsForTarget
void __thiscall EntityActionManager::removeActionsForTarget(int thisPtr, int targetId)
{
  int *entryPtr;
  int *currentPtr;
  uint index;
  int actionPtr;
  
  // Process the first list: 5 entries (size 0x2c) starting at this+0x64
  int *listBase = *(int **)(thisPtr + 0x64);
  if (listBase != 0) {
    for (index = 0; index < 0xdc; index += 0x2c) {
      // Each entry: +0x00 = action pointer, +0x18 = target ID
      if (*(int *)(index + 0x18 + (int)listBase) == targetId) {
        actionPtr = *(int *)(index + (int)listBase);
        if (actionPtr != 0) {
          // Cancel the action and update state
          Utils::cancelAction(0, actionPtr);    // FUN_006fc4c0
          Utils::updateState();                 // FUN_006f7300
        }
      }
    }
  }
  
  // Process the second list: 2 entries (size 0x20) at this+0x30
  currentPtr = (int *)(thisPtr + 0x30);
  for (int i = 0; i < 2; i++) {
    entryPtr = (int *)*currentPtr;              // pointer to action object
    if (entryPtr != 0) {
      if (*(int *)((int)entryPtr + 0x18) == targetId) {
        // Cancel and update
        Utils::cancelAction(0, (int)entryPtr);         // FUN_006fc4c0
        Utils::updateState();                          // FUN_006f7300
        
        // Check flags (bit 0x20) and a second pointer
        if ((currentPtr[-1] != 0) && ((*(byte *)(currentPtr + 4) & 0x20) != 0) && (currentPtr[2] != 0)) {
          Utils::freeSomething(currentPtr[3]);          // FUN_00815060
        }
        
        // Clear all fields in the entry
        *(int *)((int)entryPtr + 0x18) = 0;
        *(int *)((int)entryPtr + 0x14) = 0;
        *currentPtr = 0;                  // pointer to action object
        currentPtr[1] = 0;                // +4
        currentPtr[-1] = 0;               // -4 (previous field)
        currentPtr[2] = 0;                // +8
        currentPtr[3] = 0;                // +12
      }
    }
    currentPtr += 8;                     // move to next entry (32 bytes)
  }
}
// FUNC_NAME: Character::canStartAction
uint __thiscall Character::canStartAction(int thisPtr)
{
  char isGameActive;
  int *managerPtr;
  uint actionResult;
  uint vtableResult;
  uint bitField;
  uint comparisonValue;
  
  isGameActive = FUN_008a4380(); // Check if gameplay is active (e.g., not in menu)
  if (isGameActive != '\0') {
    // Gameplay active path
    if (thisPtr == 0) {
      managerPtr = (int *)0x0;
    }
    else {
      managerPtr = (int *)FUN_0043b870(DAT_01131018); // Get some global manager (e.g., PlayerManager)
    }
    vtableResult = (**(code **)(*managerPtr + 0x34))(); // Call virtual function at offset 0x34 (e.g., getLocalCharacter)
    if ((vtableResult == 0) ||
       ((*(uint *)(vtableResult + 0x3c) != *(uint *)(thisPtr + 0x68c) >> 2 &&
        ((*(uint *)(vtableResult + 0x44) >> 6 & 1) == 0)))) {
      // Either no result or conditions indicate action not blocked by interaction
      if (FUN_007f8f10() == '\0') { // Check if character is alive (returns 0 = dead?)
        bitField = *(uint *)(thisPtr + 0x24a4);
        if (((bitField >> 0xb) & 1) == 0) { // Check if some flag allows action (e.g., not in scripted state)
          return ((bitField >> 0x13) << 8) | 1; // Return success with upper bits from flag
        }
      }
    }
    return vtableResult & 0xffffff00; // Mask off low byte (indicates failure)
  }
  // Gameplay not active (e.g., in menus/cutscenes)
  if (FUN_007f7c60() == '\0') { // Check if not in cutscene/dialog
    if (FUN_007f8f10() == '\0') { // Check if alive
      bitField = *(uint *)(thisPtr + 0x24a4);
      if (((bitField >> 0xb) & 1) == 0) { // Check flag
        return FUN_007eb750(thisPtr); // Call alternative handler (e.g., scene specific action)
      }
    }
  }
  return 0; // Default failure (original code used uVar3 which may be uninitialized; assume 0)
}
// FUNC_NAME: SceneManager::updateActiveChildren
void __fastcall SceneManager::updateActiveChildren(int thisPtr)
{
  int count;
  int **arrayPtr;
  
  // Check if update flag is already set (bit 0x2000000) and that children array exists at +0xAC
  if (((*(uint *)(thisPtr + 0x5c) >> 0x19 & 1) == 0) && (*(int *)(thisPtr + 0xac) != 0)) {
    // Set the "updating" flag to prevent re-entrance
    *(uint *)(thisPtr + 0x5c) = *(uint *)(thisPtr + 0x5c) | 0x2000000;
    
    // Read count from the child array structure at +0xAC: +0 is base pointer, +4 is count
    count = *(int *)(*(int *)(thisPtr + 0xac) + 4);
    while (count = count + -1, -1 < count) {
      // Get pointer to child object
      arrayPtr = *(int ***)(**(int **)(thisPtr + 0xac) + count * 4);
      if (arrayPtr != (int **)0x0) {
        // Call virtual function at vtable offset 0x10 (4th function, likely update)
        (**(code **)(*arrayPtr + 0x10))(thisPtr);
      }
    }
    // Post-update hook
    FUN_007909d0();
    return;
  }
  return;
}
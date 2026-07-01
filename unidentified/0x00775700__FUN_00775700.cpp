// FUNC_NAME: SomeClass::checkAndProcessState
void __fastcall SomeClass::checkAndProcessState(int thisPtr)
{
  int iVar1;
  
  // Check if state pointer at +0x5c is non-null and not equal to 0x48
  if ((*(int *)(thisPtr + 0x5c) != 0) && (*(int *)(thisPtr + 0x5c) != 0x48)) {
    // Compute offset from state pointer
    if (*(int *)(thisPtr + 0x5c) == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(thisPtr + 0x5c) + -0x48;
    }
    // Check bit 1 of flags at +0xe8 (offset from computed base)
    if ((*(unsigned int *)(iVar1 + 0xe8) >> 1 & 1) == 0) {
      // If bit not set, call processing function
      if (*(int *)(thisPtr + 0x5c) != 0) {
        FUN_00725fc0();
        return;
      }
      FUN_00725fc0();
      return;
    }
  }
  return;
}
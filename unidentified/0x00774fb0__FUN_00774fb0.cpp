// FUNC_NAME: SomeClass::setSomeFlagOrState
void __fastcall SomeClass::setSomeFlagOrState(int thisPtr)
{
  // Check if bit 5 of the flags at offset +0x64 (100 decimal) is already set
  if ((*(uint *)(thisPtr + 100) >> 5 & 1) == 0) {
    // Set bit 5 of the flags at offset +0x64
    *(uint *)(thisPtr + 100) = *(uint *)(thisPtr + 100) | 0x20;
    // Check the value at offset +0x5c - if non-zero and not 0x48, call FUN_007251a0
    if ((*(int *)(thisPtr + 0x5c) != 0) && (*(int *)(thisPtr + 0x5c) != 0x48)) {
      if (*(int *)(thisPtr + 0x5c) != 0) {
        FUN_007251a0();
        return;
      }
      FUN_007251a0();
      return;
    }
  }
  return;
}
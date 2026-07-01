// FUNC_NAME: SomeClass::releaseOrUnlockSomething
void __fastcall SomeClass::releaseOrUnlockSomething(int thisPtr)
{
  // Check flags at +0x30 and +0x32 (likely bitfield or state flags)
  if (((*(byte *)(thisPtr + 0x30) & 1) != 0) || ((*(byte *)(thisPtr + 0x32) & 1) != 0)) {
    // Call some release/cleanup function (likely decrement refcount or free resource)
    FUN_004b7010();
    // Check bit 1 of the dword at +0x30 (second bit)
    if (((*(uint *)(thisPtr + 0x30) >> 1 & 1) != 0) && (*(int *)(thisPtr + 0x38) != 0)) {
      // Call a function with pointer to +0x2c (likely a handle or pointer field)
      FUN_009f1b20(thisPtr + 0x2c);
      // Clear bit 1 of the flags at +0x30
      *(uint *)(thisPtr + 0x30) = *(uint *)(thisPtr + 0x30) & 0xfffffffd;
    }
  }
  return;
}
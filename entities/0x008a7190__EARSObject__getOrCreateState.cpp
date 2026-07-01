// FUNC_NAME: EARSObject::getOrCreateState
int __fastcall EARSObject::getOrCreateState(int thisPtr)
{
  // +0x64: state pointer field (0x100 bytes allocated)
  // +0x74: allocation size parameter for state object
  if (*(int *)(thisPtr + 100) == 0) {
    // If state not yet allocated, allocate and construct it
    FUN_00603330(*(undefined4 *)(thisPtr + 0x74), thisPtr + 0x60);
  }
  return thisPtr + 0x60;
}
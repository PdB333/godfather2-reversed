// FUNC_NAME: UnknownClass::initFromParam
void __thiscall UnknownClass::initFromParam(int thisPtr, uint param2)
{
  int allocationResult;
  uint handle;

  allocationResult = allocateMemory(0x340); // size 0x340 for some structure
  if (allocationResult != 0) {
    handle = getResourceHandle(param2); // convert or obtain handle
    *(uint *)(thisPtr + 8) = handle;    // +0x8: resource handle
    *(int *)(thisPtr + 0x10) = 5;       // +0x10: status code (5 = ready)
    return;
  }
  *(int *)(thisPtr + 0x10) = 5;          // +0x10: set to ready even on failure? Possibly placeholder
  *(uint *)(thisPtr + 8) = 0;            // +0x8: null handle
  return;
}
// FUNC_NAME: SomeMgr::checkHandleType
uint __fastcall SomeMgr::checkHandleType(int thisPtr)
{
  int field8 = *(int *)(thisPtr + 8); // +0x08: type/size field
  if ((field8 != 0) && (field8 != 0x48)) { // 0x48 = 72 (likely a known object size)
    uint result = sub_79e970(); // helper to resolve or create handle
    return result;
  }
  // return original EAX with low byte masked (likely a stripped handle or alignment)
  uint originalEax;
  return originalEax & 0xFFFFFF00;
}
// FUNC_NAME: INetObject::isLocalAuthority
uint __fastcall INetObject::isLocalAuthority(void) {
  int* pSessionPtr;
  int sessionBase;
  uint uRet;
  uint uTemp;
  uint* piSubObj;
  uint uResult;
  int dummy;

  pSessionPtr = *(int**)(DAT_012233a0 + 4);  // global singleton pointer to session manager
  if (pSessionPtr == 0) {
    sessionBase = 0;
  } else {
    sessionBase = (int)pSessionPtr - 0x1f30;  // get base of NetSession from embedded offset
  }

  uRet = CONCAT31((int3)((uint)pSessionPtr >> 8), 1);  // packed ID (low byte = 1 = local)

  if (sessionBase != 0 && (*(byte*)(sessionBase + 0x8e6) & 1) != 0) {
    uTemp = *(uint*)(this + 0x10);  // pointer to sub-object (or interface)
    if (uTemp == 0 || (uTemp = uTemp - 0x48, uTemp == 0)) {
      uResult = 0;
    } else {
      if (*(int*)(this + 0x10) == 0) {
        piSubObj = 0;
      } else {
        piSubObj = (uint*)(*(int*)(this + 0x10) - 0x48);  // adjust to base of embedded object
      }
      uTemp = 0x55859efa;  // magic GUID for local authority check
      dummy = 0;
      // virtual call to check if this object has local authority
      char c = (**(char(__fastcall**)(uint, int*))*piSubObj + 0x10)(0x55859efa, &dummy);
      uTemp = (uint)(c != 0) * 0x55859efa;  // if true, keep the GUID
      uResult = uTemp;
    }
    uRet = uTemp & 0xffffff00;  // clear low byte
    if (uResult != 0 && (*(byte*)(uResult + 0x8e6) & 1) != 0) {
      uRet = CONCAT31((int3)(uTemp >> 8), 1);  // pack with low byte = 1
    }
  }
  return uRet;
}
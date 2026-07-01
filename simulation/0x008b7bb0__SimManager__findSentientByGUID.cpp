// FUNC_NAME: SimManager::findSentientByGUID
uint __thiscall SimManager::findSentientByGUID(int thisPtr, int *guid)
{
  int *piVar1;
  uint uVar2;
  
  uVar2 = 0xffffffff;
  if (*(uint *)(thisPtr + 0x508) != 0) {
    piVar1 = (int *)(thisPtr + 0x14);
    uVar2 = 0;
    while ((((piVar1[-2] != *guid || (piVar1[-1] != guid[1])) || (*piVar1 != guid[2])) ||
           (piVar1[1] != guid[3]))) {
      uVar2 = uVar2 + 1;
      piVar1 = piVar1 + 5;
      if (*(uint *)(thisPtr + 0x508) <= uVar2) {
        return 0xffffffff;
      }
    }
  }
  return uVar2;
}
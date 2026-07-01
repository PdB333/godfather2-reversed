// FUNC_NAME: PlayerSM::setIsInCombat
void __thiscall PlayerSM::setIsInCombat(int thisPtr, undefined4 param_2)
{
  int iVar1;
  
  if ((*(byte *)(thisPtr + 0x5f) & 1) != (byte)param_2) {
    if ((byte)param_2 == 0) {
      *(uint *)(thisPtr + 0x5c) = *(uint *)(thisPtr + 0x5c) & 0xfeffffff;
    }
    else {
      *(uint *)(thisPtr + 0x5c) = *(uint *)(thisPtr + 0x5c) | 0x1000000;
    }
    if ((((*(int *)(thisPtr + 200) != 0) && (2 < *(int *)(thisPtr + 0xd0))) &&
        (*(int *)(thisPtr + 0xb0) == 3)) &&
       (((*(uint *)(thisPtr + 0x5c) >> 2 & 1) == 0 && ((*(uint *)(thisPtr + 0x5c) >> 6 & 1) == 0))))
    {
      iVar1 = FUN_007915b0();
      if (iVar1 != 0) {
        FUN_008c1f50(thisPtr,param_2);
      }
    }
  }
  return;
}
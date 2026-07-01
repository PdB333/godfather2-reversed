// FUNC_NAME: PlayerSM::updateState
void __fastcall PlayerSM::updateState(int thisPtr)
{
  int iVar1;
  int iVar2;
  undefined4 uVar3;
  
  iVar1 = FUN_004461c0(thisPtr + 0x7c,0);
  if (iVar1 != 0) {
    FUN_0078fed0(iVar1);
    FUN_0078ff60(iVar1);
  }
  iVar2 = FUN_008c7510(*(undefined4 *)(thisPtr + 200));
  *(int *)(thisPtr + 0xb0) = iVar2;
  if (*(int *)(thisPtr + 200) == 0x637b907) {
    if (*(int *)(thisPtr + 0xd0) < 3) goto LAB_00791c17;
    if ((iVar2 == 3) && ((*(uint *)(thisPtr + 0x5c) >> 2 & 1) == 0)) {
      *(uint *)(thisPtr + 0x5c) = *(uint *)(thisPtr + 0x5c) | 0x40;
    }
  }
  if ((((2 < *(int *)(thisPtr + 0xd0)) && (*(int *)(thisPtr + 0xb0) == 3)) &&
      ((*(uint *)(thisPtr + 0x5c) >> 2 & 1) == 0)) && ((*(uint *)(thisPtr + 0x5c) >> 6 & 1) == 0)) {
    iVar2 = FUN_007915b0();
    if (iVar2 != 0) {
      FUN_008c5460(thisPtr);
      if (*(int *)(thisPtr + 200) == 0x637b907) {
        uVar3 = FUN_00790000(iVar1);
        FUN_0090b750(thisPtr,uVar3);
      }
    }
  }
LAB_00791c17:
  FUN_00792d80(thisPtr);
  return;
}
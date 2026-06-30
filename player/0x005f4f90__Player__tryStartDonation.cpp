// FUNC_NAME: Player::tryStartDonation
undefined1 __thiscall Player::tryStartDonation(int thisPtr, int param_2)

{
  int iVar1;
  int iVar2;
  int *piVar3;
  undefined1 local_11;
  float local_10 [2];
  float fStack_8;
  
  local_11 = 0;
  iVar1 = 0;
  piVar3 = (int *)(thisPtr + 0x82b0);
  do {
    if ((-1 < *piVar3) && (*piVar3 == param_2)) goto LAB_005f4fc3;
    iVar1 = iVar1 + 1;
    piVar3 = piVar3 + 0x5c;
  } while (iVar1 < 10);
  iVar1 = -1;
LAB_005f4fc3:
  if ((*(int *)(thisPtr + 0x580) != 0) && (-1 < iVar1)) {
    iVar1 = iVar1 * 0x170 + 0x8210 + thisPtr;
    if (*(int *)(*(int *)(iVar1 + 0x9c) * 0x10 + 0x81c4 + thisPtr) != 0) {
      iVar2 = FUN_005e9d10();
      FUN_00c9cbe0(*(undefined4 *)(thisPtr + 0x580),*(undefined4 *)(iVar2 + 0x10),2,local_10);
      FUN_00ab4db0(&DAT_00e2aea0);
      local_10[0] = *(float *)(iVar1 + 0x134);
      if ((*(int *)(iVar1 + 0xf8) == 0) && (DAT_00e2b05c <= local_10[0])) {
        FUN_00c9eac0();
        FUN_00c9cd40(2,local_10);
        FUN_00c9eae0();
        local_11 = 1;
        if (fStack_8 != DAT_00e2b05c) {
          local_11 = 0;
        }
      }
      FUN_00ab4e70();
      return local_11;
    }
    return 0;
  }
  return 0;
}
// FUNC_NAME: LuaBinding::getNextKey
uint LuaBinding::getNextKey(int param_2)
{
  int iVar1;
  int *in_EAX;
  undefined4 *puVar2;
  int iVar3;
  undefined4 *extraout_ECX;
  
  iVar1 = *in_EAX;
  if (iVar1 == 0) {
    return 0xffffffff;
  }
  if ((((iVar1 == 3) && (iVar3 = (int)(float)in_EAX[1], (float)iVar3 == (float)in_EAX[1])) &&
      (0 < iVar3)) &&
     ((((iVar3 - 1U & 0xff000000) == 0 && (-1 < iVar3)) && (iVar3 <= *(int *)(param_2 + 0x1c))))) {
    return iVar3 - 1U;
  }
  if (iVar1 == 3) {
    if ((float)(int)(float)in_EAX[1] == (float)in_EAX[1]) {
      puVar2 = (undefined4 *)FUN_00637f10();
      goto LAB_00637617;
    }
  }
  else if (iVar1 == 4) {
    puVar2 = (undefined4 *)FUN_00637f90();
    goto LAB_00637617;
  }
  puVar2 = (undefined4 *)FUN_00637ea0();
LAB_00637617:
  if (puVar2 == &DAT_00e2a93c) {
    FUN_00633920(param_1,"invalid key for `next\\'");
    puVar2 = extraout_ECX;
  }
  return (uint)((int)puVar2 + (-8 - *(int *)(param_2 + 0x10))) / 0x14 + *(int *)(param_2 + 0x1c);
}
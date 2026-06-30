// FUNC_NAME: QuickSort::partition
void __thiscall QuickSort::partition(int param_1, int param_2, undefined4 param_3)
{
  int in_EAX;
  int iVar1;
  
  iVar1 = in_EAX - param_1 >> 2;
  if (0x28 < iVar1) {
    iVar1 = iVar1 + 1;
    iVar1 = (int)(iVar1 + (iVar1 >> 0x1f & 7U)) >> 3;
    FUN_00588b10(param_1,iVar1 * 8 + param_1,param_3);
    FUN_00588b10(param_2 + iVar1 * -4,iVar1 * 4 + param_2,param_3);
    FUN_00588b10(in_EAX + iVar1 * -8);
    FUN_00588b10(iVar1 * 4 + param_1,in_EAX + iVar1 * -4,param_3);
    return;
  }
  FUN_00588b10(param_1);
  return;
}
// FUNC_NAME: SomeClass::handleMessage
void __thiscall SomeClass::handleMessage(int thisPtr, short *param_2, int param_3)
{
  int iVar1;
  
  iVar1 = *(int *)(thisPtr + 0x34);
  if (-1 < iVar1) {
    if (param_3 == thisPtr + 0x28) {
      FUN_006a3450(&DAT_0112a0e0);
      *(int *)(thisPtr + 0x34) = *(int *)(thisPtr + 0x34) + 1;
      return;
    }
    if (param_3 == thisPtr + 8) {
      if ((param_2 != (short *)0x0) && (iVar1 != 0)) {
        FUN_006a2660(*(int *)(*(int *)(thisPtr + 0x30) + 4) + 8,param_2,0x20);
        return;
      }
    }
    else if (param_3 == thisPtr + 0x10) {
      if ((param_2 != (short *)0x0) && (iVar1 != 0)) {
        FUN_006a2690(*(int *)(*(int *)(thisPtr + 0x30) + 4) + 0x48,param_2,0x200);
        return;
      }
    }
    else if (param_3 == thisPtr + 0x18) {
      if ((param_2 != (short *)0x0) && (iVar1 != 0)) {
        if (*param_2 == 0x31) {
          *(undefined1 *)(*(int *)(*(int *)(thisPtr + 0x30) + 4) + 0x458) = 1;
          return;
        }
        *(undefined1 *)(*(int *)(*(int *)(thisPtr + 0x30) + 4) + 0x458) = 0;
        return;
      }
    }
    else if (param_3 == thisPtr + 0x20) {
      if ((param_2 != (short *)0x0) && (iVar1 != 0)) {
        FUN_006a2380(param_2);
        return;
      }
    }
    else if (param_3 == thisPtr) {
      *(undefined4 *)(thisPtr + 0x34) = 0xffffffff;
    }
  }
  return;
}
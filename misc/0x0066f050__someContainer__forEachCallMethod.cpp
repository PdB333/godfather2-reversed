// FUNC_NAME: someContainer::forEachCallMethod

void __thiscall someContainer::forEachCallMethod(int *param_1, int param_2, int param_3, undefined4 param_4)

{
  int iVar1;
  
  iVar1 = 0;
  if (0 < param_3) {
    do {
      // Call virtual method at offset 0x10 on the object, passing each element and param_4
      (**(code **)(*param_1 + 0x10))(*(undefined4 *)(param_2 + iVar1 * 4),param_4,0);
      iVar1 = iVar1 + 1;
    } while (iVar1 < param_3);
  }
  return;
}
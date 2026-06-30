// FUNC_NAME: SomeClass::vtablePatcherOrConstructorHelper
void __thiscall SomeClass::vtablePatcherOrConstructorHelper(int *param_1, undefined4 param_2, undefined4 param_3, undefined4 param_4,
            undefined8 param_5, undefined8 param_6, undefined8 param_7, undefined8 param_8,
            undefined4 param_9, undefined4 param_10)
{
  int *piVar1;
  int iVar2;
  
  iVar2 = *param_1;
  // Patch vtable pointer at offset +0x14 (likely vtable table entry slot)
  **(undefined4 **)(iVar2 + 0x14) = &PTR_FUN_01124cc4;
  piVar1 = (int *)(iVar2 + 0x14);
  *piVar1 = *piVar1 + 4;
  // Delegate to another initialization function (likely does more setup)
  FUN_004f07e0(param_2, param_5, param_6, param_7, param_8, param_3, param_9, param_10, param_4);
  return;
}
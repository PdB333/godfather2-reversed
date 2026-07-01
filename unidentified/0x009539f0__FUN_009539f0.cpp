// FUNC_NAME: SomeClass::someMethod
void __thiscall SomeClass::someMethod(int *this, undefined4 param_2, undefined4 param_3, undefined4 param_4,
            undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8,
            undefined4 param_9)
{
  int *piVar1;
  int iVar2;
  
  iVar2 = *this;
  **(undefined4 **)(iVar2 + 0x14) = &PTR_LAB_00e573d8;
  piVar1 = (int *)(iVar2 + 0x14);
  *piVar1 = *piVar1 + 4;
  FUN_009538c0(param_2,param_3,param_4,param_5,param_6,param_7,param_8,param_9);
  return;
}
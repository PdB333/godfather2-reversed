// FUNC_NAME: SomeClass::someMethod
void __thiscall SomeClass::someMethod(int *this, undefined4 param_2, undefined4 param_3, undefined4 param_4,
            undefined4 param_5, undefined4 param_6, undefined4 param_7, undefined4 param_8,
            undefined4 param_9, undefined4 param_10, undefined4 param_11)
{
  int *piVar1;
  int iVar2;
  
  iVar2 = *this;
  **(undefined4 **)(iVar2 + 0x14) = &PTR_LAB_01124c74; // +0x14: vtable pointer
  piVar1 = (int *)(iVar2 + 0x14);
  *piVar1 = *piVar1 + 4; // Advance vtable pointer by 4 bytes
  FUN_004ee920(param_2,param_3,param_4,1,param_6,param_7,param_8,param_9,param_10,param_11);
  return;
}
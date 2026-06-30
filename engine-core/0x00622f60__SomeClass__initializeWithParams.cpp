// FUNC_NAME: SomeClass::initializeWithParams
int SomeClass::initializeWithParams(int param_1, int *param_2, int param_3)
{
  undefined4 uVar1;
  int *piVar2;
  
  piVar2 = param_2;
  (**(code **)(*param_2 + 8))(param_2); // vtable call at offset +8
  if (param_3 == 0) {
    uVar1 = 0;
  }
  else {
    uVar1 = FUN_004265d0(param_3, piVar2); // some conversion/copy function
  }
  FUN_00623940(piVar2, uVar1); // store or process
  *(int **)(param_1 + 0x14) = param_2; // store param_2 at +0x14
  (**(code **)(*param_2 + 8))(); // another vtable call at +8
  if (param_3 != 0) {
    uVar1 = FUN_004265d0(param_3, *(undefined4 *)(param_1 + 0x14));
    *(undefined4 *)(param_1 + 0x18) = uVar1; // store at +0x18
    (**(code **)(*param_2 + 4))(param_3, 0); // vtable call at +4
    (**(code **)(*param_2 + 0xc))(); // vtable call at +0xc
    return param_1;
  }
  *(undefined4 *)(param_1 + 0x18) = 0; // clear at +0x18
  (**(code **)(*param_2 + 0xc))(); // vtable call at +0xc
  return param_1;
}
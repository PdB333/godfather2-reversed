// FUNC_NAME: SomeClass::someMethod
void SomeClass::someMethod(int* param_1, int param_2)
{
  undefined4 uVar1;
  int unaff_EDI;
  
  *(int **)(unaff_EDI + 4) = param_1;
  (**(code **)(*param_1 + 8))();
  if (param_2 != 0) {
    uVar1 = FUN_004265d0(param_2,*(undefined4 *)(unaff_EDI + 4));
    *(undefined4 *)(unaff_EDI + 8) = uVar1;
    (**(code **)(*param_1 + 4))(param_2,0);
    (**(code **)(*param_1 + 0xc))();
    return;
  }
  *(undefined4 *)(unaff_EDI + 8) = 0;
  (**(code **)(*param_1 + 0xc))();
  return;
}
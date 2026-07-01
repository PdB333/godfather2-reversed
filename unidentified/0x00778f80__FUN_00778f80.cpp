// FUNC_NAME: SomeClass::checkDistanceOrSomething
undefined4 __fastcall FUN_00778f80(int param_1)
{
  int *piVar1;
  float10 extraout_ST0;
  
  if ((*(int *)(param_1 + 0x88) != 0) && (*(int *)(param_1 + 0x88) != 0x48)) {
    if (*(int *)(param_1 + 0x88) == 0) {
      piVar1 = (int *)0x0;
    }
    else {
      piVar1 = (int *)(*(int *)(param_1 + 0x88) + -0x48);
    }
    (**(code **)(*piVar1 + 0x1a8))();
    if ((float10)_DAT_00d6835c < extraout_ST0) {
      return 1;
    }
  }
  return 0;
}
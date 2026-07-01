// FUNC_NAME: SomeClass::releaseOrResetSomething
void __fastcall SomeClass::releaseOrResetSomething(int param_1)
{
  int iVar1;
  
  iVar1 = param_1;
  if (*(char *)(param_1 + 0xff8) != '\x02') {
    if (*(int *)(param_1 + 0xff0) == 0) {
      iVar1 = 0;
    }
    else {
      iVar1 = *(int *)(param_1 + 0xff0) + -0x48;
    }
  }
  if (*(char *)(param_1 + 0xff8) != '\x01') {
    if (*(int *)(param_1 + 0xff0) == 0) {
      param_1 = 0;
    }
    else {
      param_1 = *(int *)(param_1 + 0xff0) + -0x48;
    }
  }
  if (iVar1 != 0) {
    if (*(int *)(iVar1 + 0xff0) != 0) {
      FUN_004daf90((undefined4 *)(iVar1 + 0xff0));
      *(undefined4 *)(iVar1 + 0xff0) = 0;
    }
    *(undefined1 *)(iVar1 + 0xff8) = 0;
    *(undefined1 *)(iVar1 + 0xff9) = 0xff;
  }
  if (param_1 != 0) {
    if (*(int *)(param_1 + 0xff0) != 0) {
      FUN_004daf90((undefined4 *)(param_1 + 0xff0));
      *(undefined4 *)(param_1 + 0xff0) = 0;
    }
    *(undefined1 *)(param_1 + 0xff8) = 0;
    *(undefined1 *)(param_1 + 0xff9) = 0xff;
  }
  FUN_007fcd60();
  return;
}
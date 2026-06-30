// FUNC_NAME: SomeClass::releaseOrReset
void __fastcall SomeClass::releaseOrReset(int *param_1)
{
  SomeClass::release(param_1); // 0x005c0b40
  param_1[2] = 0; // +0x08
  param_1[1] = 0; // +0x04
  if (*param_1 != 0) { // +0x00
    (**(code **)(**(int **)(DAT_012234ec + 4) + 4))(*param_1,0);
  }
  *param_1 = 0; // +0x00
  return;
}
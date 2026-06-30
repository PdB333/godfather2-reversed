// FUNC_NAME: SomeClass::updateSomething
void SomeClass::updateSomething(int param_1)
{
  int unaff_ESI;
  
  if ((*(int *)(unaff_ESI + 0x28) != 0) &&
     (DAT_00e2af44 < *(float *)(param_1 + 0xc) || DAT_00e2af44 == *(float *)(param_1 + 0xc))) {
    if ((*(byte *)(*(int *)(unaff_ESI + 0x24) + 0x14) & 0x20) != 0) {
      FUN_004e41b0();
      FUN_004e41b0();
    }
    FUN_004ef520();
  }
  return;
}
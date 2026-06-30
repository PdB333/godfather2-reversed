// FUNC_NAME: SomeClass::setSomePointer
void SomeClass::setSomePointer(int param_1)
{
  int iVar1;
  int *piVar2;
  
  iVar1 = param_1;
  param_1 = *(undefined4 *)(param_1 + 0x184); // +0x184: some offset
  piVar2 = (int *)FUN_006b1230(&param_1);
  *piVar2 = iVar1;
  return;
}
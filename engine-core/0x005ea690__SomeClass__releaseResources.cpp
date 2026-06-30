// FUNC_NAME: SomeClass::releaseResources
void SomeClass::releaseResources(int param_1)
{
  int *piVar1;
  int *piVar2;
  int iVar3;
  
  iVar3 = 4;
  piVar2 = (int *)(param_1 + 0x10c);
  do {
    piVar1 = piVar2 + -9;
    piVar2 = piVar2 + -0xc;
    if (*piVar1 != 0) {
      FUN_009c8f10(*piVar1);
    }
    if (*piVar2 != 0) {
      FUN_009c8f10(*piVar2);
    }
    iVar3 = iVar3 + -1;
  } while (-1 < iVar3);
  if (*(int *)(param_1 + 4) != 0) {
    (**(code **)(param_1 + 0x10))(*(int *)(param_1 + 4));
  }
  return;
}
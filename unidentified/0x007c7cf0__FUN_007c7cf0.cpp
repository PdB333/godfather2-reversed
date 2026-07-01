// FUNC_NAME: SomeClass::updateSomePointer
void __thiscall updateSomePointer(int this, undefined4 param_2)
{
  int *piVar1;
  int iVar2;
  
  iVar2 = *(int *)(*(int *)(this + 0x58) + 0x31a8);
  if (iVar2 == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = iVar2 + -0x48;
  }
  piVar1 = (int *)(this + 0xdc);
  if (iVar2 == 0) {
    iVar2 = 0;
  }
  else {
    iVar2 = iVar2 + 0x48;
  }
  if (*piVar1 != iVar2) {
    if (*piVar1 != 0) {
      FUN_004daf90(piVar1);
    }
    *piVar1 = iVar2;
    if (iVar2 != 0) {
      *(undefined4 *)(this + 0xe0) = *(undefined4 *)(iVar2 + 4);
      *(int **)(iVar2 + 4) = piVar1;
    }
  }
  *(undefined4 *)(this + 0xd8) = *(undefined4 *)(this + 0x58);
  FUN_007d2110(param_2,0);
  return;
}
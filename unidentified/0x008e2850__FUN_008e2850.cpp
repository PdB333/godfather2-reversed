// FUNC_NAME: SomeClass::removeFromListOrSomething
void FUN_008e2850(undefined4 param_1, int param_2)
{
  int iVar1;
  int *piVar2;
  undefined **local_18;
  int local_14;
  undefined4 local_10;
  undefined4 local_c;
  undefined ***local_8;
  undefined1 local_4;
  
  iVar1 = FUN_00791300();
  local_18 = &PTR_FUN_00e31e2c;
  if (iVar1 == 0) {
    local_14 = 0;
  }
  else {
    local_14 = iVar1 + 0x48;
  }
  local_10 = 0;
  if (local_14 != 0) {
    local_10 = *(undefined4 *)(local_14 + 4);
    *(int **)(local_14 + 4) = &local_14;
  }
  local_c = *(undefined4 *)(param_2 + 0x30);
  local_8 = &local_18;
  local_4 = 0;
  FUN_00408a00(&local_c,0);
  piVar2 = (int *)(param_2 + 0x44);
  if (iVar1 == 0) {
    iVar1 = 0;
  }
  else {
    iVar1 = iVar1 + 0x48;
  }
  if (*piVar2 != iVar1) {
    if (*piVar2 != 0) {
      FUN_004daf90(piVar2);
    }
    *piVar2 = iVar1;
    if (iVar1 != 0) {
      *(undefined4 *)(param_2 + 0x48) = *(undefined4 *)(iVar1 + 4);
      *(int **)(iVar1 + 4) = piVar2;
    }
  }
  if (local_14 != 0) {
    FUN_004daf90(&local_14);
  }
  return;
}
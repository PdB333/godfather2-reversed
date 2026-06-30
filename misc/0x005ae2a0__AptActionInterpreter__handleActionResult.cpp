// FUNC_NAME: AptActionInterpreter::handleActionResult
void __thiscall AptActionInterpreter::handleActionResult(int this, int param_2)

{
  int *piVar1;
  code *pcVar2;
  int iVar3;
  uint uVar4;
  int unaff_FS_OFFSET;
  undefined *local_14;
  char *local_10;
  undefined4 local_c;
  int local_8;
  undefined1 *local_4;
  
  iVar3 = FUN_005adfa0(param_2,this);
  if (iVar3 != 0) {
    return;
  }
  local_14 = &DAT_00e3d06c;
  local_10 = "..\\source\\Apt\\AptActionInterpreter.cpp";
  local_c = 0x467;
  local_8 = 2;
  local_4 = &DAT_01128ff4;
  if (DAT_01128ff4 != '\0') {
    piVar1 = *(int **)(**(int **)(unaff_FS_OFFSET + 0x2c) + 0x30);
    uVar4 = 1;
    if (((piVar1 == (int *)0x0) ||
        (uVar4 = (**(code **)(*piVar1 + 8))(&local_14,&DAT_00e3d06c), local_4 != (undefined1 *)0x0))
       && ((uVar4 & 2) != 0)) {
      *local_4 = 0;
    }
    if (((piVar1 != (int *)0x0) || (local_8 != 4)) &&
       (((uVar4 & 1) != 0 || ((local_8 == 0 || (local_8 == 1)))))) {
      pcVar2 = (code *)swi(3);
      (*pcVar2)();
      return;
    }
    return;
  }
  return;
}
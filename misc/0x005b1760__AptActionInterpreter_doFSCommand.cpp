// Xbox PDB: AptActionInterpreter::doFSCommand
// FUNC_NAME: AptActionInterpreter::handleFSCommand
undefined4 FUN_005b1760(undefined4 param_1)

{
  int *piVar1;
  code *pcVar2;
  char *in_EAX;
  int iVar3;
  uint uVar4;
  undefined4 uVar5;
  int unaff_FS_OFFSET;
  char *local_14;
  char *local_10;
  undefined4 local_c;
  int local_8;
  undefined1 *local_4;
  
  iVar3 = _strncmp(in_EAX,"FSCommand:",10);
  if (iVar3 == 0) goto LAB_005b1804;
  local_14 = "isFSCommand(szCommand)";
  local_10 = "..\\source\\Apt\\AptActionInterpreter.cpp";
  local_c = 0xe2f;
  local_8 = 2;
  local_4 = &DAT_01129001;
  if (DAT_01129001 == '\0') goto LAB_005b1804;
  piVar1 = *(int **)(**(int **)(unaff_FS_OFFSET + 0x2c) + 0x30);
  uVar4 = 1;
  if (piVar1 == (int *)0x0) {
LAB_005b17e1:
    if ((uVar4 & 2) != 0) {
      *local_4 = 0;
    }
  }
  else {
    uVar4 = (**(code **)(*piVar1 + 8))(&local_14,"isFSCommand(szCommand)");
    if (local_4 != (undefined1 *)0x0) goto LAB_005b17e1;
  }
  if (((piVar1 != (int *)0x0) || (local_8 != 4)) &&
     (((uVar4 & 1) != 0 || ((local_8 == 0 || (local_8 == 1)))))) {
    pcVar2 = (code *)swi(3);
    uVar5 = (*pcVar2)();
    return uVar5;
  }
LAB_005b1804:
  (*DAT_0119cb20)(in_EAX + 10,param_1);
  return 1;
}
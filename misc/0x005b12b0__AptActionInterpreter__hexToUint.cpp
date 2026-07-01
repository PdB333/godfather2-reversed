// FUNC_NAME: AptActionInterpreter::hexToUint
void AptActionInterpreter::hexToUint(char hiDigit, char loDigit)
{
  int *piVar1;
  code *pcVar2;
  char cVar3;
  int iVar4;
  uint uVar5;
  int unaff_FS_OFFSET;
  char cStack00000005;
  undefined1 uStack00000006;
  char *local_14;
  char *local_10;
  undefined4 local_c;
  int local_8;
  undefined1 *local_4;
  
  cVar3 = hiDigit;
  iVar4 = _isxdigit((int)hiDigit);
  if (iVar4 != 0) {
    iVar4 = _isxdigit((int)loDigit);
    if (iVar4 != 0) goto LAB_005b1364;
  }
  // Assertion: "isxdigit(a) && isxdigit(b)"
  // File: "..\\source\\Apt\\AptActionInterpreter.cpp", line 0xddf (3551)
  local_14 = "isxdigit(a) && isxdigit(b)";
  local_10 = "..\\source\\Apt\\AptActionInterpreter.cpp";
  local_c = 0xddf;
  local_8 = 2;
  local_4 = &DAT_01129000; // +0x0 assertion enabled flag
  if (DAT_01129000 == '\0') goto LAB_005b1364;
  piVar1 = *(int **)(**(int **)(unaff_FS_OFFSET + 0x2c) + 0x30);
  uVar5 = 1;
  if (piVar1 == (int *)0x0) {
LAB_005b1341:
    if ((uVar5 & 2) != 0) {
      *local_4 = 0;
    }
  }
  else {
    uVar5 = (**(code **)(*piVar1 + 8))(&local_14,"isxdigit(a) && isxdigit(b)");
    if (local_4 != (undefined1 *)0x0) goto LAB_005b1341;
  }
  // If assertion fails, trigger int3 debug break
  if (((piVar1 != (int *)0x0) || (local_8 != 4)) &&
     (((uVar5 & 1) != 0 || ((local_8 == 0 || (local_8 == 1)))))) {
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
LAB_005b1364:
  // Both digits are hex, parse as two hex digits
  cStack00000005 = loDigit;
  uStack00000006 = 0;  // null terminator for the two-char string
  hiDigit = cVar3;      // restore hi digit (though param_1 is now stack pointer)
  _strtoul(&hiDigit, (char **)0x0, 0x10);  // parse as base 16
  return;
}
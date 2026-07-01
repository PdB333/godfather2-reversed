// FUNC_NAME: AptValue::checkIsBoolean
void AptValue::checkIsBoolean(void)
{
  int *piVar1;
  code *pcVar2;
  char cVar3;
  uint uVar4;
  int unaff_FS_OFFSET;
  char *local_14;
  char *local_10;
  undefined4 local_c;
  int local_8;
  undefined1 *local_4;
  
  cVar3 = FUN_005a7c70(); // AptValue::isBoolean() - check if value is boolean
  if (cVar3 != '\0') {
    return;
  }
  // Assertion data: "isBoolean()" at file "c:\packages001_pc\apt\0.19.optimized\source\apt\_AptValue.h" line 0xd7
  local_14 = "isBoolean()";
  local_10 = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
  local_c = 0xd7;
  local_8 = 2;
  local_4 = &DAT_01128fa9; // Global assertion flag
  if (DAT_01128fa9 != '\0') {
    piVar1 = *(int **)(**(int **)(unaff_FS_OFFSET + 0x2c) + 0x30);
    uVar4 = 1;
    if (((piVar1 == (int *)0x0) ||
        (uVar4 = (**(code **)(*piVar1 + 8))(&local_14,"isBoolean()"), local_4 != (undefined1 *)0x0))
       && ((uVar4 & 2) != 0)) {
      *local_4 = 0; // Clear assertion flag
    }
    if (((piVar1 != (int *)0x0) || (local_8 != 4)) &&
       (((uVar4 & 1) != 0 || ((local_8 == 0 || (local_8 == 1)))))) {
      pcVar2 = (code *)swi(3); // Trigger debug breakpoint
      (*pcVar2)();
      return;
    }
    return;
  }
  return;
}
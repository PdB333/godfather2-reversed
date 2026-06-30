// Xbox PDB: AptValue::c_array
// FUNC_NAME: AptValue::assertIsArray
void AptValue::assertIsArray(void)
{
  int *piVar1;
  code *pcVar2;
  char cVar3;
  uint uVar4;
  char *local_14;
  char *local_10;
  undefined4 local_c;
  int local_8;
  undefined1 *local_4;
  
  cVar3 = FUN_0059c500(); // likely AptValue::isValid or some invariant check
  if (cVar3 != '\0') {
    return;
  }
  local_14 = "isArray()";
  local_10 = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
  local_c = 0x103; // line number 259
  local_8 = 2; // assertion type or severity
  local_4 = &DAT_01128fae; // global assertion flag
  if (DAT_01128fae != '\0') { // assert enabled
    piVar1 = *(int **)(**(int **)(unaff_FS_OFFSET + 0x2c) + 0x30); // get CRT debug info
    uVar4 = 1;
    if (((piVar1 == (int *)0x0) ||
        (uVar4 = (**(code **)(*piVar1 + 8))(&local_14,"isArray()"), local_4 != (undefined1 *)0x0))
       && ((uVar4 & 2) != 0)) {
      *local_4 = 0; // clear assertion flag to suppress further assertions
    }
    if (((piVar1 != (int *)0x0) || (local_8 != 4)) &&
       (((uVar4 & 1) != 0 || ((local_8 == 0 || (local_8 == 1)))))) {
      pcVar2 = (code *)swi(3); // breakpoint / debug break
      (*pcVar2)();
      return;
    }
    return;
  }
  return;
}
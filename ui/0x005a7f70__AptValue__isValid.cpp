// FUNC_NAME: AptValue::isValid
undefined4 FUN_005a7f70(void)

{
  int *piVar1;
  code *pcVar2;
  uint uVar3;
  undefined4 uVar4;
  uint *this;
  int unaff_FS_OFFSET;
  undefined *local_14;
  char *local_10;
  undefined4 local_c;
  int local_8;
  undefined1 *local_4;
  
  if (this != (uint *)0x0) goto LAB_005a7ffe;
  local_14 = &DAT_00e3b9b8;
  local_10 = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
  local_c = 0x1a9;
  local_8 = 2;
  local_4 = &DAT_01128fb9;
  if (DAT_01128fb9 == '\0') goto LAB_005a7ffe;
  piVar1 = *(int **)(**(int **)(unaff_FS_OFFSET + 0x2c) + 0x30);
  uVar3 = 1;
  if (piVar1 == (int *)0x0) {
LAB_005a7fdb:
    if ((uVar3 & 2) != 0) {
      *local_4 = 0;
    }
  }
  else {
    uVar3 = (**(code **)(*piVar1 + 8))(&local_14,&DAT_00e3b9b8);
    if (local_4 != (undefined1 *)0x0) goto LAB_005a7fdb;
  }
  if (((piVar1 != (int *)0x0) || (local_8 != 4)) &&
     (((uVar3 & 1) != 0 || ((local_8 == 0 || (local_8 == 1)))))) {
    pcVar2 = (code *)swi(3);
    uVar4 = (*pcVar2)();
    return uVar4;
  }
LAB_005a7ffe:
  // Check if the value type is a string (0x14) and the reference flag is set
  if (((*this & 0x7fff) == 0x14) && ((~(byte)(*this >> 0xf) & 1) == 0)) {
    return 1;
  }
  return 0;
}
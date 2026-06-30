// FUNC_NAME: AptValue::isValidOrDebugAssert
undefined4 FUN_005a4080(void)

{
  int *piVar1;
  code *pcVar2;
  uint uVar3;
  undefined4 uVar4;
  uint *this; // unaff_EDI - likely 'this' pointer for AptValue
  int unaff_FS_OFFSET;
  undefined *local_14; // debug info: filename pointer
  char *local_10; // debug info: source file path
  undefined4 local_c; // debug info: line number
  int local_8; // debug info: assertion type
  undefined1 *local_4; // debug info: assertion flag
  
  if (this != (uint *)0x0) goto LAB_005a410e;
  // Debug assertion: "this pointer is null"
  local_14 = &DAT_00e3b9b8; // likely "Assertion failed" string
  local_10 = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
  local_c = 0x2b5; // line 693
  local_8 = 2; // assertion type (e.g., ASSERT_ALWAYS)
  local_4 = &DAT_01128f71; // global assertion flag
  if (DAT_01128f71 == '\0') goto LAB_005a410e;
  piVar1 = *(int **)(**(int **)(unaff_FS_OFFSET + 0x2c) + 0x30);
  uVar3 = 1;
  if (piVar1 == (int *)0x0) {
LAB_005a40eb:
    if ((uVar3 & 2) != 0) {
      *local_4 = 0; // disable further assertions
    }
  }
  else {
    uVar3 = (**(code **)(*piVar1 + 8))(&local_14,&DAT_00e3b9b8);
    if (local_4 != (undefined1 *)0x0) goto LAB_005a40eb;
  }
  if (((piVar1 != (int *)0x0) || (local_8 != 4)) &&
     (((uVar3 & 1) != 0 || ((local_8 == 0 || (local_8 == 1)))))) {
    pcVar2 = (code *)swi(3); // software interrupt (debug break)
    uVar4 = (*pcVar2)();
    return uVar4;
  }
LAB_005a410e:
  // Check if this is a valid AptValue (non-null, type in valid range)
  uVar3 = *this & 0x7fff; // mask to get type field (lower 15 bits)
  if ((0xb < uVar3) && ((uVar3 < 0x14 && ((~(byte)(*this >> 0xf) & 1) == 0)))) {
    // Type is between 0xC and 0x13 (inclusive) and not a special flag
    return 1; // valid
  }
  return 0; // invalid
}
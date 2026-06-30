// FUNC_NAME: AptValue::setVftIndex
void AptValue::setVftIndex(uint *this)
{
  int *piVar1;
  code *pcVar2;
  uint uVar3;
  uint vftIndex; // unaff_EDI
  int fsOffset; // unaff_FS_OFFSET
  char *file;
  char *condition;
  undefined4 line;
  int severity;
  undefined1 *assertFlag;
  
  if ((int)vftIndex < 0x24) goto LAB_0059c377;
  condition = "n < AptVFT_NumVFTs";
  file = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
  line = 0xa3;
  severity = 2;
  assertFlag = &DAT_01128f0c;
  if (DAT_01128f0c == '\0') goto LAB_0059c377;
  piVar1 = *(int **)(**(int **)(fsOffset + 0x2c) + 0x30);
  uVar3 = 1;
  if (piVar1 == (int *)0x0) {
LAB_0059c354:
    if ((uVar3 & 2) != 0) {
      *assertFlag = 0;
    }
  }
  else {
    uVar3 = (**(code **)(*piVar1 + 8))(&condition,"n < AptVFT_NumVFTs");
    if (assertFlag != (undefined1 *)0x0) goto LAB_0059c354;
  }
  if (((piVar1 != (int *)0x0) || (severity != 4)) &&
     (((uVar3 & 1) != 0 || ((severity == 0 || (severity == 1)))))) {
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
LAB_0059c377:
  // Store vftIndex in lower 15 bits of the first uint field
  *this = *this & 0xffff8000 | vftIndex;
  return;
}
// FUNC_NAME: AptXFormStack::popTransform
void AptXFormStack::popTransform(void)
{
  int *piVar1;
  code *pcVar2;
  uint uVar3;
  int iVar4;
  undefined8 *this; // unaff_EDI
  int fsOffset; // unaff_FS_OFFSET
  char *assertExpr;
  char *assertFile;
  undefined4 assertLine;
  int assertLevel;
  undefined1 *assertFlag;
  
  if (0 < *(int *)(this + 0x77)) goto LAB_0059cc25;
  assertExpr = "nCXFormStack > 0";
  assertFile = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_Apt.h";
  assertLine = 0x1c9;
  assertLevel = 2;
  assertFlag = &DAT_01128f17;
  if (DAT_01128f17 == '\0') goto LAB_0059cc25;
  piVar1 = *(int **)(**(int **)(fsOffset + 0x2c) + 0x30);
  uVar3 = 1;
  if (piVar1 == (int *)0x0) {
LAB_0059cc02:
    if ((uVar3 & 2) != 0) {
      *assertFlag = 0;
    }
  }
  else {
    uVar3 = (**(code **)(*piVar1 + 8))(&assertExpr,"nCXFormStack > 0");
    if (assertFlag != (undefined1 *)0x0) goto LAB_0059cc02;
  }
  if (((piVar1 != (int *)0x0) || (assertLevel != 4)) &&
     (((uVar3 & 1) != 0 || ((assertLevel == 0 || (assertLevel == 1)))))) {
    pcVar2 = (code *)swi(3);
    (*pcVar2)();
    return;
  }
LAB_0059cc25:
  // Decrement stack count and pop transform
  *(int *)(this + 0x77) = *(int *)(this + 0x77) + -1;
  iVar4 = *(int *)(this + 0x77) + 1;
  *this = this[iVar4 * 4];
  this[1] = this[iVar4 * 4 + 1];
  this[2] = this[iVar4 * 4 + 2];
  this[3] = this[iVar4 * 4 + 3];
  return;
}
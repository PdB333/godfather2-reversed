// FUNC_NAME: AptStack::pop
void AptStack::pop(void)

{
  int *exceptionRecord;
  code *handler;
  uint handlerFlags;
  int *edi;
  int fsOffset;
  char *assertionMsg;
  char *assertionFile;
  undefined4 assertionLine;
  int assertionType;
  undefined1 *assertionFlag;
  
  if (0 < *edi) goto LAB_005b1a31;
  assertionMsg = "size() > 0";
  assertionFile = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptStack.h";
  assertionLine = 0x23;
  assertionType = 2;
  assertionFlag = &DAT_01129003;
  if (DAT_01129003 == '\0') goto LAB_005b1a31;
  exceptionRecord = *(int **)(**(int **)(fsOffset + 0x2c) + 0x30);
  handlerFlags = 1;
  if (exceptionRecord == (int *)0x0) {
LAB_005b1a0e:
    if ((handlerFlags & 2) != 0) {
      *assertionFlag = 0;
    }
  }
  else {
    handlerFlags = (**(code **)(*exceptionRecord + 8))(&assertionMsg,"size() > 0");
    if (assertionFlag != (undefined1 *)0x0) goto LAB_005b1a0e;
  }
  if (((exceptionRecord != (int *)0x0) || (assertionType != 4)) &&
     (((handlerFlags & 1) != 0 || ((assertionType == 0 || (assertionType == 1)))))) {
    handler = (code *)swi(3);
    (*handler)();
    return;
  }
LAB_005b1a31:
  // Call destructor on the top element and decrement stack size
  (**(code **)(&DAT_0103aee0 + (*(uint *)edi[*edi] & 0x7fff) * 4))
            ((uint *)edi[*edi]);
  *edi = *edi + -1;
  return;
}
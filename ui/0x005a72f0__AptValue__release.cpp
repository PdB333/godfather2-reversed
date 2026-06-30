// FUNC_NAME: AptValue::release
void AptValue::release(void)
{
  int *piVar1;
  code *pcVar2;
  uint uVar3;
  
  // +0x02: reference count (short)
  if (*(short *)(this + 2) != 0) {
    // Reference count > 0, just decrement
    FUN_0059c230(this);  // AptValue::decrementRefCount
    return;
  }
  
  // Assertion: getRefCount() > 0
  // File: c:\packages001_pc\apt\0.19.optimized\source\apt\_AptValue.h, line 0xb3 (179)
  char *assertMsg = "getRefCount() > 0";
  char *assertFile = "c:\\packages001_pc\\apt\\0.19.optimized\\source\\apt\\_AptValue.h";
  int assertLine = 0xb3;
  int assertLevel = 2;
  char *assertFlag = &DAT_01128fa6;
  
  if (*assertFlag != '\0') {
    // Debug assertion check
    piVar1 = *(int **)(**(int **)(__readfsdword(0x2c) + 0x30) + 0x30);
    uVar3 = 1;
    if (piVar1 != (int *)0x0) {
      uVar3 = (**(code **)(*piVar1 + 8))(&assertMsg, "getRefCount() > 0");
      if (assertFlag != (undefined1 *)0x0) goto LAB_005a7360;
    }
    else {
LAB_005a7360:
      if ((uVar3 & 2) != 0) {
        *assertFlag = 0;
      }
    }
    
    if (((piVar1 != (int *)0x0) || (assertLevel != 4)) &&
       (((uVar3 & 1) != 0 || ((assertLevel == 0 || (assertLevel == 1)))))) {
      pcVar2 = (code *)swi(3);  // Debug breakpoint
      (*pcVar2)();
      return;
    }
  }
  
  // Reference count is 0, still decrement (will trigger delete)
  FUN_0059c230(this);  // AptValue::decrementRefCount
  return;
}
// FUNC_NAME: RefCountedString::setString
void RefCountedString::setString(int *newString)
{
  int *oldString;
  int *piVar2;
  int refCount;
  int *piVar4;
  int thisPtr;
  
  FUN_005a4560(); // likely some initialization or lock
  piVar4 = newString;
  piVar1 = (int *)(thisPtr + 0x28); // +0x28: pointer to current string
  *piVar1 = 0;
  *(undefined4 *)(thisPtr + 0x24) = 0; // +0x24: string length or flags
  if (&newString != (int **)piVar1) {
    oldString = (int *)*piVar1;
    if (((oldString != (int *)0x0) && (*oldString = *oldString + -1, *oldString == 0)) &&
       (refCount = *piVar1, refCount != 0)) {
      FUN_005a1b40(); // likely free/deallocate
      (*DAT_0119caf8)(refCount,0x30); // operator delete with size 0x30
    }
    *piVar1 = (int)piVar4;
    if (piVar4 != (int *)0x0) {
      *piVar4 = *piVar4 + 1; // increment ref count
    }
  }
  *(int *)(thisPtr + 8) = piVar4[10]; // +0x08: copy some data from new string
  *piVar4 = *piVar4 + -1; // decrement ref count
  if (*piVar4 == 0) {
    FUN_005a1b40();
    (*DAT_0119caf8)(piVar4,0x30);
  }
  return;
}
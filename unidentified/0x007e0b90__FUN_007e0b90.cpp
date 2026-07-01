// FUNC_NAME: SomeClass::notifyOrSetLinkedObject
void __thiscall SomeClass::notifyOrSetLinkedObject(int thisPtr, int linkedObj)
{
  int *piVar1;
  
  piVar1 = (int *)(thisPtr + 0x114);
  if (linkedObj == 0) {
    linkedObj = 0;
  }
  else {
    linkedObj = linkedObj + 0x48;
  }
  if (*piVar1 != linkedObj) {
    if (*piVar1 != 0) {
      FUN_004daf90(piVar1);
    }
    *piVar1 = linkedObj;
    if (linkedObj != 0) {
      *(undefined4 *)(thisPtr + 0x118) = *(undefined4 *)(linkedObj + 4);
      *(int **)(linkedObj + 4) = piVar1;
    }
  }
  return;
}
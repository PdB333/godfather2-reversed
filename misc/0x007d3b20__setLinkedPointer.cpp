// FUNC_NAME: setLinkedPointer
int * __thiscall setLinkedPointer(int *thisPtr, int newPtr)
{
  if (*thisPtr != newPtr) {
    if (*thisPtr != 0) {
      FUN_004daf90(thisPtr);
    }
    *thisPtr = newPtr;
    if (newPtr != 0) {
      thisPtr[1] = *(int *)(newPtr + 4); // copy new object's link field +0x04
      *(int **)(newPtr + 4) = thisPtr;   // set new object's link field to point back
    }
  }
  return thisPtr;
}
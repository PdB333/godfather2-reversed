// FUNC_NAME: RefHolder::releaseReferences
void __thiscall RefHolder::releaseReferences(int *thisPtr)
{
  int *containerPtr;
  int *ptrToRelease;
  int *basePtr;
  int index;

  if (thisPtr != (int *)0x0) {
    // Release pointer at offset +0xC (thisPtr[3])
    ptrToRelease = (int *)thisPtr[3];
    basePtr = (int *)thisPtr[0];
    if (ptrToRelease != (int *)0x0) {
      // Index stored at offset -8 from the pointer (i.e., at allocation start+8)
      index = *(int *)(ptrToRelease + -2);
      // Zero the entry in the array at basePtr[0xC] (basePtr[3])
      *(int *)(*(int *)(basePtr + 3) + index * 4) = 0;
      // Decrement reference counter at offset +0x4 (thisPtr[1])
      thisPtr[1] = thisPtr[1] - 1;
      // Free the allocation (header at ptrToRelease - 0x10)
      (*DAT_01206694)(ptrToRelease + -4);
    }
    // Release pointer at offset +0x10 (thisPtr[4])
    ptrToRelease = (int *)thisPtr[4];
    basePtr = (int *)thisPtr[0];
    if (ptrToRelease != (int *)0x0) {
      index = *(int *)(ptrToRelease + -2);
      *(int *)(*(int *)(basePtr + 3) + index * 4) = 0;
      thisPtr[1] = thisPtr[1] - 1;
      (*DAT_01206694)(ptrToRelease + -4);
    }
    // Release pointer from parent class (accessed via negative offset -8)
    // thisPtr[-2] is the container’s pointer (offset 0 relative to container start)
    ptrToRelease = (int *)thisPtr[-2];
    basePtr = (int *)thisPtr[0];
    if (ptrToRelease != (int *)0x0) {
      index = *(int *)(ptrToRelease + -2);
      *(int *)(*(int *)(basePtr + 3) + index * 4) = 0;
      thisPtr[1] = thisPtr[1] - 1;
      (*DAT_01206694)(ptrToRelease + -4);
    }
  }
  return;
}
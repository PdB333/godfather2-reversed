// FUNC_NAME: RefCountedObject::release
void RefCountedObject::release(void)
{
  int *refCountPtr;
  int refCount;
  
  if (this != 0) {
    refCountPtr = *(int **)(this + 4);
    if (((refCountPtr != (int *)0x0) && (*refCountPtr = *refCountPtr + -1, *refCountPtr == 0)) &&
       (refCount = *(int *)(this + 4), refCount != 0)) {
      RefCountedObject::onRefCountZero(); // FUN_005a1b40 - virtual cleanup
      (*DAT_0119caf8)(refCount,0x30); // operator delete with size 0x30
    }
    (*DAT_0119caf8)(); // operator delete on this
  }
  return;
}
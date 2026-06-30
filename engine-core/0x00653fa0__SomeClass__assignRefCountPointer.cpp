// FUNC_NAME: SomeClass::assignRefCountPointer
void __thiscall SomeClass::assignRefCountPointer(int *newPtr)
{
  int *oldPtr;
  int *refCountPtr;
  
  oldPtr = *(int **)(this + 0x1b0);
  if (oldPtr != (int *)0x0) {
    refCountPtr = oldPtr + 2; // offset +0x8: refcount
    *refCountPtr = *refCountPtr - 1;
    if (*refCountPtr == 0) {
      (**(code **)(*oldPtr + 8))(); // call virtual destructor via vtable[2]
    }
  }
  *(int **)(this + 0x1b0) = newPtr;
  if (newPtr != (int *)0x0) {
    *(int *)(newPtr + 8) = *(int *)(newPtr + 8) + 1;
  }
  return;
}
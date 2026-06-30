// FUNC_NAME: RefCountedPtr::assign
void RefCountedPtr::assign(void *newPtr)
{
  int *refCountedObj;
  int *oldObj;
  
  oldObj = *(int **)this;
  if (oldObj != (int *)0x0) {
    refCountedObj = oldObj + 2;
    *refCountedObj = *refCountedObj + -1;
    if (*refCountedObj == 0) {
      (**(code **)(*oldObj + 8))(); // call destructor via vtable
    }
  }
  *(int **)this = (int *)newPtr;
  if (newPtr != (void *)0x0) {
    *(int *)((int)newPtr + 8) = *(int *)((int)newPtr + 8) + 1; // increment ref count at +0x08
  }
  return;
}
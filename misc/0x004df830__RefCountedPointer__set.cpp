// FUNC_NAME: RefCountedPointer::set
void __thiscall RefCountedPointer::set(int *this, int *newPtr)
{
  int *oldPtr;
  
  oldPtr = *this;  // this->m_ptr
  if (oldPtr != 0) {
    if (*(int *)(oldPtr + 0x20) != 0) {  // oldPtr->m_refCount
      // Decrement old reference count
      *(int *)(oldPtr + 0x20) = *(int *)(oldPtr + 0x20) - 1;
      if (*(int *)(oldPtr + 0x20) == 0) {  // if refCount reaches 0
        // Call virtual destructor through vtable
        (**(code **)(*(int *)oldPtr + 4))();
      }
      *(int *)(oldPtr + 0x20) = 0;  // Clear old refCount
    }
    *this = newPtr;  // Assign new pointer
    if (newPtr != 0) {
      // Increment new reference count
      *(int *)(newPtr + 4) = *(int *)(newPtr + 4) + 1;
    }
  }
  return;
}
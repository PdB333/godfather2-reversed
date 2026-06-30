// FUNC_NAME: RefCountedPtr::assign
void __thiscall RefCountedPtr::assign(int *this, int *other)
{
  int *currentPtr;
  int newPtr;
  
  currentPtr = (int *)*this;
  if (currentPtr != 0) {
    newPtr = *other;
    if (*(int *)(currentPtr + 0x20) != 0) {
      // Decrement reference count on current object's ref counter
      int *refCount = (int *)(*(int *)(currentPtr + 0x20) + 4);
      *refCount = *refCount - 1;
      if ((*(int **)(currentPtr + 0x20))[1] == 0) {
        // If ref count reached zero, call destructor via vtable
        (**(code **)(**(int **)(currentPtr + 0x20) + 4))();
      }
      // Clear the ref counter pointer
      *(undefined4 *)(currentPtr + 0x20) = 0;
    }
    // Assign new pointer
    *(int *)(currentPtr + 0x20) = newPtr;
    if (newPtr != 0) {
      // Increment reference count on new object's ref counter
      *(int *)(newPtr + 4) = *(int *)(newPtr + 4) + 1;
    }
  }
  return;
}
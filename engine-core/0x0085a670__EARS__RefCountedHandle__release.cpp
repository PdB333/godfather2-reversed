// FUNC_NAME: EARS::RefCountedHandle::release
void __fastcall EARS::RefCountedHandle::release(int *this)
{
  // this layout:
  // +0x00: pointer to managed object (primary)
  // +0x04: reference count
  // +0x08: secondary pointer (e.g., embedded buffer)
  // +0x0C: pointer to virtual allocator (owns vtable)
  int *primaryObject = reinterpret_cast<int*>(this[0]);
  int *secondaryObject = reinterpret_cast<int*>(this[2]);
  void **allocator = reinterpret_cast<void**>(this[3]); // allocator with vtable

  if (primaryObject != nullptr) {
    // free sub-resources inside primary object at offsets +0x08 and +0x0C
    if (primaryObject[2] != 0) {
      freeSubObject(primaryObject[2]); // FUN_00859170
    }
    if (primaryObject[3] != 0) {
      freeSubObject(primaryObject[3]); // FUN_00859170
    }
    // call virtual release on allocator for primary object
    typedef void (__thiscall *ReleaseFunc)(void*, int);
    ReleaseFunc releaseFunc = (ReleaseFunc)(*((int*)allocator[0] + 1)); // vtable offset +4
    releaseFunc(primaryObject, 0);
    // decrement reference count
    this[1]--;
  }
  // nullify primary pointer
  this[0] = 0;

  // release secondary object if present
  if (secondaryObject != nullptr) {
    typedef void (__thiscall *ReleaseFunc)(void*, int);
    ReleaseFunc releaseFunc = (ReleaseFunc)(*((int*)allocator[0] + 1));
    releaseFunc(secondaryObject, 0);
  }

  // call virtual deallocate on allocator (likely frees the handle itself)
  typedef void (__thiscall *DeallocateFunc)();
  DeallocateFunc deallocFunc = (DeallocateFunc)(*((int*)allocator[0] + 3)); // vtable offset +0xC
  deallocFunc();
}
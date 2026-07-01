// FUNC_NAME: EARSObject::deletingDestructor
// Address: 0x007e1510
// __thiscall
int * __thiscall EARSObject::deletingDestructor(int *thisPtr, byte deleteFlag)
{
  // If the object's vtable pointer (first DWORD) is non-null, call the real destructor
  if (*thisPtr != 0) {
    EARSObject::destructor(thisPtr); // FUN_004daf90 - actual cleanup
  }
  // If the delete flag (bit 0) is set, deallocate the memory
  if ((deleteFlag & 1) != 0) {
    operator delete(thisPtr); // FUN_009c8eb0 - heap deallocation
  }
  return thisPtr;
}
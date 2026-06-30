// FUNC_NAME: DataHolder::~DataHolder
//
// Destructor for a class with a buffer pointer at +0x04.
// The vtable is updated to a base vtable, then the buffer pointer (if non-null)
// is decremented by 0x48 to retrieve the allocation header before releasing it.
// Finally, the object is deleted if param_2 & 1 is set.
//
// Typical pattern for EA EARS objects with custom heap allocation.

undefined4 * __thiscall DataHolder_~DataHolder(undefined4 *this, byte param_2)
{
  int *bufferPtr;        // piVar1 ; pointer at this+0x04
  int adjustment;        // iVar2  ; offset back to allocation header

  bufferPtr = (int *)(this + 1);           // this+0x04
  *this = &PTR_FUN_00d61fc4;               // set vtable to base class vtable

  if (*bufferPtr == 0) {
    adjustment = 0;
  }
  else {
    adjustment = *bufferPtr - 0x48;        // 0x48 = size of allocation header
  }

  // Release the allocation header reference (possibly decrement refcount or free)
  FUN_006f8d40(adjustment, 1);

  // Free the buffer if it was allocated
  if (*bufferPtr != 0) {
    FUN_004daf90(bufferPtr);               // free the buffer pointer itself?
    *bufferPtr = 0;
  }

  // Second free attempt (redundant in case of double-free bug?)
  if (*bufferPtr != 0) {
    FUN_004daf90(bufferPtr);
  }

  // Delete this object if the calling code requests it (param_2 & 1)
  if ((param_2 & 1) != 0) {
    FUN_009c8eb0(this);                    // operator delete(this)
  }

  return this;
}
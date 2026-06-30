// FUNC_NAME: BaseObject::~BaseObject
undefined4 * __thiscall BaseObject::~BaseObject(undefined4 *this, byte freeMemFlag)
{
  uint handle;
  
  // Switch vtable to base class's vtable (destructor chain)
  *this = &PTR_FUN_00e39c48;
  
  handle = this[6]; // +0x18: handle or index for resource cleanup
  
  // If handle is valid (>=0), release associated resource
  if (-1 < (int)handle) {
    // Get thread-local storage context (likely global memory manager)
    TlsGetValue(DAT_01139810);
    // Free resource: offset into memory pool (handle & 0x3FFFFFFF) * 0x60, type 0x17
    FUN_00aa26e0(this[4], (handle & 0x3fffffff) * 0x60, 0x17);
  }
  
  // Final vtable set to purecall to prevent any further virtual calls
  *this = &PTR___purecall_00dcfcf4;
  
  // If the free memory flag is set, deallocate the object itself
  if ((freeMemFlag & 1) != 0) {
    FUN_009c8eb0(this); // operator delete or custom deallocator
  }
  
  return this;
}
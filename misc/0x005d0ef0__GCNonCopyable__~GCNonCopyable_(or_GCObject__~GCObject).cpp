// FUNC_NAME: GCNonCopyable::~GCNonCopyable (or GCObject::~GCObject)
undefined4 * __thiscall GCObject_destructor(undefined4 *this, byte flags)

{
  char isDeallocated;
  
  *this = &PTR___purecall_00e3edb4;  // Set vtable to purecall
  if (this[0xb] != 0) {  // +0x2C - GC reference count/pointer
    (*g_gcManager->releaseObject)(this[0xb]);  // Release GC reference via global GC manager
  }
  this[0xb] = 0;  // Clear GC reference
  if ((flags & 1) != 0) {  // If delete flag is set
    isDeallocated = g_heapManager->checkAndDeallocate(this);  // Try to deallocate memory
    if (isDeallocated == '\0') {  // If not already deallocated
      (**(code **)(**(int **)(g_allocTable + 4) + 4))(this,0);  // Free via allocator table
    }
  }
  return this;
}
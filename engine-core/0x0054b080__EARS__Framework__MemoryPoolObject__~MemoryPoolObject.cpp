// FUNC_NAME: EARS::Framework::MemoryPoolObject::~MemoryPoolObject
undefined4* __thiscall MemoryPoolObject::~MemoryPoolObject(undefined4* this, byte flags)
{
  uint poolIndex;
  
  // Set vtable to this class's vtable (base class)
  *this = &PTR_FUN_00e39c48;
  
  // Check if the pool index (offset 0x18) is valid (>= 0)
  // poolIndex is stored as signed int, so negative means invalid
  poolIndex = this[6];
  if ((int)poolIndex >= 0) {
    // Get thread-local storage pointer for the memory manager context
    TlsGetValue(DAT_01139810);
    
    // Release the memory block pointed to by this[4] (offset 0x10)
    // The block size is (poolIndex & 0x3FFFFFFF) * 0x60 (0x60 bytes per slot)
    // The third argument 0x17 likely indicates a pool type or allocation ID
    FUN_00aa26e0(this[4], (poolIndex & 0x3FFFFFFF) * 0x60, 0x17);
  }
  
  // After child class destruction, set vtable to purecall to catch any post-destruction calls
  *this = &PTR___purecall_00dcfcf4;
  
  // If flags bit 0 is set, free the object memory
  if ((flags & 1) != 0) {
    FUN_009c8eb0(this);
  }
  
  return this;
}
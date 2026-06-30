// FUNC_NAME: EARSObject::constructor
int __thiscall EARSObject::constructor(int thisPtr, byte flags)
{
  // Base class or common initialization
  FUN_009f0cb0();
  
  // If bit 0 of flags indicates heap allocation, register the allocation
  // with the thread-local memory manager
  if ((flags & 1) != 0) {
    // Get the TLS value (likely a pointer to the current thread's memory manager)
    TlsGetValue(DAT_01139810);
    // Record the allocation: this pointer, size from offset +4, and object size 0x31
    FUN_00aa26e0(thisPtr, *(short *)(thisPtr + 4), 0x31);
  }
  
  return thisPtr;
}
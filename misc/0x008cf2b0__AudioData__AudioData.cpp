// FUNC_NAME: AudioData::AudioData

undefined4 * __thiscall AudioData::AudioData(void)

{
  undefined4 *allocatedMemory;
  undefined4 *lookupResult;
  undefined4 flags;
  undefined4 alignment;
  undefined4 zero;
  
  // Get the global memory allocator singleton
  allocatorSingleton = (undefined4 *)FUN_009c8f80();  // likely returns a pointer to a memory manager
  flags = 2;
  alignment = 0x10;
  zero = 0;
  // Allocate 0x80 bytes with alignment and flags via the allocator's vtable function
  allocatedMemory = (undefined4 *)(**(code **)*allocatorSingleton)(0x80, &flags);
  if (allocatedMemory != (undefined4 *)0x0) {
    // Call base class constructor (or initialization function) with flags
    FUN_00416a70(zero, unaff_retaddr);  // unaff_retaddr is likely 'this' but decompiler misidentified
    // Set vtable pointer for this class
    *allocatedMemory = &PTR_FUN_00d7ccb0;
    // Initialize field at offset 0x70 (0x1c * 4) to null
    allocatedMemory[0x1c] = 0;
    // Set byte at offset 0x74 (0x1d * 4) to 0
    *(undefined1 *)(allocatedMemory + 0x1d) = 0;
    // Look up a resource (or singleton) by hash 0xaa186cbc
    lookupResult = (undefined4 *)FUN_004a3790(0xaa186cbc);
    if (lookupResult != (undefined4 *)0x0) {
      // Store the looked-up value into the field at offset 0x70
      allocatedMemory[0x1c] = *lookupResult;
    }
    return allocatedMemory;
  }
  return (undefined4 *)0x0;
}
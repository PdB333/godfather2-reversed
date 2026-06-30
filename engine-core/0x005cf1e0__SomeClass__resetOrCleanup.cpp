// FUNC_NAME: SomeClass::resetOrCleanup
void SomeClass::resetOrCleanup(void)
{
  // Check if some resource/object exists (offset +0x0C from this)
  if (*(int*)((char*)this + 0x0C) != 0) {
    // Cleanup or release that resource
    FUN_005cf240();
  }
  
  // Call various cleanup/reset functions
  FUN_005d1090();  // Likely resets some subsystem
  FUN_005db540();  // Likely resets another subsystem
  FUN_005d0b90();  // Likely resets a third subsystem
  
  // Reset counters/state at offsets +0x08 and +0x04
  *(int*)((char*)this + 0x08) = 0;
  *(int*)((char*)this + 0x04) = 0;
  
  // If there's a pointer at offset +0x00, release it via some manager
  if (*(int*)this != 0) {
    // Call a release/destroy function through a vtable or global manager
    (**(code**)(**(int**)(DAT_012234ec + 4) + 4))(*(int*)this, 0);
  }
  
  // Null out the pointer at offset +0x00
  *(int*)this = 0;
  
  return;
}
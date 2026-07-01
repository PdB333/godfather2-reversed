// FUNC_NAME: AIBrainComponent::constructor
undefined4 __thiscall AIBrainComponent::constructor(undefined4 this, byte flags)
{
  // Call base class constructor or initialization function
  // FUN_008fbf30 is likely AIBrain::initialize() or similar
  FUN_008fbf30();
  
  // If the flag bit 0 is set, allocate or initialize additional memory
  // FUN_0043b960 is likely operator delete[] or EARS::Memory::deallocate
  // +0x130 is the allocation size in bytes (304 bytes)
  if ((flags & 1) != 0) {
    FUN_0043b960(this, 0x130);
  }
  
  return this;
}
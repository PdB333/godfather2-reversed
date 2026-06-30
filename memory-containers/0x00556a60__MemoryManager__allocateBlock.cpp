// FUNC_NAME: MemoryManager::allocateBlock
void __thiscall MemoryManager::allocateBlock(uint size, MemoryBlock* blockPtr, uint id)
{
  // Call internal setup with zero arguments and the given id, this pointer, and return address?
  // The fifth argument (in_EAX) is an artifact of the decompiler; original call likely passed 4 args.
  FUN_00556ab0(0, 0, id, this); // assumed corrected signature
  
  // Set block size field at offset 0x2c: size divided by 4 (shift right 2) with high flags (0xC0000000)
  blockPtr[0x0B] = (size >> 2) | 0xC0000000; // 0x2c / 4 = 0x0B (since field is 4 bytes)
  
  // Global initialization call
  FUN_0043b490();
  
  // Log or notify system with message 0x2001 using the id
  FUN_009f01f0(0x2001, id, 0);
}
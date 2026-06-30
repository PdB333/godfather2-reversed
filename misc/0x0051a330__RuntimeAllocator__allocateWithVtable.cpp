// FUNC_NAME: RuntimeAllocator::allocateWithVtable
void RuntimeAllocator::allocateWithVtable(undefined4 eaxParam)
{
  // This function appears to be a custom memory allocator that writes a vtable pointer
  // and then stores the provided EAX parameter (likely an object size or identifier)
  // into a sequential buffer located at g_globalAllocator + 0x14.

  // Call a sub-initializer (unknown purpose, possibly base init)
  sub_init();

  // Get a pointer to the allocator's current allocation pointer (g_globalAllocator + 0x1=14)
  int *allocPtr = (int *)(g_globalAllocator + 0x14); // +0x14: current allocation offset

  // Write the vtable address at the current allocation position
  **(undefined4 **)(g_globalAllocator + 0x14) = &VTABLE_SomeClass; // PTR_LAB_01125180

  // Advance the allocation pointer by 4 (size of vtable pointer)
  *allocPtr = *allocPtr + 4;

  // Align the next address to 4-byte boundary
  undefined4 *alignedSlot = (undefined4 *)((*allocPtr + 3) & 0xfffffffc);
  *allocPtr = (int)alignedSlot;

  // Write the EAX parameter into the aligned slot
  *alignedSlot = eaxParam;

  // Advance the allocation pointer past that slot
  *allocPtr = *allocPtr + 4;
}
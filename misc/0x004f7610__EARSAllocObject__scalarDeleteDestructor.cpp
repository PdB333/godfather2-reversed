// FUNC_NAME: EARSAllocObject::scalarDeleteDestructor
undefined4 * __thiscall EARSAllocObject::scalarDeleteDestructor(undefined4 *this, byte deleteFlag)
{
  int *allocNode;
  int *listPtr;
  
  // Set vtable pointer to the correct table (likely after destruction)
  *this = &PTR_FUN_00e37110;
  
  // Check if there is an active allocation node (offset +0x10)
  allocNode = this[4];
  if (allocNode != 0) {
    // Insert the node back into the free list managed by the global memory manager (DAT_01206880)
    // The manager has a linked list head at offset +0x14
    listPtr = (int *)(DAT_01206880 + 0x14);
    *(undefined ***)*listPtr = &PTR_LAB_01123be8;  // Set current node's next to something
    *listPtr = *listPtr + 4;                      // Advance list head
    *(int *)*listPtr = allocNode;                 // Store alloc node address
    *listPtr = *listPtr + 4;                      // Advance again
    this[4] = 0;  // Clear allocation pointer
    this[5] = 0;  // Clear associated size (offset +0x14)
  }
  
  // If flag indicates scalar delete, actually free the memory
  if ((deleteFlag & 1) != 0) {
    FUN_009c8eb0(this);  // operator delete or custom free
  }
  return this;
}
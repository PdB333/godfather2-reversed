// FUNC_NAME: PoolAllocator::allocateNode
void __thiscall PoolAllocator::allocateNode(void) {
  int *counterPtr;
  Node *newNode;

  // Allocate a 0x48-byte node from global memory
  newNode = (Node *)(*g_MemoryAllocFunc)(0, 0x48);
  
  if (newNode == (Node *)0x0) {
    // Allocation failed
    if (this != (PoolAllocator *)0x0) {
      // Error cleanup
      FUN_00635a80();
      return;
    }
    newNode = (Node *)0x0; // redundant
  }
  else {
    // Allocation succeeded; update total allocated size counter
    if (this != (PoolAllocator *)0x0) {
      counterPtr = (int *)(*(int *)(this + 0x10) + 0x24);
      *counterPtr = *counterPtr + 0x48;
    }
  }

  // Insert newNode at head of the free list (linked list header at (this+0x10)->+0x0C)
  newNode->next = *(Node **)(*(int *)(this + 0x10) + 0xC);
  *(Node ***)(*(int *)(this + 0x10) + 0xC) = &newNode->next; // actually sets the head to newNode

  // Zero-initialize all fields
  newNode->field_04 = 9;   // +0x04: byte set to 9 (default type?)
  newNode->field_05 = 0;   // +0x05: byte
  newNode->field_08 = 0;   // +0x08: dword
  newNode->field_0x28 = 0; // +0x28: dword (index 10)
  newNode->field_0x10 = 0; // +0x10: dword (index 4)
  newNode->field_0x34 = 0; // +0x34: dword (index 0xD)
  newNode->field_0x0C = 0; // +0x0C: dword (index 3)
  newNode->field_0x2C = 0; // +0x2C: dword (index 0xB)
  newNode->field_0x30 = 0; // +0x30: dword (index 0xC)
  newNode->field_0x24 = 0; // +0x24: dword (index 9)
  newNode->field_0x44 = 0; // +0x44: byte (index 0x11)
  newNode->field_0x1C = 0; // +0x1C: dword (index 7)
  newNode->field_0x45 = 0; // +0x45: byte
  newNode->field_0x46 = 0; // +0x46: byte
  newNode->field_0x47 = 0; // +0x47: byte
  newNode->field_0x14 = 0; // +0x14: dword (index 5)
  newNode->field_0x38 = 0; // +0x38: dword (index 0xE)
  newNode->field_0x18 = 0; // +0x18: dword (index 6)
  newNode->field_0x3C = 0; // +0x3C: dword (index 0xF)
  newNode->field_0x20 = 0; // +0x20: dword (index 8)
}
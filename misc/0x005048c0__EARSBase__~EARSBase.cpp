// FUNC_NAME: EARSBase::~EARSBase
void __thiscall EARSBase::~EARSBase(EARSBase *this)
{
  EARSBase *child;
  EARSNode *nextNode;
  int *freePtr;

  // Set initial vtable (destructor step 1)
  *(int *)this = &VTable_00e37f3c;

  // Destroy child object at offset 0x98 (0x26 * 4)
  child = *(EARSBase **)((char *)this + 0x98);
  if (child != nullptr) {
    childDtor(child);
    *(EARSBase **)((char *)this + 0x98) = nullptr;
  }

  // Remove this node from a doubly linked list
  // Offsets: +0x28 = prev, +0x2C = next
  *(EARSBase **)((char *)this->next + 0x28) = this->prev; // next->prev = prev
  *(EARSBase **)((char *)this->prev + 0x2C) = this->next; // prev->next = next

  // Remove all children from a child list (range [head, tail) at offsets 0x30 and 0x38)
  while (this->childListHead != this->childListTail) {
    EARSNode *node = this->childListHead; // offset 0x30 (0xc * 4)
    if (node->someField != nullptr) { // node+0x10
      // Unlink node: update previous and next (assuming list node at node+0x10, prev at node+0x14, next at node+0x10?)
      *(int *)(node->prev + 0x10) = node->next; // prev->next = next
      *(int *)(node->next + 0x14) = node->prev; // next->prev = prev
      node->next = nullptr; // node->next = 0
      node->prev = nullptr; // node->prev = 0 // Actually only sets next to 0
    }
  }

  // Add pointer at offset 0x24 (9 * 4) to a global free list (for allocation tracking)
  freePtr = *(int **)((char *)this + 0x24);
  if (freePtr != nullptr) {
    int **listEnd = (int **)(DAT_012068e8 + 0x14); // Global allocator free list pointer
    **(int ***)(DAT_012068e8 + 0x14) = &VTable_01124ba8; // Store vtable? Actually stores a vtable address? Hmm
    *listEnd = *listEnd + 4; // advance pointer (strange increment)
    *(int *)*listEnd = (int)freePtr;
    *listEnd = *listEnd + 4;
    *(int **)((char *)this + 0x24) = nullptr;
  }

  // Set vtable to next destructor step
  *(int *)this = &VTable_00e37f48;

  // Remove another linked list node (e.g., from parent's child list)
  // Offsets: +0x10 = prev, +0x14 = next? Actually fields at 0x10 and 0x14
  if (this->nodePrev != nullptr) { // offset 0x10 (4 * 4)
    *(EARSBase **)((char *)this->nodeNext + 0x10) = this->nodePrev; // next->prev = prev
    *(EARSBase **)((char *)this->nodePrev + 0x14) = this->nodeNext; // prev->next = next
    this->nodePrev = nullptr;
  }

  // Final vtable (probably destructor complete)
  *(int *)this = &VTable_00e37304;
}
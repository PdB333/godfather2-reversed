// FUNC_NAME: MemoryManager::freeNode
// Address: 0x005e0ff0
// Role: Frees a memory node from a custom memory pool/allocator.
// Handles merging with adjacent free nodes to reduce fragmentation and
// updates the free list (doubly linked list). 
void __thiscall MemoryManager::freeNode(int node, int pool)
{
  int* freeHead;
  int* nextFree;

  // The node being freed is at address param_1 (node)
  // The pool/memory block descriptor is at param_2 (pool)
  
  // Remove node from the free list? Let's read the logic carefully.
  // param_1 = node being freed
  // param_2 = pool descriptor (has a free list head? at +0x1c)
  
  // *(int **)(param_1 + 8) is the 'next' pointer of the free node? 
  // Or maybe it's the 'size' field and we are checking if the next chunk is also free?
  // Given this is a free function, likely we are merging with the next free block.
  // In a simple buddy or slab allocator, each node has a header with flags.
  // Let's assume node layout:
  // +0x00: previous_free_or_prev_node (some kind of list pointer)
  // +0x04: next_free_or_next_node
  // +0x08: possibly size or 'next' in a different list? Or maybe a flag at +0x15?
  
  nextFree = *(int**)(node + 8);  // dereference as pointer, so this is likely the 'next' pointer to another node block
  *(int*)(node + 8) = *nextFree;   // set this node's next to the node after nextFree? Very odd.
  
  // Check if the block at address nextFree is free (flag at offset 0x15)
  if (*(char*)(*nextFree + 0x15) == '\0') {
    // The block at nextFree is also free, so we merge.
    // Set the 'prev' of some list? Or update the size?
    *(int*)(*nextFree + 4) = node;
  }
  
  // Set this node's 'next' in the free list to whatever is at node+4 (previous or something)
  nextFree[1] = *(int*)(node + 4);
  
  // The pool descriptor likely has a free list head at +0x1c.
  // Check if the node being freed is adjacent to the current free list head? 
  if (node == *(int*)(*(int*)(pool + 0x1c) + 4)) {
    // Insert node before the free list head.
    *(int**)(*(int*)(pool + 0x1c) + 4) = nextFree;
    *nextFree = node;
    *(int**)(node + 4) = nextFree;
    return;
  }
  
  // Otherwise, we need to insert node into the free list.
  int* prevFree = *(int**)(node + 4);
  if (node == *prevFree) {
    // node is already after prevFree? Then we don't need to change the list order.
    *prevFree = (int)nextFree;
    *nextFree = node;
    *(int**)(node + 4) = nextFree;
    return;
  }
  
  // Otherwise, we insert node between prevFree and whatever comes after prevFree
  prevFree[2] = (int)nextFree;
  *nextFree = node;
  *(int**)(node + 4) = nextFree;
  return;
}
// FUNC_NAME: MemoryPool::freeNode
int * __thiscall MemoryPool::freeNode(int *this, int *node, int poolHeader, int *freeList)
{
  int current;
  int prev;
  
  current = *(int *)(poolHeader + 8);  // +0x8: next free node
  node[1] = (int)freeList;             // +0x4: store free list pointer
  *node = current;                     // +0x0: store current free node
  
  while (current == 0) {               // If current is null, advance freeList
    node[1] = node[1] + 4;
    current = *(int *)node[1];
    *node = current;
  }
  
  current = *freeList;
  if (current == poolHeader) {
    *freeList = *(int *)(current + 8);  // +0x8: next pointer
  }
  else {
    for (prev = *(int *)(current + 8); prev != poolHeader; prev = *(int *)(prev + 8)) {
      current = prev;
    }
    *(int *)(current + 8) = *(int *)(prev + 8);  // +0x8: unlink from list
  }
  
  FUN_009c8f10(poolHeader);  // Free the pool header memory
  
  *(int *)(this + 0xc) = *(int *)(this + 0xc) - 1;  // +0xc: decrement allocation count
  
  return node;
}
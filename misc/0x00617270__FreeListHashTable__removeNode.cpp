// FUNC_NAME: FreeListHashTable::removeNode
int __thiscall FreeListHashTable::removeNode(uint key)
{
  uint *bucketArray;
  uint *node;
  uint *prevNode;
  uint bucketIndex;

  bucketIndex = key % *(uint *)(this + 4);              // modulus
  bucketArray = *(uint **)(this + 8);                   // bucket array base
  node = (uint *)bucketArray[bucketIndex];
  prevNode = (uint *)0x0;
  while( true ) {
    if (node == (uint *)0x0) {
      return 1;
    }
    if (*node == key) break;
    prevNode = node;
    node = (uint *)node[2];                             // +0x8: next pointer in hash chain
  }
  // Remove node from hash chain
  if (prevNode != (uint *)0x0) {
    prevNode[2] = (uint)node[2];
    node[2] = *(uint *)(this + 0xc);                    // +0xC: free list head
    *(int *)(this + 0x10) = *(int *)(this + 0x10) - 1; // +0x10: node count
    *(uint **)(this + 0xc) = node;                      // add to free list
    return 0;
  }
  bucketArray[bucketIndex] = (uint)node[2];
  node[2] = *(uint *)(this + 0xc);
  *(int *)(this + 0x10) = *(int *)(this + 0x10) - 1;
  *(uint **)(this + 0xc) = node;
  return 0;
}
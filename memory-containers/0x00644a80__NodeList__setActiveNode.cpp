// FUNC_NAME: NodeList::setActiveNode
// This function manages a doubly linked list of nodes (likely free list or block pool).
// The class has:
//   +0x30: sentinel node (head)
//   +0x3c: pointer to first real node after sentinel
//   +0x440: current active node pointer
//   +0x468: computed data pointer (active node's embedded block address)
//   +0x46c: flag (if zero, compute data pointer from active node)
// Node structure (at param_2):
//   +0x4: block size
//   +0x8: prev pointer
//   +0xc: next pointer

void __thiscall NodeList::setActiveNode(int thisPtr, int newBlock, char recycleOld)
{
  int oldBlock = *(int *)(thisPtr + 0x440);
  *(int *)(thisPtr + 0x440) = newBlock;
  *(int *)(newBlock + 0xc) = newBlock;
  *(int *)(*(int *)(thisPtr + 0x440) + 8) = *(int *)(*(int *)(thisPtr + 0x440) + 0xc);

  if ((oldBlock != thisPtr + 0x30) && (recycleOld != '\0')) {
    int nextAfterHead = *(int *)(thisPtr + 0x3c);
    *(int *)(oldBlock + 8) = thisPtr + 0x30;
    *(int *)(oldBlock + 0xc) = nextAfterHead;
    *(int *)(thisPtr + 0x3c) = oldBlock;
    *(int *)(nextAfterHead + 8) = oldBlock;
  }

  if (*(char *)(thisPtr + 0x46c) == '\0') {
    int activeNode = *(int *)(thisPtr + 0x440);
    int sizeField = *(int *)(activeNode + 4);
    int dataOffset = (sizeField >> 1) & 0x3ffffffc;
    *(uint *)(thisPtr + 0x468) = activeNode + dataOffset;
  }
}
// FUNC_NAME: MemoryPool::freeNode
void __fastcall MemoryPool::freeNode(int this, int **freeList)
{
  int currentNode;
  uint switchValue;

  *(byte *)(this + 5) = *(byte *)(this + 5) | 1;  // Mark node as freed (bit 0)
  switchValue = *(byte *)(this + 4) - 5;  // Get node type (offset 0x04)
  if (4 < switchValue) {
    return;
  }
  while( true ) {
    switch((&switchTable_00626650)[switchValue]) {
    case 0x626671:  // Type 0: small node (8 bytes)
      *(int *)(this + 8) = *freeList;  // +0x08: next pointer
      *freeList = this;
      return;
    case 0x626679:  // Type 1: medium node (24 bytes)
      *(int *)(this + 0x18) = *freeList;  // +0x18: next pointer
      *freeList = this;
      return;
    case 0x626681:  // Type 2: large node (76 bytes)
      *(int *)(this + 0x4c) = *freeList;  // +0x4c: next pointer
      *freeList = this;
      return;
    case 0x626689:  // Type 3: extra large node (64 bytes)
      *(int *)(this + 0x40) = *freeList;  // +0x40: next pointer
      *freeList = this;
      return;
    }
    currentNode = *(int *)(this + 8);  // Follow next pointer
    if ((*(byte *)(currentNode + 5) & 0x11) != 0) break;  // Check if already freed or special
    *(byte *)(currentNode + 5) = *(byte *)(currentNode + 5) | 1;  // Mark as freed
    switchValue = *(byte *)(currentNode + 4) - 5;
    if (4 < switchValue) {
      return;
    }
  }
  return;
}
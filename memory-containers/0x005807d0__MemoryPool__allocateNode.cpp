// FUNC_NAME: MemoryPool::allocateNode
undefined8* MemoryPool::allocateNode(int param_1)
{
  int baseAddr;
  uint blockSize;
  undefined8* currentBlock;
  undefined8* blockEnd;
  short sizeWord;
  uint requiredSize;
  undefined4* freeBlock;
  undefined4* iterBlock;
  undefined4* bestBlock;

  baseAddr = DAT_01205588;
  blockSize = (param_1 + 1) * 0x10;
  currentBlock = *(undefined8**)(baseAddr + 8);
  blockEnd = currentBlock + (param_1 + 1) * 2;

  sizeWord = (short)blockSize;

  // Check if there is space in the current block
  if (blockEnd <= (undefined8*)(*(int*)(baseAddr + 0x10) + (int)*(undefined8**)(baseAddr + 0xc))) {
    // Allocate from current block
    if (currentBlock == (undefined8*)0x0) {
      currentBlock = (undefined8*)0x0;
    } else {
      *currentBlock = 0;
      currentBlock[1] = 0;
    }

    // Initialize the node structure (offsets relative to byte pointer)
    *(int*)currentBlock = *(int*)(baseAddr + 4);           // +0: next = previous head
    *(int*)((int)currentBlock + 4) = 0;                    // +4: prev = NULL
    *(byte*)(currentBlock + 1) = 0;                         // +8: flags? or alignment
    *(byte*)((int)currentBlock + 9) = 1;                    // +9: inUse flag?
    *(short*)((int)currentBlock + 10) = sizeWord;           // +10: block size
    *(int*)((int)currentBlock + 12) = param_1;              // +12: index / pool ID

    // Link into the free list (insert at head)
    if (*(int*)(baseAddr + 4) != 0) {
      *(int*)(*(int*)(baseAddr + 4) + 4) = (int)currentBlock; // old head->prev = new node
    }
    *(int*)(baseAddr + 8) = (int)blockEnd;                   // update current block end
    *(int*)(baseAddr + 4) = (int)currentBlock;               // update head
    return currentBlock;
  }

  // No space in current block, scan the free list for a suitable block
  freeBlock = *(undefined4**)(*(int*)(baseAddr + 4));   // first free block
  iterBlock = *(undefined4**)(baseAddr + 4);             // iterator start (head)

  while (true) {
    bestBlock = freeBlock;
    currentBlock = *(undefined8**)(baseAddr + 0xc);       // end of current region?

    if (bestBlock != (undefined4*)0x0) {
      currentBlock = (undefined8*)((uint)*(ushort*)((int)bestBlock + 10) + (int)bestBlock);
    }

    if (blockSize <= (uint)((int)iterBlock - (int)currentBlock)) {
      break;
    }

    if (bestBlock == (undefined4*)0x0) {
      return (undefined8*)0x0;  // allocation failure
    }

    freeBlock = (undefined4*)*freeBlock;   // move to next block in free list
    iterBlock = bestBlock;                 // update iterator
  }

  // Found a free slot; carve the node from the end of the block
  if (currentBlock == (undefined8*)0x0) {
    currentBlock = (undefined8*)0x0;
  } else {
    *currentBlock = 0;
    currentBlock[1] = 0;
  }

  *(short*)((int)currentBlock + 10) = sizeWord;
  *(int*)currentBlock = (int)bestBlock;               // next = bestBlock
  *(int*)((int)currentBlock + 4) = (int)iterBlock;    // prev = iterBlock
  *(byte*)(currentBlock + 1) = 0;
  *(byte*)((int)currentBlock + 9) = 1;
  *(int*)((int)currentBlock + 12) = param_1;

  if (bestBlock != (undefined4*)0x0) {
    *(int*)((int)bestBlock + 4) = (int)currentBlock;   // bestBlock->prev = new node
  }
  *(int*)iterBlock = (int)currentBlock;                  // iterBlock->next = new node

  return currentBlock;
}
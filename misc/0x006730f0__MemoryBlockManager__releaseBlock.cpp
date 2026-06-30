// FUNC_NAME: MemoryBlockManager::releaseBlock
undefined1 * __thiscall MemoryBlockManager::releaseBlock(int this, void *blockPtr, uint size)
{
  // this: pointer to MemoryBlockManager
  // blockPtr: pointer to user data block (preceded by 16-byte header, header contains index at offset +8)
  // size: expected size of block, but actual size may be smaller (from in_EAX)
  undefined1 *destPtr;
  undefined1 *currentDest;
  uint actualSize;

  // Get a destination pointer (possibly a free slot or compaction target)
  destPtr = (undefined1 *)this->getNextFreeSlot(); // FUN_00673070

  if (blockPtr != 0) {
    // Determine actual size to copy (likely from in_EAX, which is the real block size stored in header)
    if (in_EAX < size) {
      actualSize = in_EAX;
    } else {
      actualSize = size;
    }
    if (0 < (int)actualSize) {
      // Copy block data to the new location (probably compaction/move to free list)
      currentDest = destPtr;
      do {
        *currentDest = currentDest[(int)blockPtr - (int)destPtr]; // equivalent to memcpy(dest, blockPtr, actualSize)
        currentDest = currentDest + 1;
        actualSize = actualSize - 1;
      } while (actualSize != 0);
    }
    // Clear the index table entry (block table is at this+0xC)
    *(undefined4 *)(*(int *)(this + 0xc) + *(int *)((int)blockPtr - 8) * 4) = 0;
    // Decrement used count
    *(int *)(this + 4) = *(int *)(this + 4) - 1;
    // Actually free the header (16-byte header at blockPtr - 0x10) via global deallocator
    (*g_deallocFunc)((int)blockPtr - 0x10);
  }
  return destPtr;
}
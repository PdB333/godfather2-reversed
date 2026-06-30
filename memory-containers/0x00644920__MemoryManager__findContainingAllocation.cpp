// FUNC_NAME: MemoryManager::findContainingAllocation
uint __fastcall MemoryManager::findContainingAllocation(uint address, int heapBase)
{
  uint blockSize;
  
  // Check if address is in a small block (size < 16 bytes, aligned to 8)
  blockSize = *(uint *)(address + 4) & 0x7ffffff8;
  if (blockSize < 0x10) {
    // Iterate through the free list / allocation list at heapBase+0x448
    // The list is a linked list with next pointer at +0x18
    for (blockSize = *(uint *)(heapBase + 0x460); 
         blockSize != (uint)(heapBase + 0x448);
         blockSize = *(uint *)(blockSize + 0x18)) {
      // Check if address falls within this allocation block
      // Block header at blockSize, data starts at blockSize+4, size stored at blockSize+4
      if ((blockSize <= address) && (address < *(int *)(blockSize + 4) + blockSize)) {
        // Calculate the end of usable data (size - 16 + base)
        blockSize = *(int *)(blockSize + 4) + -0x10 + blockSize;
        if (blockSize <= address) {
          // Address is in the last 16 bytes of the block - return with flag bit set
          return CONCAT31((int3)(blockSize >> 8), 1);
        }
        break;
      }
    }
  }
  // Return block size with lower byte cleared (alignment mask)
  return blockSize & 0xffffff00;
}
// FUNC_NAME: MemoryPool::freeOrRecycleBlock
void MemoryPool::freeOrRecycleBlock(uint *block)
{
  uint *poolList;
  byte index;
  uint mask;
  uint *nextBlock;

  index = *(byte *)((int)block + 0x1d); // +0x1d: block's pool index (bit field in header)
  mask = __allshl(); // shift left by index to get bit mask for free list bitmap
  
  // Clear the bit in the pool's allocated bitmap at index*8 offset
  poolList = (uint *)(DAT_0120550c + index * 8);
  *poolList = *poolList & ~mask;
  poolList = (uint *)(DAT_0120550c + 4 + index * 8);
  *poolList = *poolList & ~(mask >> 0x20); // clear upper 32 bits as well

  // Get the free list head from pool manager (at +0x90)
  poolList = *(uint **)(DAT_0120550c + 0x90); // +0x90: pool manager's free list array
  
  nextBlock = (uint *)*poolList; // first entry in free list (head pointer?)
  
  if (nextBlock != (uint *)0x0) {
    // If there's a custom destructor (at +0x1c in pool manager struct)
    if (((int *)poolList[7] != (int *)0x0) && // +0x1c: destructor function pointer? (offset 7 * 4 = 0x1c)
       ((block < nextBlock || // block belongs to a range that has a destructor
         ((uint *)(poolList[1] + (int)nextBlock) <= block)))) {
      // Call destructor on the block
      (**(code **)(*(int *)poolList[7] + 8))(block);
      return;
    }
    // Otherwise, push block to free list (stack-like LIFO)
    *block = poolList[2]; // +0x08: next free pointer in block? (offset 2 * 4 = 8)
    poolList[5] = poolList[5] + 1; // +0x14: free list count (offset 5 * 4 = 0x14)
    poolList[2] = (uint)block; // update head to new block
  }
  return;
}
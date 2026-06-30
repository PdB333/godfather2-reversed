// FUNC_NAME: MemoryPool::free
void __thiscall MemoryPool::free(void* ptr)
{
  uint* pool = this; // param_1 in decompiled code
  uint* ptrToFree = (uint*)ptr; // unaff_ESI in decompiled code
  uint* blockBase;
  uint* blockDesc;
  int i;

  if ((ptrToFree != (uint*)0x0) && (blockBase = (uint*)*pool, blockBase != (uint*)0x0)) {
    // Check if there is an overflow handler for large allocations and if ptr is outside the first block
    if ((pool[4] != 0) &&
        ((ptrToFree < blockBase || (blockBase + (pool[1] >> 2) <= ptrToFree)))) {
      // Call the overflow handler (vtable+8)
      (**(code (__thiscall **)(int))(*(int*)pool[4] + 8))();
      return;
    }

    blockDesc = (uint*)0x0;
    i = 0;
    if (0 < (int)pool[2]) {
      do {
        if (blockDesc != (uint*)0x0) goto LAB_FoundBlock;
        blockDesc = *(uint**)(pool[3] + i * 4);
        if (((uint*)*blockDesc <= ptrToFree) &&
            (ptrToFree < (uint*)(blockDesc[1] + (int)*blockDesc))) {
          // Found the block containing the pointer
          goto LAB_FoundBlock;
        }
        i = i + 1;
      } while (i < (int)pool[2]);

      if (blockDesc != (uint*)0x0) {
LAB_FoundBlock:
        blockBase = (uint*)*blockDesc;
        if (blockBase != (uint*)0x0) {
          // Check if the block has its own overflow handler
          if (((int*)blockDesc[7] != (int*)0x0) &&
              ((ptrToFree < blockBase || (blockBase + (blockDesc[1] >> 2) <= ptrToFree)))) {
            // Call the block's overflow handler
            (**(code (__thiscall **)(int))(*(int*)blockDesc[7] + 8))();
            return;
          }
          // Insert the freed pointer into the free list of this block
          *ptrToFree = blockDesc[2];          // next free block
          blockDesc[5] = blockDesc[5] + 1;    // increment allocation count
          blockDesc[2] = (uint)ptrToFree;     // new head of free list
        }
      }
    }
  }
  return;
}
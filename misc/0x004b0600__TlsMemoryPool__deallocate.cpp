// FUNC_NAME: TlsMemoryPool::deallocate
// Address: 0x004b0600
// Role: Thread-local memory pool deallocation. Adds a block to the free list if
//   capacity allows, otherwise delegates to global deallocation (FUN_00aa21e0).
//   TLS structure offsets: +0x34 = totalCapacity, +0x90 = freeListHead, +0x94 = freeCount.
//   param_2 bit 0: if set, performs pool deallocation (when param_1 != 0).
void * __thiscall TlsMemoryPool::deallocate(void *block, byte flags)
{
  threadInitCheck(); // FUN_004b0580 - ensures TLS is set up

  if ((flags & 1) != 0 && block != 0)
  {
    // Retrieve thread-local storage data
    TlsPoolData *tlsData = (TlsPoolData *)TlsGetValue(gTlsIndex); // DAT_01139810

    // If pool is already at capacity, free to global heap
    if (tlsData->totalCapacity <= tlsData->freeCount) // totalCapacity at +0x34, freeCount at +0x94
    {
      globalDeallocate(0xb, block, 0x1f); // FUN_00aa21e0 (likely global free)
      return block;
    }

    // Otherwise, add block to thread-local free list
    tlsData->freeCount++;                // freeCount at +0x94
    *(void **)block = tlsData->freeListHead; // store previous head in block (for linked list)
    tlsData->freeListHead = block;       // update head to this block (+0x90)
  }

  return block;
}
// FUNC_NAME: WorkQueue::enqueueDeferredPacket
void WorkQueue::enqueueDeferredPacket(void *packetData)
{
  uint *bumpPoolPtr = (uint *)(g_ThreadLocalBumpPool + 0x14); // Base of thread-local bump allocator
  uint *allocBlock;

  // Check thread-local flag (offset +0x34 in TLB structure at FS:0x2c)
  if (*(int *)(**(int **)(__readfsdword(0x2c) + 0x34)) == 0)
  {
    // Fast path: allocate from thread-local bump pool
    // Write vtable pointer to current free block
    **(undefined4 **)(g_ThreadLocalBumpPool + 0x14) = &PTR_LAB_01127744; // Default vtable or callback
    *bumpPoolPtr += 4; // Advance past vtable pointer

    // Align to next 4-byte boundary
    allocBlock = (uint *)((*bumpPoolPtr + 3) & 0xfffffffc);
    *bumpPoolPtr = (uint)allocBlock;

    // Store the packet data
    *allocBlock = (uint)packetData;

    // Advance bump pointer further (reserve space for data)
    *bumpPoolPtr += 4;

    // No need to link into queue – thread will process later
    return;
  }

  // Slow path: use global free list and queue
  undefined4 *freeBlock = (undefined4 *)g_FreeListHead;
  if (g_FreeListHead == NULL)
  {
    do {
      spinYield(); // Wait until memory becomes available (spinlock)
      freeBlock = (undefined4 *)g_FreeListHead;
    } while (g_FreeListHead == NULL);
  }

  // Unlink from free list (offset +12 is next pointer)
  g_FreeListHead = (undefined *)freeBlock[3];
  freeBlock[3] = 0; // Clear next pointer

  // Initialize block: place trampoline address, packet data, and clear status
  freeBlock[0] = (undefined4)&LAB_00615e50; // Trampoline function that will process this packet
  freeBlock[1] = (undefined4)packetData;    // The actual data to process
  freeBlock[2] = 0;                         // Status or arguments (unused)

  // Append block to global work queue (FIFO)
  if (g_WorkQueueTail != NULL)
  {
    // Link current tail's next to this new block
    *(undefined4 **)((int)g_WorkQueueTail + 0xc) = freeBlock;
    g_WorkQueueTail = freeBlock;
  }
  else
  {
    // Queue was empty – set both head and tail
    g_WorkQueueHead = freeBlock;
    g_WorkQueueTail = freeBlock;
  }
}
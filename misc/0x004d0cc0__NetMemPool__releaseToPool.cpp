// FUNC_NAME: NetMemPool::releaseToPool
void NetMemPool::releaseToPool(void)
{
  LPCRITICAL_SECTION lpCriticalSection;
  NetMemBlock *unaff_ESI;
  int in_EAX; // identifier for matching
  undefined4 *puVar1; // current block

  // +0x4c: poolHead (pointer to first block in pool list)
  puVar1 = *(undefined4 **)(unaff_ESI + 0x4c);
  if (puVar1 != (undefined4 *)0x0) {
    // Walk the pool list looking for the block matching in_EAX (the block to release)
    while (puVar1[0x2b] != in_EAX) { // +0xac: block identifier
      puVar1 = (undefined4 *)*puVar1; // next block pointer
      if (puVar1 == (undefined4 *)0x0) {
        return;
      }
    }
    lpCriticalSection = (LPCRITICAL_SECTION)(unaff_ESI + 0x68); // +0x68: critical section
    EnterCriticalSection(lpCriticalSection);
    FUN_004d1ea0(); // removeFromList or similar
    if (puVar1[0x2c] == 0) { // +0xb0: reference count
      FUN_004d1820(); // addToFreeList
      // Insert block into free list (doubly-linked list at +0x5c/+0x60)
      *puVar1 = *(undefined4 *)(unaff_ESI + 0x5c); // next = freeListHead->next
      puVar1[1] = 0; // prev = NULL
      if (*(int *)(unaff_ESI + 0x5c) != 0) {
        *(undefined4 **)(*(int *)(unaff_ESI + 0x5c) + 4) = puVar1; // old head->prev = this
        *(undefined4 **)(unaff_ESI + 0x5c) = puVar1; // freeListHead = this
        LeaveCriticalSection(lpCriticalSection);
        return;
      }
      *(undefined4 **)(unaff_ESI + 0x60) = puVar1; // freeListTail = this
      *(undefined4 **)(unaff_ESI + 0x5c) = puVar1; // freeListHead = this
      LeaveCriticalSection(lpCriticalSection);
      return;
    }
    // Block still has references, mark as pending release
    puVar1[0x2a] = puVar1[0x2a] | 2; // +0xa8: flags |= 2 (pendingRelease)
    if (puVar1[0x2c] == 2) { // reference count exactly 2?
      FUN_004d1a30(); // conditionalFree or attemptDeferredFree
    }
    if (puVar1 == *(undefined4 **)(unaff_ESI + 0x48)) { // +0x48: currentBlock pointer
      *(undefined4 *)(unaff_ESI + 0x48) = 0;
      FUN_004d0870(); // advanceCurrentBlock
    }
    // Move block to cleanup list (doubly-linked at +0x54/+0x58)
    *puVar1 = 0; // next = NULL
    puVar1[1] = *(undefined4 *)(unaff_ESI + 0x58); // prev = cleanupListTail->prev
    if (*(undefined4 **)(unaff_ESI + 0x58) != (undefined4 *)0x0) {
      **(undefined4 **)(unaff_ESI + 0x58) = puVar1; // old tail->next = this
      *(undefined4 **)(unaff_ESI + 0x58) = puVar1; // cleanupListTail = this
      LeaveCriticalSection(lpCriticalSection);
      return;
    }
    *(undefined4 **)(unaff_ESI + 0x54) = puVar1; // cleanupListHead = this
    *(undefined4 **)(unaff_ESI + 0x58) = puVar1; // cleanupListTail = this
    LeaveCriticalSection(lpCriticalSection);
  }
  return;
}
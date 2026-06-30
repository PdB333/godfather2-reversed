// FUNC_NAME: TNLConnection::flushLists
undefined4 __thiscall TNLConnection::flushLists(void) {
  int iVar1;
  int *listNode;
  int *headPtr;
  int dataPtr;
  undefined4 retVal;
  // unaff_ESI is the 'this' pointer
  // Offsets: +0x00: vtable
  // +0x04: pointer to a mutex/critical section object
  // +0x08: pointer to first list (e.g., send queue)
  // +0x0C: pointer to second list (e.g., receive queue)

  retVal = 0;
  if ((*(int *)(this + 0x08) != 0) && (*(int *)(this + 0x0C) != 0)) {
    // Loop through the first list at offset +0x08
    // The list object has a head pointer at offset +0x20 (possibly a sentinel node)
    iVar1 = *(int *)(*(int *)(this + 0x08) + 0x20);
    while (iVar1 != 0) {
      // Re-fetch list handle (loop invariant)
      iVar1 = *(int *)(this + 0x08);
      // Get the pointer to the head node's link pointer (offset +0x1C)
      listNode = **(int ***)(iVar1 + 0x1C);
      headPtr = *(int **)(iVar1 + 0x1C);
      if (*headPtr == (int)headPtr) {
        // Empty list assertion (linked list sentinel)
        assertionFailed();
      }
      // Save data pointer from node at offset +0x10 (4th int)
      dataPtr = headPtr[4];
      // Remove node from list (or process it)
      removeNodeFromList(*(void **)(this + 0x08), (void *)iVar1, (void *)headPtr);
      // If mutex exists and data pointer is non-null, destroy the data
      if ((*(int *)(this + 0x04) != 0) && (dataPtr != 0)) {
        lockMutex();          // Assume FUN_005dcdc0
        deallocate(dataPtr);  // Assume FUN_009c8eb0 (free)
      }
      // Refresh head pointer
      iVar1 = *(int *)(*(int *)(this + 0x08) + 0x20);
    }
    // Deallocate the first list object
    iVar1 = *(int *)(this + 0x08);
    if (iVar1 != 0) {
      clearList(iVar1);       // Assume FUN_005deac0 clears internal state
      deallocate(iVar1);      // free list object
    }
    iVar1 = *(int *)(this + 0x0C);
    *(undefined4 *)(this + 0x08) = 0;
    // Deallocate the second list object
    if (iVar1 != 0) {
      clearList(iVar1);       // Assume FUN_005df0e0
      deallocate(iVar1);
    }
    *(undefined4 *)(this + 0x0C) = 0;
    // Call virtual destructor on mutex object (offset +0x0C of vtable)
    if (*(int **)(this + 0x04) != (int *)0x0) {
      (**(code **)(**(int **)(this + 0x04) + 0x0C))();
      *(undefined4 *)(this + 0x04) = 0;
    }
    retVal = 1;
  }
  return retVal;
}
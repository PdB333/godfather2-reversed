// FUNC_NAME: SomeAllocator::popFreeBlock
undefined4 * __fastcall SomeAllocator::popFreeBlock(int this)
{
  undefined4 *freeBlock;
  undefined4 nextBlock;
  
  // If the free list is empty (head is null) and the block list is either empty or not marked as free
  if ((*(int *)(this + 0x34) == 0) &&
     ((*(int *)(this + 0x30) == 0 || ((*(byte *)(this + 0x24) & 1) == 0)))) {
    // Call some function to allocate more blocks (e.g., grow the pool)
    FUN_004de190();
  }
  
  freeBlock = *(undefined4 **)(this + 0x34); // +0x34: free list head pointer
  if (freeBlock != (undefined4 *)0x0) {
    nextBlock = *freeBlock; // First 4 bytes of block point to next free block
    *(int *)(this + 0x10) = *(int *)(this + 0x10) + 1; // +0x10: allocated count
    *(int *)(this + 0xc) = *(int *)(this + 0xc) + -1;  // +0x0c: free count
    *(undefined4 *)(this + 0x34) = nextBlock; // Update free list head
    return freeBlock;
  }
  
  return (undefined4 *)0x0;
}
// FUNC_NAME: MemoryBlockManager::freeBlocks
void MemoryBlockManager::freeBlocks(void)
{
  int *ppBufferInfo; // pointer to buffer info structure at this+0x10
  int iFirstElement; // first element of array
  int iSizeAdjust; // size adjustment value
  int *pSizeCounter; // pointer to size counter at +0x24

  FUN_006382a0(); // likely critical section enter or lock
  if (*(int *)(this + 0x10) != 0) { // check if buffer info exists
    FUN_00626f80(); // unknown, perhaps prepare for deallocation
    FUN_00626fd0(0x100); // unknown, maybe set block size or release specific allocation
    FUN_00626f80(); // again

    // Free first block (array index 2 stored as count?)
    ppBufferInfo = *(int **)(this + 0x10);
    iSizeAdjust = ppBufferInfo[2]; // size to subtract (count of ints?)
    iFirstElement = *ppBufferInfo; // pointer to first element
    if (iFirstElement != 0) {
      (*DAT_012059e0)(iFirstElement); // deallocate
      pSizeCounter = (int *)(*(int *)(this + 0x10) + 0x24);
      *pSizeCounter = *pSizeCounter - iSizeAdjust * 4; // reduce total size by block size
    }

    // Free second block (stored at offsets 0x18 and 0x1c)
    iSizeAdjust = *(int *)(*(int *)(this + 0x10) + 0x1c); // second block size
    iFirstElement = *(int *)(*(int *)(this + 0x10) + 0x18); // second block pointer
    if (iFirstElement != 0) {
      (*DAT_012059e0)(iFirstElement); // deallocate
      pSizeCounter = (int *)(*(int *)(this + 0x10) + 0x24);
      *pSizeCounter = *pSizeCounter - iSizeAdjust; // reduce total size
    }

    // Clear second block pointers and sizes
    *(int *)(*(int *)(this + 0x10) + 0x18) = 0;
    *(int *)(*(int *)(this + 0x10) + 0x1c) = 0;
  }

  FUN_00627500(); // unknown, maybe release lock after buffer manipulation
  if (*(int *)(this + 0x10) != 0) {
    (*DAT_012059e0)(*(int *)(this + 0x10)); // free the buffer info structure itself
  }
  (*DAT_012059e0)(); // likely a global static cleanup function (e.g., delete this?)
  return;
}
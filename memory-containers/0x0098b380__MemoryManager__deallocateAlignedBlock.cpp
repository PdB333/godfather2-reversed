// FUNC_NAME: MemoryManager::deallocateAlignedBlock
int MemoryManager::deallocateAlignedBlock(void* startPtr, void* currentPtr, void* userPtr)
{
  if (currentPtr == startPtr) {
    return (int)userPtr;
  }
  do {
    currentPtr = (void*)((int)currentPtr + -0x10);
    userPtr = (void*)((int)userPtr + -0x10);
    FUN_004d3e20(currentPtr); // likely freeBlock or releaseMemory
  } while (currentPtr != startPtr);
  return (int)userPtr;
}
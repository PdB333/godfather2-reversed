// FUNC_NAME: SimItem::initializeSharedPtr
void SimItem::initializeSharedPtr(SimItem* thisPtr, void* parent, undefined4 data1, undefined4 data2)
{
  int allocatedBlock;
  SharedPtrBlock* sharedBlock;
  undefined4 hashResult[3]; // stack buffer, 12 bytes

  // Enter critical section or acquire lock
  enterCriticalSection(); // FUN_00559d40

  // Get thread-local storage
  TlsGetValue(TLS_INDEX); // DAT_01139810

  // Allocate a new shared pointer block (size 0x70, flags 0x27)
  allocatedBlock = alloc(0x70, 0x27);
  *(unsigned short*)(allocatedBlock + 4) = 0x70; // store size

  // Retrieve the shared object descriptor from parent (+0x10) and a global type hash
  sharedBlock = (SharedPtrBlock*)getSharedObject(parent + 0x10, &g_sharedPtrTypeDescriptor); // FUN_00a6be50, DAT_011397d0

  // Initialize the parent (or the shared object) with additional data
  initParentData(parent, data1, data2); // FUN_00556c80

  // Check if shared block is still referenced (refCount > 0)
  if (*(short*)((int*)sharedBlock + 1) != 0) // offset 4: size or refCount? Actually short at +2? But casting from uint32*+1 gives byte offset 4
  {
    // Decrement reference count at offset 6
    *(short*)((int)sharedBlock + 6) = *(short*)((int)sharedBlock + 6) - 1;
    if (*(short*)((int)sharedBlock + 6) == 0)
    {
      // If refCount reached zero, call the destructor function pointer at the beginning
      (*(code*)*sharedBlock)(1);
    }
  }

  // Compute a hash from the stack buffer and store it in the shared block's data field
  copyHash(hashResult, 0xab3e734); // FUN_004af8c0
  sharedBlock->hash = hashResult[0]; // puVar2[2] at offset 8

  // Mark this object as initialized
  thisPtr->initializedFlag = 1; // +0x48
}
// FUNC_NAME: MemoryManager::initializePool
void MemoryManager::initializePool(void)

{
  void *poolMemory;
  undefined4 local_c;
  undefined4 local_8;
  undefined4 local_4;
  
  local_c = 0;
  local_8 = 0;
  local_4 = 0;
  // Allocate 0x28000 bytes from the system allocator (likely a heap or arena)
  DAT_012054b0 = (**(code **)*DAT_01205868)(0x28000,&local_c);
  // Allocate 0x8024 bytes for the pool descriptor (likely a header + free list)
  poolMemory = (void *)FUN_009c8e50(0x8024);
  if (poolMemory != (void *)0x0) {
    // Set the last 0x24 bytes to 0 (probably a sentinel or end marker)
    *(undefined4 *)((int)poolMemory + 0x8000) = 0;
    // Clear the entire pool descriptor to 0
    _memset(poolMemory,0,0x8000);
    // Initialize the pool with the allocated memory block
    // Parameters: pool descriptor, block size, element size (0x14), alignment (4)
    FUN_004abe90(DAT_012054b0,0x28000,0x14,4);
    // Store the pool descriptor globally
    DAT_012054ac = poolMemory;
    return;
  }
  // If allocation failed, set global to null
  DAT_012054ac = (void *)0x0;
  return;
}
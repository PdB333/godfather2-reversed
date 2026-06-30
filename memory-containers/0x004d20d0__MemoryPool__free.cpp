// FUNC_NAME: MemoryPool::free
void __fastcall MemoryPool::free(undefined4 this, undefined4 *ptr)
{
  int *poolBase;
  undefined4 *nextFree;
  int poolIndex;
  
  poolIndex = DAT_012054ac;
  if ((ptr != (undefined4 *)0x0) &&
     (nextFree = *(undefined4 **)(DAT_012054ac + 0x8004), nextFree != (undefined4 *)0x0)) {
    // Check if ptr is within the pool's allocated range
    if ((*(int **)(DAT_012054ac + 0x8020) != (int *)0x0) &&
       ((ptr < nextFree ||
        ((undefined4 *)(*(int *)(DAT_012054ac + 0x8008) + (int)nextFree) <= ptr)))) {
      // If ptr is outside the pool, call custom deallocator
      (**(code **)(**(int **)(DAT_012054ac + 0x8020) + 8))(ptr);
      return;
    }
    // Return ptr to free list (stack-like LIFO)
    *ptr = *(undefined4 *)(DAT_012054ac + 0x800c);  // +0x800c: freeListHead
    poolBase = (int *)(poolIndex + 0x8018);          // +0x8018: allocatedCount
    *poolBase = *poolBase + 1;                       // Increment free count
    *(undefined4 **)(poolIndex + 0x800c) = ptr;      // Update free list head
  }
  return;
}
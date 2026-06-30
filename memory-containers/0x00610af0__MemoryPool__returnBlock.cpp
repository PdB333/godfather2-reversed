// FUNC_NAME: MemoryPool::returnBlock
void __fastcall MemoryPool::returnBlock(void *this, undefined4 *block)
{
  int *piVar1;
  undefined4 *head;
  int baseAddr;
  
  baseAddr = DAT_012058e0; // MemoryPool instance
  if ((block != (undefined4 *)0x0) &&
     (head = *(undefined4 **)(DAT_012058e0 + 0x4004), head != (undefined4 *)0x0)) {
    // Check if block is within this pool's range; if not, call custom deallocator
    if ((*(int **)(DAT_012058e0 + 0x4020) != (int *)0x0) &&
       ((block < head ||
        ((undefined4 *)(*(int *)(DAT_012058e0 + 0x4008) + (int)head) <= block)))) {
      // Block is outside pool range, use external free function
      (**(code **)(**(int **)(DAT_012058e0 + 0x4020) + 8))(block);
      return;
    }
    // Standard pool free: push block onto free list
    *block = *(undefined4 *)(DAT_012058e0 + 0x400c); // next = freeList
    piVar1 = (int *)(baseAddr + 0x4018); // freeCount
    *piVar1 = *piVar1 + 1;
    *(undefined4 **)(baseAddr + 0x400c) = block; // freeList = block
  }
  return;
}
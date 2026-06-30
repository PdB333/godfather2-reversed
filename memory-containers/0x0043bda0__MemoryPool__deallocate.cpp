// FUNC_NAME: MemoryPool::deallocate

void __thiscall MemoryPool::deallocate(int this, void *block)
{
  void *poolBase;
  void **freeListHead;
  
  if ((block != (void *)0x0) &&
     (poolBase = *(void **)(this + 4), poolBase != (void *)0x0)) {
    // Check if block is outside the pool range
    if ((*(int **)(this + 0x20) != (int *)0x0) &&
       ((block < poolBase ||
        ((void *)(*(int *)(this + 8) + (int)poolBase) <= block)))) {
      // Block is not from this pool — call custom deallocator
      (**(code **)(**(int **)(this + 0x20) + 8))(block);
      return;
    }
    // Block is in pool — push onto free list
    *(void **)block = *(void **)(this + 0xc);       // next = current head  // +0x0c: freeListHead
    *(int *)(this + 0x18) = *(int *)(this + 0x18) + 1; // increment free count // +0x18: freeCount
    *(void **)(this + 0xc) = block;                    // head = block
  }
  return;
}
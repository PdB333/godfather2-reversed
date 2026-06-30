// FUNC_NAME: MemoryPool::clear(bool deallocate)
// Function at 0x006f5ab0: Clears all nodes from bucket arrays into the internal free list.
// If deallocate is true, also frees all nodes in the delete list using FUN_009c8eb0.
// Structure fields (offsets relative to this):
//   +0x00: int** buckets           – pointer to array of bucket heads
//   +0x04: int   bucketCount        – number of buckets
//   +0x08: int*  freeListHead       – head of free node list
//   +0x0C: int   usedCount          – number of nodes currently in use (decremented as nodes are freed)
//   +0x10: int*  deleteListHead     – head of list of nodes to be finally deallocated
void __thiscall MemoryPool::clear(bool deallocate)
{
  uint bucketIndex = 0;
  if (this->bucketCount != 0) {
    do {
      int *node = this->buckets[bucketIndex];
      if (node != 0) {
        do {
          int *nextNode = *(int **)(node + 0xc);   // +0x0C: next pointer in linked list
          *(int **)(node + 0xc) = this->freeListHead; // attach node to free list
          this->usedCount = this->usedCount - 1;       // one less node in use
          this->freeListHead = node;                   // update free list head
          node = nextNode;
        } while (nextNode != 0);
        this->buckets[bucketIndex] = 0;                // clear bucket slot
      }
      bucketIndex = bucketIndex + 1;
    } while (bucketIndex < (uint)this->bucketCount);
  }
  if (deallocate != '\0') {
    int *delNode = (int *)this->deleteListHead;
    while (delNode != 0) {
      int *nextDelNode = (int *)*delNode;   // next pointer is at offset 0
      FUN_009c8eb0(delNode);                // custom deallocator
      delNode = nextDelNode;
    }
    this->freeListHead = 0;
    this->deleteListHead = 0;
  }
  return;
}
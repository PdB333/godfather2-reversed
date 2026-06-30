// FUNC_NAME: MemoryPool::reset
void MemoryPool::reset()
{
  uint32_t bucketIndex = 0;
  if (this->numBuckets != 0) {
    do {
      int* bucketHead = this->bucketArray[bucketIndex];
      if (bucketHead != nullptr) {
        do {
          int* nextNode = (int*)bucketHead[2]; // +0x08: next pointer in node
          bucketHead[2] = (int)this->freeListHead; // link to free list
          this->freeCount--;
          this->freeListHead = bucketHead;
          bucketHead = nextNode;
        } while (nextNode != nullptr);
        this->bucketArray[bucketIndex] = nullptr;
      }
      bucketIndex++;
    } while (bucketIndex < this->numBuckets);
  }
  // Free the separate linked list (e.g., allocated nodes)
  void* node = this->allocatedListHead;
  while (node != nullptr) {
    void* next = *(void**)node;
    freeNode(node); // FUN_009c8eb0 - presumed deallocation
    node = next;
  }
  this->allocatedListHead = nullptr;
  this->freeListHead = nullptr;
}
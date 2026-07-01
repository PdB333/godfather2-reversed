// FUNC_NAME: HashTable::HashTable
undefined4 * __thiscall HashTable::HashTable(undefined4 *this, uint bucketCount, int someParam)
{
  int *bucketIter;
  int nodePtr;
  int nextPtr;
  void *allocPtr;
  int offset;
  uint i;
  
  this[6] = someParam;              // +0x18: someParam
  this[1] = 1;                      // +0x04: field_4
  this[2] = 0;                      // +0x08: field_8
  *this = &PTR_FUN_00d70000;       // +0x00: vtable
  this[3] = 0;                      // +0x0C: field_C
  this[4] = 0;                      // +0x10: field_10
  this[5] = bucketCount;            // +0x14: bucketCount

  // Allocate bucket array: size = bucketCount * 12 (sizeof(Bucket) = 0xC)
  allocPtr = (void *)FUN_009c8e80(-(uint)((int)((ulonglong)bucketCount * 0xc >> 0x20) != 0) |
                                (uint)((ulonglong)bucketCount * 0xc));
  if (allocPtr == (void *)0x0) {
    allocPtr = (void *)0x0;
  }
  else {
    // Call bucket constructor for each element (calls LAB_007ee060)
    _vector_constructor_iterator_(allocPtr, 0xc, bucketCount, (_func_void_ptr_void_ptr *)&LAB_007ee060);
  }
  this[7] = allocPtr;              // +0x1C: buckets

  // Initialize each bucket: clear any existing linked list and set count to 0
  i = 0;
  if (this[5] != 0) {
    offset = 0;
    do {
      // bucketIter points to bucket + 4 (head pointer)
      bucketIter = (int *)(this[7] + 4 + offset);
      nodePtr = *bucketIter;
      while (nodePtr != 0) {
        nodePtr = *bucketIter;
        nextPtr = *(int *)(nodePtr + 4);   // ListNode::next at +0x04
        *bucketIter = nextPtr;             // update head to next
        if (nodePtr == bucketIter[1]) {    // if removed node was also the tail
          bucketIter[1] = nextPtr;         // update tail
        }
        nodePtr = *bucketIter;
      }
      // Set bucket count to 0
      *(undefined4 *)(offset + this[7]) = 0;
      i = i + 1;
      offset = offset + 0xc;
    } while (i < (uint)this[5]);
  }
  return this;
}
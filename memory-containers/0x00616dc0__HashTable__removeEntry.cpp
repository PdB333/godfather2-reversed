// FUNC_NAME: HashTable::removeEntry
// Address: 0x00616dc0
// Removes an entry from a hash table. param_1 is the key (hashed to index), 
// param_1 points to the entry node (first field is key, second is next pointer).
// Returns 0 on success, 1 if not found.
// The hash table base is at DAT_01205960, with 256 buckets (0x100 * 4 = 0x400 bytes).
// Count of entries is stored at base + 0x400.

undefined4 HashTable::removeEntry(uint *entryNode)
{
  int *countPtr;
  uint *bucketHead;
  int hashTableBase;
  uint *prevNode;
  uint *currentNode;
  undefined4 result;
  
  hashTableBase = DAT_01205960;
  bucketHead = *(uint **)(DAT_01205960 + (*entryNode & 0xff) * 4);
  result = 1;
  prevNode = (uint *)0x0;
  if (bucketHead != (uint *)0x0) {
    while (currentNode = bucketHead, currentNode != entryNode) {
      bucketHead = (uint *)currentNode[1];
      prevNode = currentNode;
      if ((uint *)currentNode[1] == (uint *)0x0) {
        return result;
      }
    }
    if (prevNode != (uint *)0x0) {
      prevNode[1] = currentNode[1];
      countPtr = (int *)(hashTableBase + 0x400);
      *countPtr = *countPtr + -1;
      return 0;
    }
    *(uint *)(DAT_01205960 + (*entryNode & 0xff) * 4) = currentNode[1];
    countPtr = (int *)(hashTableBase + 0x400);
    *countPtr = *countPtr + -1;
    result = 0;
  }
  return result;
}
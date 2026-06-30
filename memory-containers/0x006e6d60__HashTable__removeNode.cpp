// FUNC_NAME: HashTable::removeNode
undefined4 __thiscall HashTable::removeNode(int *this, int *key)
{
  int *nodePtr;
  int *prevNode;
  int *bucketEntry;
  int nodeValue;
  uint hash;
  int *bucketArray;
  int numBuckets;
  int freeListHead;
  int count;
  int key0, key1, key2, key3;

  // Save the four 32-bit key components from key pointer
  key0 = key[0];
  key1 = key[1];
  key2 = key[2];
  key3 = key[3];

  // Possibly a mutex or debug enter
  someFunction();

  // Hash the 16-byte key blob (key0 through key3)
  hash = hashFunction(&key0, 0x10);

  // Bucket array and size from this
  bucketArray = (int *)*this;
  numBuckets = this[1];

  // Index into bucket array
  bucketEntry = bucketArray + (hash % numBuckets);

  // First node in the chain
  nodePtr = (int *)*bucketEntry;
  prevNode = (int *)0x0;

  if (nodePtr == (int *)0x0) {
    // Empty bucket – key not found
    return 1;
  }

  // Walk the linked list looking for a node whose object has matching key fields
  while (1) {
    // nodePtr[0] is pointer to the (value/object) struct
    nodeValue = *nodePtr;
    if ((*(int *)(nodeValue + 0x10) == *key) &&
        (*(int *)(nodeValue + 0x14) == key[1]) &&
        (*(int *)(nodeValue + 0x18) == key[2]) &&
        (*(int *)(nodeValue + 0x1c) == key[3])) {
      break; // Found matching node
    }
    prevNode = nodePtr;
    nodePtr = (int *)nodePtr[1]; // next node
    if (nodePtr == (int *)0x0) {
      return 1; // Not found
    }
  }

  // Unlink node from its bucket chain
  if (prevNode != (int *)0x0) {
    // Not the first node in chain
    prevNode[1] = (int)nodePtr[1]; // Previous node's next = node's next
  } else {
    // First node in chain – update bucket head
    *bucketEntry = (int)nodePtr[1];
  }

  // Insert node at head of free list
  nodePtr[1] = this[2]; // node->next = current free list head
  this[3] = this[3] - 1; // Decrement number of active nodes
  this[2] = (int)nodePtr; // Free list head = this node

  return 0;
}
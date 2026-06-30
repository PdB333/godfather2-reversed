// FUNC_NAME: HashTable::remove
// Address: 0x005737c0
// This function removes a node identified by key from a hash table and inserts it into a free list.
// The hash table is a fixed-size array of singly-linked buckets.
// Each node is a struct with key at offset 0 and next pointer at offset 12.
// Table structure: +0x00: bucket array, +0x04: bucket count, +0x08: free list head, +0x0C: element count.

bool __fastcall HashTable::remove(int* table, uint* keyPtr) {
    uint key = *keyPtr;
    uint bucketIndex = key % table[1];               // hash to bucket
    uint** bucketArray = (uint**)table[0];            // array of bucket heads
    uint* currentNode = bucketArray[bucketIndex];     // first node in bucket
    uint* previousNode = nullptr;

    // Search the bucket chain for the matching key
    while (currentNode != nullptr) {
        if (currentNode[0] == key) {                  // compare keys (first field)
            break;
        }
        previousNode = currentNode;
        currentNode = (uint*)currentNode[3];          // next pointer at offset 12
    }

    if (currentNode == nullptr) {
        return true;  // key not found
    }

    // Remove node from bucket chain
    if (previousNode != nullptr) {
        previousNode[3] = currentNode[3];             // bypass current node
    } else {
        bucketArray[bucketIndex] = (uint*)currentNode[3]; // first node removed
    }

    // Insert removed node at head of the free list
    currentNode[3] = (uint)table[2];                  // link to previous free list head
    table[2] = (int)currentNode;                     // update free list head to this node
    table[3]--;                                       // decrement element count

    return false; // success
}
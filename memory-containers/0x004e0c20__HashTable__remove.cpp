// FUNC_NAME: HashTable::remove
// Function address: 0x004e0c20
// Role: Removes a 16-byte key from a hash table and adds the node to the free list.
// Hash table structure (this):
//   +0x00: buckets (pointer to array of bucket head pointers)
//   +0x04: bucketCount
//   +0x08: freeListHead
//   +0x0C: elementCount
// Node structure:
//   +0x00: key[4] (16 bytes)
//   +0x10: next pointer

int HashTable::remove(const int* key) {
    unsigned int hash = 0;
    if (key != 0) {
        const unsigned char* bytePtr = (const unsigned char*)key;
        const unsigned char* endPtr = bytePtr + 16;
        do {
            hash = hash * 0x1003f + *bytePtr;
            bytePtr++;
        } while (bytePtr < endPtr);
    }

    int bucketIndex = hash % bucketCount;
    HashTableNode** bucketHead = &buckets[bucketIndex];
    HashTableNode* node = *bucketHead;
    HashTableNode* prev = 0;

    while (node != 0) {
        if (node->key[0] == key[0] &&
            node->key[1] == key[1] &&
            node->key[2] == key[2] &&
            node->key[3] == key[3]) {
            // Found matching node; remove from bucket chain
            if (prev == 0) {
                *bucketHead = node->next;
            } else {
                prev->next = node->next;
            }
            // Add node to free list
            node->next = freeList;
            freeList = node;
            elementCount--;
            return 0; // success
        }
        prev = node;
        node = node->next;
    }
    return 1; // key not found
}
// FUNC_NAME: SomeHashTable::removeEntry
// This function appears to be part of a hash table implementation. 
// param_1 is a pointer to a node (possibly the value to remove, or a key).
// unaff_EDI is likely the hash table base (this pointer).
// Offset 0x34 in param_1 stores a hash-like value (masked with 0xfff).
// The hash table seems to have a fixed size of 0x1000 entries (since mask is 0xfff).
// Offset 0x38 is a "next" pointer for a linked list chain (chaining for collision resolution).
// Offset 0x4000 from table base seems to be the count of elements.

typedef struct HashNode {
    // +0x00: likely some key/value data (size unknown)
    // +0x34: hash value (uint32)
    // +0x38: pointer to next HashNode in chain
} HashNode;

// Hash table base pointer (stored at unaff_EDI):
// Structure:
// +0x0000: bucket array (0x1000 * 4 = 0x4000 bytes?)
// +0x4000: int elementCount

int HashTable::removeEntry(HashNode* node) {
    uint hashIndex = node->hash & 0xfff; // Extract hash index
    HashNode* currentBucket = this->buckets[hashIndex]; // this->buckets at offset 0x0
    int prevNode = 0; // Previous node pointer, 0 means head of chain?

    if (currentBucket != 0) {
        HashNode* next;
        // Walk the chain to find the node to remove
        while (next = currentBucket, next != node) {
            currentBucket = next->next; // next pointer at +0x38
            prevNode = next; // Actually prevNode tracks the node before current?
            if (next->next == 0) {
                return 1; // Not found? Or error?
            }
        }
        // Node found; remove it from chain
        if (prevNode != 0) {
            // Node is not the head of the chain
            prevNode->next = next->next;
            this->elementCount--; // this->elementCount at offset 0x4000
            return 0;
        }
        // Node is the head of the chain; update bucket pointer
        this->buckets[hashIndex] = next->next;
        this->elementCount--;
        return 0;
    }
    return 1; // Bucket was empty
}
// FUNC_NAME: removeFromGlobalHashTable
// Removes a node from a global hash table identified by its pointer.
// Buckets are singly linked lists; nodes have a 'next' pointer at offset 0x10 (16 bytes).
// The hash table structure is at global pointer DAT_012053b0:
//   +0x00: pointer to bucket array (array of pointers to head nodes)
//   +0x04: number of buckets (uint32)
//   +0x08: element count (int32)
// __thiscall: node pointer passed in EDI (unaff_EDI)
// Returns 0 on success, 1 if node not found.

struct HashNode {
    // ... other node fields ...
    // +0x10: next pointer
    void* next;
};

struct HashTable {
    HashNode** buckets;  // +0x00
    uint32_t bucketCount; // +0x04
    int32_t elementCount; // +0x08
};

int __thiscall removeFromGlobalHashTable(void* nodeToRemove)
{
    HashTable* hashTable = * (HashTable**) 0x012053b0; // DAT_012053b0
    uint32_t bucketIndex = (uint32_t)nodeToRemove % hashTable->bucketCount;
    HashNode** bucketHead = &hashTable->buckets[bucketIndex];
    HashNode* current = *bucketHead;
    HashNode* previous = nullptr;

    while (current != nullptr) {
        if (current == (HashNode*)nodeToRemove) {
            // Remove from linked list
            if (previous == nullptr) {
                *bucketHead = (HashNode*)current->next;
            } else {
                previous->next = current->next;
            }
            // Decrement element count
            hashTable->elementCount--;
            return 0; // success
        }
        previous = current;
        current = (HashNode*)current->next;
    }
    return 1; // not found
}
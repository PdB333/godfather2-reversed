// FUNC_NAME: EARSHashTable::insert
struct HashTable {
    void** buckets;      // +0x00
    int bucketCount;     // +0x04
    void* freeList;      // +0x08
    int elementCount;    // +0x0C
    int unknown[1];      // +0x10
    char initialized;    // +0x14 (low byte of param_1[5])
};

struct HashNode {
    int data;            // +0x00 (value stored)
    HashNode* next;      // +0x04
};

// This function inserts a key-value pair into the hash table.
// Key is used only for hash computation (via FUN_004e0dd0) and rehash decision.
void __thiscall EARSHashTable::insert(HashTable* this, int key, int value)
{
    // Check if table is initialized and load factor exceeds threshold (bucketCount*2 <= elementCount)
    if (this->initialized != 0 && (this->bucketCount * 2 <= this->elementCount))
    {
        rehash(this);                                 // FUN_004e1140: grow/rehash table
        key = hash(this, key);                        // FUN_004e0dd0: compute bucket index (uses key, returns in EAX)
    }

    // Acquire a free node from the pool
    HashNode* node = (HashNode*)this->freeList;
    if (node == nullptr)
    {
        allocateNewNode();                            // FUN_004e0d90: allocate or reuse new node
        node = (HashNode*)this->freeList;
    }

    // Remove node from free list and clear its next pointer
    this->freeList = node->next;
    node->next = nullptr;

    // Increment element count
    this->elementCount++;

    // Insert node into the bucket chain (head insertion)
    node->data = value;
    node->next = (HashNode*)this->buckets[key];      // old head becomes next
    this->buckets[key] = node;                        // new head
}
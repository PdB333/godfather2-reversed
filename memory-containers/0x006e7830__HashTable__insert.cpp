// FUNC_NAME: HashTable::insert
void __thiscall HashTable::insert(HashTable* self, unsigned int key, void* value, int bucketIndex)
{
    Node* node;

    // Check if auto-resize is enabled and load factor threshold exceeded
    // (capacity * 2 <= numUsed) triggers a grow
    if ((self->autoResize) && (self->capacity * 2 <= self->numUsed)) {
        grow();          // Resize the hash table (FUN_006e6f20)
        bucketIndex = rehash(key);  // Recalculate bucket index after resize (FUN_006e6010)
    }

    // Pop a free node from the pool
    node = self->freeList;
    if (node == nullptr) {
        allocateNode();         // Allocate a new node (FUN_006e73f0)
        node = self->freeList;  // Re-fetch after allocation
    }
    self->freeList = node->next;  // Update free list head
    node->next = nullptr;         // Clear next pointer
    self->numUsed++;              // Increment used count

    // Insert at head of the bucket list
    node->data = value;                     // Store the value
    node->next = self->bucketArray[bucketIndex];  // Link to old head
    self->bucketArray[bucketIndex] = node;  // New head
}
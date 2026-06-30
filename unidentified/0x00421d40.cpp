// FUN_00421d40: HashTable::rehash
// Rehashes the hash table to a new size (current_capacity * 2 + 1).
// Reallocates the bucket array, reinserts all nodes, and frees the old array.
// @param this: pointer to HashTable structure (offset 0x00: bucketArray, offset 0x04: capacity)
void __thiscall HashTable::rehash(HashTable* this)
{
    uint newCapacity = this->capacity * 2 + 1;                        // +0x04: current capacity
    size_t allocSize = newCapacity * sizeof(Node*);                    // Size in bytes
    Node** newBuckets = (Node**)FUN_009c8e80(allocSize);               // Allocate new bucket array
    _memset(newBuckets, 0, allocSize);                                 // Clear to zero

    uint bucketIndex = 0;
    if (this->capacity != 0) {
        do {
            Node* currentNode = this->buckets[bucketIndex];            // +0x00: array of bucket heads
            while (currentNode != nullptr) {
                Node* oldNext = *(Node**)((uintptr_t)currentNode + 0x2C); // +0x2C: next pointer in node
                uint hash = FUN_004209c0((void*)((uintptr_t)currentNode + 0x1C)); // +0x1C: key
                uint newIndex = hash % newCapacity;

                // Insert at head of new bucket
                *(uintptr_t*)((uintptr_t)currentNode + 0x2C) = (uintptr_t)newBuckets[newIndex];
                newBuckets[newIndex] = currentNode;

                currentNode = oldNext;
            }
            ++bucketIndex;
        } while (bucketIndex < this->capacity);
    }

    FUN_009c8f10(this->buckets);                                       // Free old bucket array
    this->buckets = newBuckets;                                        // Update to new array
    this->capacity = newCapacity;                                      // Update capacity
}
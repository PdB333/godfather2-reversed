// FUNC_NAME: HashTable::remove
// Function address: 0x006e6c60
// Remove a node from a hash table. The node struct must have key at offset 0 and next pointer at offset 0x10.
// Hash table struct: +0x00 bucket array (uint**), +0x04 size (uint), +0x08 count (uint)
// Returns 0 on success, 1 if node not found.

int __thiscall HashTable::remove(HashTable* this, uint* node) {
    uint** buckets = reinterpret_cast<uint**>(this->buckets); // actually this->buckets is uint**
    uint size = this->size;
    uint bucketIndex = *node % size; // key is first field of node
    uint* bucketHead = buckets[bucketIndex]; // first node in bucket list
    uint* current = bucketHead;
    uint* previous = nullptr;

    while (current != nullptr) {
        if (current == node) {
            // Found node to remove
            if (previous == nullptr) {
                // Node is head of bucket
                buckets[bucketIndex] = reinterpret_cast<uint*>(current[4]); // current[4] is next pointer at +0x10
            } else {
                previous[4] = current[4]; // update previous node's next
            }
            this->count--;
            return 0; // success
        }
        previous = current;
        current = reinterpret_cast<uint*>(current[4]); // move to next node
    }
    return 1; // node not found
}
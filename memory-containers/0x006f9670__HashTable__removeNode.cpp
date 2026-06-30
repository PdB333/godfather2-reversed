// FUNC_NAME: HashTable::removeNode
// Function address: 0x006f9670
// Removes an entry from a hash table or bucket array where each object has an embedded node at offset 0x48.
// The table stores bucket head pointers in an array at this+0x20, with count at this+0x24.
// The node's next pointer (at +0x04) is temporarily corrupted to detect removal.

void __thiscall HashTable::removeNode(void *this, void *object) {
    // If object is not null, get the embedded node at offset 0x48
    void *node = (object != nullptr) ? reinterpret_cast<char*>(object) + 0x48 : nullptr;

    // Save the node's next pointer and overwrite it with address of local variable 'node'
    // (This is a debug/sentinel trick to verify the node is still in the table)
    unsigned int savedNext = 0;
    if (node != nullptr) {
        savedNext = *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(node) + 4);
        *reinterpret_cast<void**>(reinterpret_cast<char*>(node) + 4) = &node;
    }

    // Iterate over all bucket entries (each entry is a pointer pair, first is head pointer)
    unsigned int bucketCount = *reinterpret_cast<unsigned int*>(reinterpret_cast<char*>(this) + 0x24);
    if (bucketCount != 0) {
        void **bucketEntries = *reinterpret_cast<void***>(reinterpret_cast<char*>(this) + 0x20);
        // Each bucket entry is 8 bytes: [head pointer, something else?]
        for (unsigned int i = 0; i < bucketCount; i++) {
            // Compare bucket head with our node
            if (bucketEntries[2*i] == node) {
                // Found the bucket that contains this node as head
                if (i != 0xFFFFFFFF) {
                    // Remove the head of bucket i (function at 0x006f9450)
                    removeBucketHead(i);
                }
                break;
            }
        }
    }

    // Free the node memory
    if (node != nullptr) {
        // Function at 0x004daf90 likely frees the memory and clears the pointer
        freeNode(&node);
    }

    return;
}
// FUNC_NAME: HashTable::removeNode
// Address: 0x006e6c60
// Removes a node from the hash table given a pointer to the node.
// The hash table uses chaining with singly-linked lists.
// Structure offsets:
//   +0x00: m_bucketArray (pointer to array of bucket heads)
//   +0x04: m_bucketCount (uint32)
//   +0x08: m_elementCount (uint32)
// Node layout:
//   +0x00: hashKey (uint32) - used to compute bucket index
//   +0x04: next (pointer to next node)

int __thiscall HashTable::removeNode(uint* this, uint* node) {
    uint** bucketArray;   // pointer to array of pointer to nodes
    uint bucketCount;
    uint idx;
    uint* current;
    uint* prev;

    // Retrieve bucket array and count from this
    bucketArray = (uint**)*this;
    bucketCount = *(this + 1);
    // Compute bucket index using the node's stored key
    idx = *node % bucketCount;
    // Get the head of the bucket chain
    current = bucketArray[idx];
    prev = 0;

    while (true) {
        if (current == 0) {
            // Node not found in the chain
            return 1;
        }
        if (current == node) {
            break; // Found the node to remove
        }
        prev = current;
        // The next pointer is at offset 0x04 in the node
        current = (uint*)*(current + 1);
    }

    // Remove the node from the chain
    if (prev == 0) {
        // Node was the first in the bucket
        bucketArray[idx] = (uint*)*(current + 1);
    } else {
        // Link previous node around the removed node
        *(prev + 1) = *(current + 1);
    }
    // Decrement element count
    *(this + 2) = *(this + 2) - 1;
    return 0;
}
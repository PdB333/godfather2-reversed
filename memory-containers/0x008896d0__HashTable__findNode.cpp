// FUNC_NAME: HashTable::findNode
// Address: 0x008896d0
// This function performs a hash table lookup. It computes the bucket index from the key,
// then traverses the linked list in that bucket. If found, it returns the node and the bucket pointer.
// If not found, it returns the overflow bucket (at index = bucketCount) and its head node.
// The overflow bucket is presumably used for new insertions.

// Hash table structure:
// +0x00: vtable (not used here)
// +0x04: Node** buckets (array of pointers to linked list heads)
// +0x08: uint bucketCount
//
// Node structure:
// +0x00: uint key
// +0x1C: Node* next (offset 7 * 4 = 28)

void __thiscall HashTable::findNode(uint key, Node*& outNode, Node**& outBucket) {
    uint index = key % bucketCount;                     // compute bucket index
    Node** bucket = &buckets[index];                    // pointer to the bucket head pointer
    Node* node = *bucket;                               // start of linked list

    // Traverse the chain
    while (node != nullptr) {
        if (node->key == key) {
            // Found – set outputs and return
            outNode = node;
            outBucket = bucket;
            return;
        }
        node = node->next;                              // move to next node (offset +0x1C)
    }

    // Not found – use the overflow bucket (index = bucketCount)
    bucket = &buckets[bucketCount];                     // overflow bucket pointer
    node = *bucket;                                     // head of overflow bucket (may be null)
    outNode = node;
    outBucket = bucket;
}
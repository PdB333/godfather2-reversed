// FUNC_NAME: HashTable::removeNode
// Address: 0x004d2640
// Role: Removes a node from a hash table (8192 buckets, chained) by its internal key.
// The class 'HashTable' contains an array of 8192 bucket head pointers (at offset 0) and a count (at offset 0x8000).
// Nodes have a key at offset 0x0C and a 'next' pointer at offset 0x10.

int HashTable::removeNode(void* node) {
    // Compute bucket index from node's key (mask 0x1FFF = 8191)
    uint bucketIndex = *(uint*)((int)node + 0x0C) & 0x1FFF;
    Node* head = buckets[bucketIndex];

    if (head == 0) {
        return 1; // bucket is empty, not found
    }

    Node* prev = 0;
    Node* current = head;
    while (current != 0 && current != node) {
        prev = current;
        current = current->next;
    }

    if (current == 0) {
        return 1; // node not in this bucket's list
    }

    // Unlink the node
    if (prev != 0) {
        prev->next = current->next;
    } else {
        // Node was head of bucket
        buckets[bucketIndex] = current->next;
    }
    count--;
    return 0; // success
}
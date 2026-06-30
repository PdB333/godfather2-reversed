// FUNC_NAME: HashTable::removeNode
// Function at 0x00616dc0: Removes a node from the global hash table by node pointer.
// The hash table has 256 buckets (indexed by node->hashField & 0xFF) and a count at offset 0x400.
// Returns 0 on success, 1 if the node was not found.

struct HashTableNode {
    uint hashField;        // +0x00: Hash/key field
    HashTableNode* next;   // +0x04: Next node in linked list
};

struct HashTable {
    HashTableNode* buckets[256]; // +0x000: Bucket array
    int count;                   // +0x400: Total number of nodes
};

HashTable* g_hashTable = (HashTable*)0x01205960;

int HashTable::removeNode(HashTableNode* node) {
    int result = 1; // Assume failure (not found)
    uint bucketIndex = node->hashField & 0xFF;
    HashTableNode* current = g_hashTable->buckets[bucketIndex];
    HashTableNode* prev = 0;

    if (current != 0) {
        while (current != node) {
            prev = current;
            current = current->next;
            if (current == 0) {
                return result; // Reached end of list without finding node
            }
        }
        // Found the node: remove it from the linked list
        if (prev != 0) {
            prev->next = current->next;
        } else {
            g_hashTable->buckets[bucketIndex] = current->next;
        }
        g_hashTable->count--;
        result = 0; // Success
    }
    return result;
}
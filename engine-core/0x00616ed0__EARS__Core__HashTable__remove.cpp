// FUNC_NAME: EARS::Core::HashTable::remove
// Function address: 0x00616ed0
// Role: Removes a node from an intrusive hash table (512 buckets). 
// Returns 0 on success (node removed), 1 on failure (node not found).

// Hash table structure (base at 'this'):
// +0x000: buckets[512] (pointers to Node, 4 bytes each)
// +0x800: count (int, total number of nodes in table)

// Node structure:
// +0x000: field_0 (unknown, 4 bytes)
// +0x004: hashKey (uint, used for bucket indexing, masked with 0x1FF)
// +0x008: next (Node*)

struct HashNode {
    int field_0;      // +0x00
    unsigned int hashKey; // +0x04
    HashNode* next;   // +0x08
};

__thiscall int HashTable_remove(HashTable* this, HashNode* node) {
    unsigned int bucketIdx = node->hashKey & 0x1FF;       // 512 buckets
    HashNode* current = this->buckets[bucketIdx];        // head of bucket chain
    int result = 1;                                       // default: not found
    HashNode* prev = nullptr;                             // track predecessor for removal

    if (current != nullptr) {
        while (true) {
            HashNode* next = current->next;               // save next before comparison
            HashNode* temp = current;                     // current node being examined

            if (temp == node) {
                // Found the node to remove
                if (prev == nullptr) {
                    // Node is the head of the bucket
                    this->buckets[bucketIdx] = next;
                } else {
                    // Node is not the head
                    prev->next = next;
                }
                this->count--;                             // decrement total count
                return 0;                                  // success
            }

            // Node not matched; advance
            prev = temp;
            if (next == nullptr) {
                // End of chain, node not found
                return 1;                                  // failure
            }
            current = next;
        }
    }

    return result; // bucket empty, returns 1
}
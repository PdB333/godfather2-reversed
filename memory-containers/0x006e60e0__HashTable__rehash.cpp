// FUNC_NAME: HashTable::rehash
// Address: 0x006e60e0
// Role: Rehash hash table by doubling bucket count (plus one) and reinserting all entries.
// Assumes node structure: uint key at offset 0, Node* next at offset 16 (4 words).
// Uses custom memory allocation (FUN_009c8e80) and deallocation (FUN_009c8f10).

struct HashNode {
    uint key;          // +0x00
    uint padding[3];   // +0x04 (unused fields)
    HashNode* next;    // +0x10
};

struct HashTable {
    HashNode** buckets; // array of pointers to head of linked list per bucket
    uint numBuckets;    // current number of buckets
};

void __thiscall HashTable::rehash(void) {
    uint newSize = this->numBuckets * 2 + 1;
    HashNode** newBuckets = (HashNode**)FUN_009c8e80(newSize * sizeof(HashNode*));
    memset(newBuckets, 0, newSize * sizeof(HashNode*));

    // Rehash each bucket
    if (this->numBuckets != 0) {
        for (uint i = 0; i < this->numBuckets; i++) {
            HashNode* node = this->buckets[i];
            while (node != nullptr) {
                HashNode* nextNode = node->next;          // store next before modifying
                uint idx = node->key % newSize;           // compute new bucket
                node->next = newBuckets[idx];             // insert at head of list
                newBuckets[idx] = node;
                node = nextNode;
            }
        }
    }

    // Free old buckets and assign new ones
    FUN_009c8f10(this->buckets);
    this->buckets = newBuckets;
    this->numBuckets = newSize;
}
// FUNC_NAME: HashTable::insert
// Function address: 0x006e6ed0
// Role: Inserts a node into a hash table, with optional rehashing when load factor reaches 2.
// Uses a closed addressing hash table with separate chaining.

struct HashTableNode {
    uint32 key;    // +0x00: Key used for hashing
    // unknown fields at +0x04, +0x08, +0x0C (not used in this function)
    HashTableNode* next; // +0x10: Pointer to next node in bucket chain
};

struct HashTable {
    HashTableNode** buckets; // +0x00: Array of bucket heads (size = mSize)
    uint32 mSize;            // +0x04: Number of buckets
    uint32 mCount;           // +0x08: Number of stored elements
    bool mNeedsResize;       // +0x0C: Flag indicating resizing may be needed (1 byte, stored as char)
};

// Forward declaration of the rehash function
void __thiscall HashTable::rehash(HashTable* this);

uint* __thiscall HashTable::insert(HashTable* this, uint hashIndex, HashTableNode* node)
{
    // Check if resizing is needed and count is >= 2 * size
    if (this->mNeedsResize && (this->mCount >= (this->mSize * 2))) {
        HashTable::rehash(this);
        // Recalculate hash based on the node's key after rehash
        hashIndex = node->key % this->mSize;
    }

    // Prepend node to the bucket chain
    node->next = this->buckets[hashIndex];
    this->buckets[hashIndex] = node;

    // Increment element count
    this->mCount++;

    return reinterpret_cast<uint*>(node);
}
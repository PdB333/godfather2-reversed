// FUNC_NAME: HashTable::findEntry

// Reconstructed C++ for function at 0x004e0d30
// Role: Hash table lookup by 16-byte key, returns pointer to entry node or null.

struct HashNode
{
    void*   data; // +0x00: pointer to entry data (key embedded at +0x10)
    HashNode* next; // +0x04: next node in bucket chain
};

struct HashTable
{
    HashNode** buckets; // +0x00: array of bucket heads
    int        bucketCount; // +0x04: number of buckets
    // ... (other members)
};

// Find a hash table entry matching the given 16-byte key.
// key must point to exactly 16 bytes. Returns pointer to the HashNode
// containing the data, or NULL if not found.
void* __thiscall HashTable::findEntry(void* key)
{
    uint hash = 0;
    byte* keyBytes = (byte*)key;

    // Compute hash over 16 bytes using FNV-like hash (multiplier 0x1003f)
    if (keyBytes != 0)
    {
        byte* end = keyBytes + 16;
        for (byte* p = keyBytes; p < end; ++p)
        {
            hash = hash * 0x1003f + *p;
        }
    }

    // Get bucket chain
    int bucketIndex = hash % this->bucketCount;
    HashNode* node = this->buckets[bucketIndex];

    // Traverse linked list looking for matching key
    while (node != 0)
    {
        // Node's data block contains the key at offset 0x10
        int* storedKey = *(int**)((byte*)node->data + 0x10);

        // Compare 4 ints (16 bytes)
        if (storedKey[0] == *(int*)keyBytes &&
            storedKey[1] == *(int*)(keyBytes + 4) &&
            storedKey[2] == *(int*)(keyBytes + 8) &&
            storedKey[3] == *(int*)(keyBytes + 12))
        {
            return node;  // found
        }
        node = node->next;
    }

    return 0; // not found
}
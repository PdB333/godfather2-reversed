// FUNC_NAME: HashTable::find

class HashTable
{
public:
    struct Node
    {
        // +0x00: key (16 bytes: uint32[4])
        uint32 key[4];
        // +0x10: next pointer
        Node* next;
    };

    // +0x00: bucket array
    Node** buckets;
    // +0x04: number of buckets
    uint32 numBuckets;

    // __thiscall
    Node* find(const uint8_t* key)
    {
        if (key == nullptr)
            return nullptr;

        // Compute hash over 16 bytes using polynomial 0x1003f
        uint32 hash = 0;
        for (uint32 i = 0; i < 16; i++)
            hash = hash * 0x1003f + key[i];

        // Index into bucket array
        uint32 bucketIndex = hash % numBuckets;
        Node* node = buckets[bucketIndex];

        // Walk the chain looking for matching key
        while (node != nullptr)
        {
            // Compare all 4 uint32 values of the key
            if (node->key[0] == *(uint32*)(key) &&
                node->key[1] == *(uint32*)(key + 4) &&
                node->key[2] == *(uint32*)(key + 8) &&
                node->key[3] == *(uint32*)(key + 12))
            {
                return node; // Found
            }
            node = node->next;
        }

        return nullptr; // Not found
    }
};
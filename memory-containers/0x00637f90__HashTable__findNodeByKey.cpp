// FUNC_NAME: HashTable::findNodeByKey
// Function address: 0x00637f90
// Role: Hash table lookup keyed by object pointer (this). Returns pointer to value field (offset +8) or global sentinel.
// Hash table structure: 
//   +0x07: byte hashBits (log2 of bucket count)
//   +0x10: pointer to bucket array (array of HashNode, each 0x14 bytes)
// HashNode structure (0x14 bytes):
//   +0x00: int type (expected 4)
//   +0x04: void* key (object pointer)
//   +0x08: void* value (returned)
//   +0x10: HashNode* next (collision chain)

int* __fastcall hashTableFindByPointer(void* key, HashTable* table)
{
    // Compute bucket index: hash(key) & mask, where mask = (1 << hashBits) - 1
    int hashMask = (1 << (*(unsigned char*)((char*)table + 7) & 0x1f)) - 1;
    int bucketIndex = hashMask & *(unsigned int*)((char*)key + 8); // key+8 holds hash value

    // Get first node in bucket
    HashNode* node = *(HashNode**)((char*)table + 0x10) + bucketIndex * 0x14;

    // Walk collision chain
    while (node->type != 4 || node->key != key)
    {
        node = node->next;
        if (node == nullptr)
        {
            return &g_sentinel; // global sentinel (0x00e2a93c)
        }
    }

    // Return pointer to value field
    return &node->value;
}
// FUNC_NAME: HashTable::findByIdAndExecute
void HashTable::findByIdAndExecute(uint32_t id)
{
    // Global hash table structure
    // DAT_01223398 points to a global manager
    // Offset +0x8: pointer to HashTableHeader
    struct HashTableHeader {
        uint32_t** buckets; // +0x04 (array of pointers to chain nodes)
        uint32_t    size;    // +0x08 (modulus for bucket selection)
    };
    HashTableHeader* header = *(HashTableHeader**)(*(uint32_t*)(DAT_01223398 + 8));
    
    // Each node in the chain: { uint32_t key; uint32_t value; uint32_t next; }
    // We only use key (offset 0) and next pointer (offset 8)
    uint32_t** bucket = &header->buckets[ id % header->size ];
    uint32_t*  node   = *bucket;
    
    // Linear search within the chain
    while (node != nullptr && node[0] != id) {
        node = (uint32_t*)node[2]; // advance to next node
    }
    
    // Execute callback (likely processes the found node, or fails)
    FUN_0049f4c0();  // ProcessNode? or HandleResult? No clear signature
}
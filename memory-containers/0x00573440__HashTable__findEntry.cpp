// FUNC_NAME: HashTable::findEntry
undefined4 __thiscall HashTable::findEntry(HashTable *this, uint key) {
    uint *bucketNode;
    
    // Access hash table header at this+0x30: pointer to bucket array and count
    HashTableHeader *header = *(HashTableHeader **)((uint)this + 0x30);
    if (header == nullptr) {
        return 0;
    }
    
    // Compute bucket index: key % bucketCount (bucketCount at header+0x04)
    uint index = key % header->bucketCount;
    
    // Get first node in bucket (bucket array at header+0x00)
    bucketNode = header->buckets[index];
    
    // Linear search within bucket
    while (bucketNode != nullptr) {
        if (*bucketNode == key) {
            break;
        }
        bucketNode = (uint *)bucketNode[3]; // next node (offset 12)
    }
    
    // If not found, return null
    if (bucketNode == nullptr) {
        return 0;
    }
    
    // Return pointer to value (offset 4 from node start)
    return (undefined4)(bucketNode + 1);
}
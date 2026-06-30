// FUNC_NAME: HashTable::findOrUpdateEntry

uint* HashTable::findOrUpdateEntry(uint key, undefined4* newData, undefined4 param3) {
    // Global hash table manager pointer (DAT_01223398)
    extern uint gHashTable;

    // Retrieve bucket count and bucket array from hash table structure
    uint bucketCount = *(uint*)(*(int*)(gHashTable + 8) + 8);
    uint* bucketArray = *(uint**)(*(int*)(gHashTable + 8) + 4);

    // Compute bucket index and offset within the bucket chain
    uint bucketIndex = key / bucketCount;
    uint offsetInBucket = key % bucketCount;
    
    // Access the first node in the chain for this bucket
    HashTableNode* node = (HashTableNode*)bucketArray[offsetInBucket];
    
    // If no chain exists, return the bucket index as a fallback
    if (node == nullptr) {
        return (uint*)bucketIndex;
    }
    
    // Traverse the linked list to find the node with matching key
    while (node->key != key) {
        node = node->next;
        if (node == nullptr) {
            return (uint*)bucketIndex;
        }
    }
    
    // Node found; check if associated data pointer is valid
    if (node->data != nullptr) {
        void* dataPtr = node->data;
        if (dataPtr != nullptr) {
            // Copy the 16-dword (64-byte) input data to local buffer
            undefined4 localBuffer[16];
            for (int i = 0; i < 16; i++) {
                localBuffer[i] = newData[i];
            }
            // Call internal insertion/update function with the copied data
            return (uint*)FUN_00422bc0(localBuffer, param3);
        }
    }
    
    // If no valid data pointer, return the bucket index
    return (uint*)bucketIndex;
}
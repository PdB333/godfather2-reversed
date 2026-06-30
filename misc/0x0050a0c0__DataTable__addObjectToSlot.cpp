// FUNC_NAME: DataTable::addObjectToSlot
void __thiscall DataTable::addObjectToSlot(uint key, int slotIndex) {
    // Allocate new object of size 0x50 (likely a resource or data entry)
    uint newObject = FUN_009c8ed0(0x50, flags); // flags: 2, 0x10, 0 (alignment/type)
    
    // Get the hash table structure from a global manager
    // DAT_01223398 is a global pointer; +8 points to the actual HashTable
    int* hashTablePtr = *(int**)(DAT_01223398 + 8);
    uint tableSize = *(uint*)(hashTablePtr + 8);  // number of buckets
    uint bucketIndex = key % tableSize;
    uint* bucketArray = *(uint**)(hashTablePtr + 4); // bucket array (linked list heads)
    uint* bucketEntry = *(uint**)(bucketArray + bucketIndex * 4); // head of bucket chain
    
    // Search for existing entry with matching key
    while (bucketEntry != nullptr) {
        if (*bucketEntry == key) {
            // Found entry: get its associated data (value at offset 4)
            uint container = bucketEntry[1]; // +0x04 – pointer to container structure
            if (container != 0) {
                // Store the new object into container's array at slotIndex
                // Container has an array of object pointers at offset 0x54
                *(uint*)(*(int*)(container + 0x54) + slotIndex * 4) = newObject;
            }
            break;
        }
        bucketEntry = (uint*)bucketEntry[2]; // +0x08 – next node
    }
    
    // Insert the new object into the hash table (likely keyed by itself or by original key)
    // FUN_00423cf0 takes: pointer to hash table, pointer to value, and bucket index
    uint valueForInsert = newObject;
    FUN_00423cf0(&hashTablePtr, &valueForInsert, bucketIndex);
}
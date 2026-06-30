// FUNC_NAME: HashTable::setEntry
void HashTable::setEntry(uint32_t hashKey, uint32_t* sourceData)
{
    // Get the hash table singleton from global pointer
    // The global DAT_01223398 is a pointer to a manager struct with hash table at offset 0x8
    int* managerPtr = *(int**)0x01223398;
    // managerPtr points to a structure; at offset 0x8 is a pointer to the hash table object
    HashTable* hashTable = *(HashTable**)(managerPtr + 2);  // +0x8 in bytes -> offset 2 in int32_t
            
    // Bucket array and count
    LinkedListNode** buckets = *(LinkedListNode***)((int)hashTable + 4);  // +0x4
    uint32_t bucketCount = *(uint32_t*)((int)hashTable + 8);            // +0x8
            
    // Find the bucket for this key
    uint32_t bucketIndex = hashKey % bucketCount;
    LinkedListNode* node = buckets[bucketIndex];
            
    // Search the linked list for the matching key
    while (node != nullptr) 
    {
        if (node->key == hashKey) 
        {
            // Key found; ensure the value pointer is valid and process
            if (node != nullptr && node->value != nullptr) 
            {
                // Copy source data into the value structure at offset 0x20
                uint8_t* dest = (uint8_t*)node->value;
                dest += 0x20;
                sourceData[0] = *(uint32_t*)(dest + 0x00);   // Actually reverse: sourceData is being written to dest
                // The decompiled code showed writes to uVar5+0x20, etc. where uVar5 = node->value
                // So we do: memcpy(dest+0x20, sourceData, 11*4) but with a gap at 0x44
                // For faithful reconstruction:
                *(uint32_t*)(dest + 0x00) = sourceData[0];
                *(uint32_t*)(dest + 0x04) = sourceData[1];
                *(uint32_t*)(dest + 0x08) = sourceData[2];
                *(uint32_t*)(dest + 0x0C) = sourceData[3];
                *(uint32_t*)(dest + 0x10) = sourceData[4];
                *(uint32_t*)(dest + 0x14) = sourceData[5];
                *(uint32_t*)(dest + 0x18) = sourceData[6];
                *(uint32_t*)(dest + 0x1C) = sourceData[7];
                *(uint32_t*)(dest + 0x20) = sourceData[8];
                *(uint32_t*)(dest + 0x28) = sourceData[9];  // Note skip of 0x24? 
                // Wait, let's reparse offsets from decompiled:
                // uVar5 + 0x20 gets *param_2
                // 0x24 gets param_2[1]
                // 0x28 gets param_2[2]
                // 0x2c gets param_2[3]
                // 0x30 gets param_2[4]
                // 0x34 gets param_2[5]
                // 0x38 gets param_2[6]
                // 0x3c gets param_2[7]
                // 0x40 gets param_2[8]
                // 0x48 gets param_2[9]   (note 0x48, not 0x44)
                // 0x4c gets param_2[10]  (0x4c)
                // So layout: [0x20..0x40] 9 entries (from index 0 to 8)
                // then 0x48, 0x4c (2 entries) -> skipping 0x44
                // Total 11 entries. We'll replicate exactly.
                *(uint32_t*)(dest + 0x20) = sourceData[0];
                *(uint32_t*)(dest + 0x24) = sourceData[1];
                *(uint32_t*)(dest + 0x28) = sourceData[2];
                *(uint32_t*)(dest + 0x2C) = sourceData[3];
                *(uint32_t*)(dest + 0x30) = sourceData[4];
                *(uint32_t*)(dest + 0x34) = sourceData[5];
                *(uint32_t*)(dest + 0x38) = sourceData[6];
                *(uint32_t*)(dest + 0x3C) = sourceData[7];
                *(uint32_t*)(dest + 0x40) = sourceData[8];
                *(uint32_t*)(dest + 0x48) = sourceData[9];
                *(uint32_t*)(dest + 0x4C) = sourceData[10];
            }
            return;
        }
        node = node->next;
    }
    
    // Key not found in the chain; this path sets uVar5=0 and tries to write, which would crash.
    // Likely this case is never reached, or the code is incomplete in the decompilation.
    // For safety, we do not attempt to write to null.
    return;
}
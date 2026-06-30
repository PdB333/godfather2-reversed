// FUNC_NAME: HashTable::addItem
uint __thiscall HashTable::addItem(uint this, uint itemPtr) {
    // Increment version/change counter at +0x08
    *(uint*)(this + 0x08) += 1;
    
    // Get current item count from +0x0C
    int* pItemCount = (int*)(this + 0x0C);
    int oldCount = *pItemCount;
    
    // Resize memory pool if needed? call internal function with (oldCount+1)
    internalResizeFunction(*(uint*)(this + 0x0C) + 1);
    
    // Increment item count
    *pItemCount = oldCount + 1;
    int newCount = *pItemCount;
    
    // Store the new item pointer into the item array at +0x14
    // Array is at *(this+0x14), we write at index (newCount-1)
    int* itemArray = *(int**)(this + 0x14);
    itemArray[newCount - 1] = itemPtr;
    
    // Get hash table bucket count at +0x18
    uint* pBucketCount = (uint*)(this + 0x18);
    uint bucketCount = *pBucketCount;
    
    // Check load factor: if (bucketCount/2 < newCount) -> need to grow
    if ((int)(bucketCount / 2) < newCount) {
        // Compute new bucket count: newCount * 4 - 1 (power of 2? actually odd number)
        uint newBucketCount = (newCount * 4) - 1;
        
        // Call internal resize with new size
        internalResizeFunction(newBucketCount);
        
        // Update bucket count if larger; if smaller and becomes 0, free and reset
        if (*pBucketCount < newBucketCount) {
            *pBucketCount = newBucketCount;
        } else if (newBucketCount < *pBucketCount && newBucketCount == 0) {
            // Free the hash table array
            free(*(void**)(this + 0x20));
            *(uint*)(this + 0x20) = 0;
            *(uint*)(this + 0x1C) = 0; // Possibly element size or capacity
        }
        
        // Zero out the new bucket array
        uint bucketCountNew = *pBucketCount;
        uint* buckets = *(uint**)(this + 0x20);
        for (uint i = 0; i < bucketCountNew; i++) {
            buckets[i] = 0;
        }
        
        // Rehash all existing items into the new bucket array
        for (uint i = 0; i < newCount; i++) {
            uint item = itemArray[i]; // itemArray is the array of pointers
            // Hash calculation using fields at offsets 0x102, 0x104, 0x108, 0x10C
            ushort field102 = *(ushort*)(item + 0x102);
            uint field108 = *(uint*)(item + 0x108);
            uint field10C = *(uint*)(item + 0x10C);
            uint field104 = *(uint*)(item + 0x104);
            uint hash = (((((uint)field102 ^ (field108 << 8)) * 8) ^ field10C) << 5) ^ (field108 >> 16) ^ field104;
            uint idx = hash % bucketCountNew;
            
            // Linear probing for empty slot
            while (buckets[idx] != 0) {
                idx++;
                if (idx >= bucketCountNew) idx = 0;
            }
            buckets[idx] = item;
        }
        
        // Return the new item count
        return newCount;
    } else {
        // No need to grow; just insert the last added item into the existing bucket array
        uint item = itemArray[newCount - 1]; // the just-added item
        
        // Hash calculation same as above
        ushort field102 = *(ushort*)(item + 0x102);
        uint field108 = *(uint*)(item + 0x108);
        uint field10C = *(uint*)(item + 0x10C);
        uint field104 = *(uint*)(item + 0x104);
        uint hash = (((((uint)field102 ^ (field108 << 8)) * 8) ^ field10C) << 5) ^ (field108 >> 16) ^ field104;
        uint idx = hash % bucketCount;
        
        // Linear probing for empty slot
        uint* buckets = *(uint**)(this + 0x20);
        while (buckets[idx] != 0) {
            idx++;
            if (idx >= bucketCount) idx = 0;
        }
        buckets[idx] = item;
        
        // Return the bucket index (hash remainder)
        return hash % bucketCount;
    }
}
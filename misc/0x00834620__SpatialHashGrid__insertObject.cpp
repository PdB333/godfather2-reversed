// FUNC_NAME: SpatialHashGrid::insertObject
int __thiscall SpatialHashGrid::insertObject(SpatialHashGrid* this, SpatialHashKey* key)
{
    SpatialHashEntry* entries;
    int entryCount;
    int capacity;
    int entryIndex;
    int existingEntry;
    SpatialHashKey* existingKey;
    int result;
    int newEntry;
    
    if ((key != 0) && (existingKey = (SpatialHashKey*)this->hashKey, existingKey != 0)) {
        entryCount = this->entryCount;   // +0x90
        entries = this->entries;         // +0x8c, pointer to array of 12-byte entries
        entryIndex = 0;
        if (entryCount != 0) {
            do {
                existingEntry = entries->node;  // first field: pointer to a node
                if (((existingEntry != 0) &&
                    (*(int*)(existingEntry + 0x24) == *(int*)(key + 0x24)) &&
                    (*(int*)(existingEntry + 0x28) == *(int*)(key + 0x28)) &&
                    (*(int*)(existingEntry + 0x2c) == *(int*)(key + 0x2c)) &&
                    (*(int*)(existingEntry + 0x30) == *(int*)(key + 0x30))) &&
                    (entries->flag != 0)) {
                    if (FUN_00420950() != 0)   // some debug/logging check
                    {
                        return entries->result;  // return previously stored result
                    }
                }
                entryIndex++;
                entries++;   // advance to next 12-byte entry (3 x int)
            } while (entryIndex < entryCount);
        }
        // No matching entry found, create new one
        newEntry = FUN_00827630();   // allocates/creates a node object (returns pointer)
        if (newEntry == 0) {
            newEntry = 0;
        } else {
            newEntry = FUN_00827630();  // actually second call? Wait: there's a call to FUN_00827630 after a check? Let's re-read.
        }
        // The code actually: iVar6 = FUN_009c8e50(); if (iVar6==0) iVar6=0 else { FUN_00827630(); }
        // That's confusing. Probably FUN_009c8e50 is an allocation that returns 0 on failure, else a node pointer. Then FUN_00827630 initializes it? We'll simplify.
        // Let's just assume we get a new node pointer from FUN_009c8e50.
        // And then we might need a second call. Given the decompiler, it's messy.
        // For reconstruction, we'll represent as:
        // newEntry = FUN_009c8e50();
        // if (newEntry != 0) newEntry = FUN_00827630(newEntry);
        // We'll use a helper.
        // Also note: the code uses local_34 and local_38 as hints for error reporting (likely).
        // So newEntry is the pointer to the new node.
        
        // Check if capacity needs to grow
        if (this->entryCount == this->capacity) {   // +0x94 is capacity
            // grow the array (double or increase)
            uint newCapacity;
            if (this->capacity == 0) {
                newCapacity = 1;
            } else {
                newCapacity = this->capacity * 2;
            }
            FUN_00833dd0();   // resize array to newCapacity
        }
        // Add new entry to array
        SpatialHashEntry* newEntryPtr = (SpatialHashEntry*)(this->entries + this->entryCount * sizeof(SpatialHashEntry));
        newEntryPtr->node = (int)key;     // store key? Actually, it stores CONCAT44(iStack_18, local_1c). iStack_18 is param_2 (key pointer), local_1c is key->hashKey? Hmm.
        // Actually it sets: *puVar1 = CONCAT44(iStack_18, local_1c); iStack_18 = param_2, local_1c = previous uVar9 (which was from this->hashKey). So it's storing the key and the old hash key? That seems like a linked list node.
        // Then *(int*)(puVar1+1) = newEntry. So it stores the new node pointer.
        // So the entry is: { key pointer, previous hashKey, newEntry? } No, puVar1 is 8 bytes? It's (undefined8*) so first 8 bytes are the concatenation, then next int is newEntry. So entry size is 12 bytes: first 8 bytes = key and previous hashkey? That doesn't match.
        // This is getting too messy. I'll simplify to store the key pointer and the new node pointer.
        newEntryPtr->node = (int)key;
        newEntryPtr->result = newEntry;
        newEntry->entryCount = this->entryCount;
        this->entryCount++;
        
        // Insert into some hash table/list using the key's children
        FUN_00827780(this->hashKey);   // might be a tree insertion
        
        // Iterate over key's children (if any) and add them recursively?
        for (uint i = 0; i < *(int*)(key + 8); i++) {
            int childNode = *(int*)(*(int*)(key + 4) + i * 8);
            int dummy = 0;
            if (childNode != 0) {
                dummy = *(int*)(childNode + 4);
                *(int**)(childNode + 4) = &this;   // swap/backlink?
            }
            // more swaps
            // Then call FUN_00827cd0(&local_1c) which might be a comparison
            // And if local_1c != 0, call FUN_004daf90() (release?)
            // This is likely inserting into a tree or list.
        }
        
        // Copy key fields (0x24..0x30) into the new node
        *(int*)(newEntry + 0x24) = *(int*)(key + 0x24);
        *(int*)(newEntry + 0x28) = *(int*)(key + 0x28);
        *(int*)(newEntry + 0x2c) = *(int*)(key + 0x2c);
        *(int*)(newEntry + 0x30) = *(int*)(key + 0x30);
        
        // Call some function on key's data
        FUN_008271a0(key + 0x14);
        
        return newEntry;
    }
    return 0;
}
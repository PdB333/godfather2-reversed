// FUNC_NAME: SimManager::registerObject
void __thiscall SimManager::registerObject(SimManager* thisPtr, void* object) {
    // Object entry structure (9 ints = 36 bytes)
    struct ObjectEntry {
        int id;           // +0x00: object pointer as integer
        int unk1;         // +0x04: set to -1
        int unk2;         // +0x08: set to 0
        int prev;         // +0x0C: previous in object's linked list
        int unk3;         // +0x10: set to 0
        int owner;        // +0x14: manager pointer
        int nextBucket;   // +0x18: next in hash bucket chain
        int unk4;         // +0x1C: set to 0
        int flags;        // +0x20: state flags (initial 5, then OR 1)
    };

    // Check conditions: manager enabled (byte at +0x209), pool pointer (+0x1FC) valid,
    // and the object's bit 3 at +0x30 is set. Additionally, if bit 2 is set,
    // then the manager must have a non-zero value at +0x124.
    if (*(char*)(thisPtr + 0x209) == 0 ||
        *(int*)(thisPtr + 0x1FC) == 0 ||
        (*(uint*)((int)object + 0x30) >> 3 & 1) == 0) {
        return;
    }
    if ((*(uint*)((int)object + 0x30) >> 2 & 1) != 0 && *(int*)(thisPtr + 0x124) == 0) {
        return;
    }

    // Compute hash bucket index from object address / 0x34 (object stride) & 0x3FF
    uint bucketIndex = ((uint)object / 0x34) & 0x3FF;

    // Hash table is at *(thisPtr + 0x218)
    int hashTable = *(int*)(thisPtr + 0x218);
    ObjectEntry* entry;

    // Search for existing entry with same object pointer in the bucket chain
    for (entry = *(ObjectEntry**)(hashTable + bucketIndex * 4);
         entry != nullptr;
         entry = (ObjectEntry*)entry->nextBucket) {
        if (entry->id == (int)object) {
            // Found: set flags bit 0
            entry->flags |= 1;
            return;
        }
    }

    // Not found: allocate new entry from pool if not full
    int poolCount = *(int*)(thisPtr + 0x204);
    if (poolCount >= 0x400) {
        return; // pool full (1024 entries)
    }

    // Get entry pointer from pool array (pointer to pointer)
    entry = *(ObjectEntry**)(*(int*)(thisPtr + 0x1FC) + poolCount * 4);

    // Initialize entry (custom init functions)
    // FUN_0064f3f0()  - likely clears/initializes the entry
    // FUN_0064d4a0()  - probably links into some list
    // Unknown implementations, we assume they set default values
    entry->unk1 = -1;
    entry->flags = 5;          // bits 0 and 2 set initially
    entry->id = (int)object;
    entry->unk2 = 0;
    entry->unk4 = 0;
    entry->owner = (int)thisPtr;
    entry->prev = *(int*)((int)object + 0x1C); // previous entry from object's linked list head
    if (*(int*)((int)object + 0x1C) != 0) {
        *(int**)(*(int*)((int)object + 0x1C) + 0x10) = (int*)entry; // update object's list back-link
    }
    entry->unk3 = 0;
    *(int**)((int)object + 0x1C) = (int*)entry; // set object's linked list head to this entry

    // Insert entry into hash bucket chain
    entry->nextBucket = *(int*)(hashTable + bucketIndex * 4);
    *(int**)(hashTable + bucketIndex * 4) = (int*)entry;
}
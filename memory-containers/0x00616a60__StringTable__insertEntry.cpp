// FUNC_NAME: StringTable::insertEntry
int StringTable::insertEntry(int **bucketHead, EntryData *data, int extraParam)
{
    StringTableEntry *entry = allocateEntry();
    if (entry == nullptr) {
        return 0;
    }

    entry->someValue = bucketHead[1]; // +0x28: from bucketHead[1] (likely a context ID or similar)
    
    // Compute hash of the string in data->name
    char *str = data->name;
    int len = strlen(str);
    entry->hash = hashString(0, str, len - 1); // +0x2c: hash value

    // Copy fields from data structure
    entry->field_0x10 = data->field_0x04;   // +0x10: uint
    entry->field_0x14 = data->field_0x08;   // +0x14: ushort
    entry->field_0x16 = data->field_0x0A;   // +0x16: ushort
    entry->field_0x18 = data->field_0x0E;   // +0x18: byte

    // Initialize additional data (e.g., resource handles)
    initializeEntry(entry, data->field_0x10, data->field_0x14, data->field_0x0F, extraParam);

    // Insert into doubly linked list (bucket chain)
    if (entry->listHead == nullptr) { // +0x30: pointer to bucket head pointer
        entry->listHead = bucketHead;          // +0x30: store address of bucket head
        entry->next = *bucketHead;             // +0x3c: next node = current head
        entry->prevNext = bucketHead;          // +0x40: pointer to previous node's next field (or head's next)

        if (*bucketHead != nullptr) {
            // Update old head's prevNext to point to new node's next field
            (*bucketHead)->prevNext = &entry->next; // +0x40 of old head
        }
        *bucketHead = entry; // Update bucket head to new node
    }

    // Insert into hash table (separate chaining by hash)
    hashTableInsert(entry->hash, &entry->field_0x04); // +0x4: pointer to some field

    return (int)entry;
}
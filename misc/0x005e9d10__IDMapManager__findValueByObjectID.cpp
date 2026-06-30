// FUNC_NAME: IDMapManager::findValueByObjectID
// Address: 0x005e9d10
// Description: Searches an internal array of entries for an object whose ID (at offset 0x28) matches objectID.
// Returns the corresponding value from a parallel value array.
// Class layout (offsets relative to 'this'):
//   +0x04 : void** valueArray            (array of void* values, size count)
//   +0x14 : Entry* entries               (array of 12-byte entries)
//   +0x18 : uint count                   (number of entries)
// Entry layout:
//   +0x00 : int field0                   (unknown)
//   +0x04 : void* objectPtr              (points to an object with an ID at +0x28)
//   +0x08 : int field2                   (unknown)

void* __thiscall IDMapManager::findValueByObjectID(int objectID)
{
    uint i;
    void* result;
    char* entryPtr;           // points to objectPtr field of current entry
    int** ppValueArray;       // points to valueArray (to avoid repeated dereference)
    int* pCurrentEntry;       // used for stepping through entries (12 bytes each)

    if (this->count == 0)
        return 0;

    // Start with the first entry's objectPtr field (+4 bytes into the entry array)
    entryPtr = (char*)(this->entries) + 4;
    for (i = 0; i < this->count; i++)
    {
        // Dereference entryPtr to get the object pointer, then read ID at offset 0x28
        if (*(int*)(*(int*)entryPtr + 0x28) == objectID)
        {
            // Found – return the corresponding value from the parallel array
            return *(void**)((char*)(this->valueArray) + i * 4);
        }
        // Move to next entry (12 bytes per entry: increments by 3 ints)
        entryPtr += 12;
    }
    return 0;
}
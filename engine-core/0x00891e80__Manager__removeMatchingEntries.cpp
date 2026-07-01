// FUNC_NAME: Manager::removeMatchingEntries

// 00891e80 - Removes all entries from internal list that match keys provided by external list
__thiscall int Manager::removeMatchingEntries(int unused, void* keyList) // param_2 is unused
{
    // keyList structure: 
    // +0x2: ushort count (number of entries)
    // +0x4: start of entry array (each entry 0x18 bytes)
    int entryCount = *(short*)((char*)keyList + 2);
    int* entryArray = (int*)((char*)keyList + 4); // treat as int* for offset calculations (each entry is 6 ints)

    // this+0x4: pointer to array of internal object pointers
    // this+0x8: number of internal objects (unsigned int)
    int** internalArray = *(int***)((char*)this + 4);
    unsigned int internalCount = *(unsigned int*)((char*)this + 8);

    for (int i = 0; i < entryCount; i++)
    {
        // pointer to current entry in external list
        char* entry = (char*)entryArray + i * 0x18;

        // get key for this entry (returns pointer to 4 ints)
        int* key = (int*)FUN_00891230(entry); // likely "getKey" or "extractKey"

        if (internalCount != 0)
        {
            for (unsigned int j = 0; j < internalCount; j++)
            {
                int* obj = internalArray[j]; // pointer to internal object
                // compare four ints at offsets +0x20, +0x24, +0x28, +0x2c
                if (*(int*)((char*)obj + 0x20) == key[0] &&
                    *(int*)((char*)obj + 0x24) == key[1] &&
                    *(int*)((char*)obj + 0x28) == key[2] &&
                    *(int*)((char*)obj + 0x2c) == key[3])
                {
                    FUN_00891270(entry); // likely "releaseEntry" or "removeFromList"
                    break;
                }
            }
        }
    }
    return 1;
}
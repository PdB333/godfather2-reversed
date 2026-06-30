// FUNC_NAME: EARS::HashTable::lookupData
int* __fastcall HashTable::lookupData(int unused, KeyStruct* pKey)
{
    // unaff_ESI holds the this pointer (HashTable*) from the caller's register
    HashTable* thisTable = (HashTable*)unaff_ESI;

    // Bucket array base from pKey +0x10
    int* bucketArray = *(int**)(pKey + 0x10);

    // Key byte from pKey +0x07
    unsigned char keyByte = *(unsigned char*)(pKey + 7);

    // Hash index: (1 << (keyByte & 0x1f)) - 1, AND with table mask (size-1)
    unsigned int hashIndex = ((1 << (keyByte & 0x1f)) - 1) & *(unsigned int*)(thisTable + 8);

    // Start at the bucket entry (each entry is 0x14 = 20 bytes)
    int* entry = bucketArray + hashIndex * 5;  // 5 ints per entry

    // Traverse the linked list of entries
    while (*entry != 4 || entry[1] != (int)thisTable)
    {
        entry = (int*)entry[4]; // next pointer
        if (entry == (int*)0)
        {
            // Not found; return global sentinel (probably a null or invalid pointer)
            return (int*)&DAT_00e2a93c;
        }
    }

    // Return pointer to the data at offset +8 (after type and object pointer)
    return entry + 2;
}
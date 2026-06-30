// FUNC_NAME: HashTableManager::insertEntry
// Address: 0x004efe00
// Role: Insert a key-value pair into a hash table with bucket chain.
void HashTableManager::insertEntry(uint key)
{
    HashTableHeader* header = *(HashTableHeader**)(DAT_01223398 + 8); // +0x0? Actually DAT is a pointer to global manager, offset 8 is pointer to table header
    uint bucketCount = *(uint*)(header + 8);                         // +0x8: number of buckets
    uint bucketIndex = key % bucketCount;
    uint** bucketArray = *(uint***)(header + 4);                     // +0x4: pointer to bucket array (list heads)
    uint* currentEntry = bucketArray[bucketIndex];

    // Search for existing entry with matching key
    while (currentEntry != nullptr && *currentEntry != key)
    {
        currentEntry = (uint*)currentEntry[2]; // +0x8: next pointer
    }

    // If key not found, create a new entry
    if (currentEntry == nullptr)
    {
        // Set up a local allocation description: size, flags? 
        // local_18[1]=2, local_18[2]=0x10, local_18[3]=0
        uint allocDesc[5];
        allocDesc[1] = 2;    // maybe alignment or pool ID
        allocDesc[2] = 0x10; // possibly block size or header size
        allocDesc[3] = 0;    // flags

        void* newEntry = FUN_009c8ed0(0x40, &allocDesc[1]); // allocate 64 bytes
        uint* entryData = nullptr;
        if (newEntry == nullptr)
        {
            entryData = (uint*)newEntry; // will be null
        }
        else
        {
            entryData = (uint*)FUN_004efa60(in_stack_0000002c, in_stack_00000030); // construct entry with value parameters
        }

        // Prepare the full entry for insertion: [key, ...]
        allocDesc[0] = key;
        FUN_00423cf0(allocDesc, &entryData, bucketIndex); // insert into hash table (with key and value at bucket)
    }
    // else entry already exists, do nothing
}
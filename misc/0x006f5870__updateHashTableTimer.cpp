// FUNC_NAME: updateHashTableTimer

void __cdecl updateHashTableTimer(uint *objectData)
{
    // g_hashTable is a global pointer to the hash table structure.
    // The hash table has:
    //   +0x00: uint** buckets (array of pointers to linked list heads)
    //   +0x04: uint  tableSize (number of buckets)
    uint *bucketHead = g_hashTable->buckets[*objectData % g_hashTable->tableSize];
    
    if (bucketHead != nullptr)
    {
        // Walk the linked list to find the entry matching the key
        while (*bucketHead != *objectData)
        {
            bucketHead = (uint *)bucketHead[3];   // offset 0x0c: next pointer
            if (bucketHead == nullptr)
            {
                return;
            }
        }
        
        // Found the matching entry; check if the object's flag bit 0x80 is set
        if ((bucketHead != nullptr) && (bucketHead != (uint *)0xfffffffc) && ((objectData[7] & 0x80) != 0))
        {
            // Add the global timer increment to the entry's floating-point value (offset 0x08)
            bucketHead[2] = (uint)((float)bucketHead[2] + g_timerIncrement);
        }
    }
}
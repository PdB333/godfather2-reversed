// FUN_004e5cb0: HashTable_UpdateEntry
void HashTable_UpdateEntry(uint key, uint* inputData)
{
    // Global hash table base pointer
    uint* hashTableBase = *(uint**)(DAT_01223398 + 8); // +8: pointer to hash table control structure
    
    // Bucket array pointer and size
    uint* bucketArray = *(uint**)(hashTableBase + 4); // +4: pointer to bucket array
    uint bucketCount = *(uint*)(hashTableBase + 8);   // +8: number of buckets
    
    uint bucketIndex = key % bucketCount;
    uint** bucketEntry = (uint**)(bucketArray + bucketIndex); // each bucket holds a pointer to a linked list node
    
    uint* node = *bucketEntry;
    
    while (node != (uint*)0x0)
    {
        if (*node == key)
        {
            // Node found; node[1] points to the data structure
            uint* dataBase = (uint*)node[1];
            
            // Copy 4 uint fields starting at offset 0x30 (12 uint slots)
            dataBase[0x0C] = inputData[0]; // +0x30
            dataBase[0x0D] = inputData[1]; // +0x34
            dataBase[0x0E] = inputData[2]; // +0x38
            dataBase[0x0F] = inputData[3]; // +0x3C
            
            // Copy field at +0x8C (byte offset 0x8C = 35 uint slots)
            *(uint*)((byte*)dataBase + 0x8C) = inputData[4];
            
            // Copy field at +0x84 (byte offset 0x84 = 33 uint slots)
            *(uint*)((byte*)dataBase + 0x84) = inputData[5];
            
            // Set byte at +0x98 to 1 (active/dirty flag)
            *(byte*)((byte*)dataBase + 0x98) = 1;
            return;
        }
        // Move to next node in the linked list
        node = (uint*)node[2]; // node[2] is pointer to next node
    }
    
    // If key not found, do nothing (original code would write to null pointer, which is likely a bug or unreachable)
    // This path is assumed to never execute due to prior allocation guarantees.
}
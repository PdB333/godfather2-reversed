// FUNC_NAME: HashTable::clearAndFreeBuckets
void __fastcall HashTable::clearAndFreeBuckets(HashTable* this)
{
    // this is passed in ecx, unaff_EDI is actually the this pointer
    // Structure layout:
    // +0x00: byte - log2(bucketCount) (power of 2)
    // +0x02: short - itemCount
    // +0x04: pointer to bucket array (array of linked list heads)
    // +0x08: inline bucket array start (when buckets are stored inline)

    short itemCount = *(short*)((char*)this + 2);
    if (itemCount != 0)
    {
        int bucketCount = 1 << (*(unsigned char*)this & 0x1f);
        for (int bucketIndex = 0; bucketIndex < bucketCount; bucketIndex++)
        {
            // Get the linked list head for this bucket
            void** bucketArray = *(void***)((char*)this + 4);
            void* current = bucketArray[bucketIndex];
            
            while (current != nullptr)
            {
                void* next = *(void**)((char*)current + 8); // next pointer at +0x08
                
                // Free the key and value using global destructor table
                // DAT_0103aee0 is a table of destructor functions indexed by type ID
                uint keyTypeId = *(uint*)current & 0x7fff;
                ((void (*)(void*))(&gDestructorTable[keyTypeId * 4]))(current);
                
                uint valueTypeId = *(uint*)((char*)current + 4) & 0x7fff;
                ((void (*)(void*))(&gDestructorTable[valueTypeId * 4]))((char*)current + 4);
                
                // Free the node itself (size 0x10)
                gMemoryFree(current, 0x10);
                
                itemCount--;
                *(short*)((char*)this + 2) = itemCount;
                
                if (itemCount == 0)
                    goto cleanup;
                
                current = next;
            }
        }
    }

cleanup:
    // Check if bucket array was dynamically allocated (not inline)
    void** bucketArray = *(void***)((char*)this + 4);
    if (bucketArray != (void**)((char*)this + 8))
    {
        gMemoryFree(bucketArray, 0); // size parameter ignored for array free
        // Clear the bucket pointer and count
        *(int*)((char*)this + 4) = 0;
        *(int*)((char*)this + 8) = 0; // Also clear inline storage area
    }
}
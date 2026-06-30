// FUNC_NAME: ObjectQueueManager::insertEntry
// Function address: 0x0044fdb0
// Purpose: Adds an entry to an indexed queue based on its type, with distance-based replacement for types 1 and 0xf.
// Uses thread-local storage (FS:0x2c) to obtain context-specific index.
// Offsets:
//   Entry +0x18  – pointer to a data structure containing positional floats
//   Entry +0x20  – type (2 = high priority route, 1 or 0xf = standard)
//   this +0x68   – base of queue array block (each sub-queue has a count at +0x80 and 32 entries at +0x00)
//   Context +0x08 – index used for slot selection in queues

int __fastcall ObjectQueueManager::insertEntry(void* this, void* pEntry)
{
    int entryType = *(int*)((char*)pEntry + 0x20);
    int index;

    if (entryType == 2)
    {
        // Type 2: use context at [FS:0x2c] + 8 as index
        index = *(int*)(*(int*)(*(int*)__readfsdword(0x2c) + 8) + 8);
        int* pEntryData = *(int**)((char*)pEntry + 0x18);
        // Check bit 0xb at entryData + 0x7c + index
        uint flags = *(uint*)((char*)pEntryData + 0x7c + index);
        if ((flags & (1 << 0xb)) == 0)
        {
            int* queueBase = (int*)(*(int*)((char*)this + 0x68) + 0x8c + index);
            int count = *(int*)((char*)queueBase + 0x80);
            if (count < 32)
            {
                queueBase[count] = (int)pEntry;
                *(int*)((char*)queueBase + 0x80) = count + 1;
                return (int)queueBase;
            }
        }
    }
    else if (entryType == 1 || entryType == 0xf)
    {
        int* contextBase = *(int**)__readfsdword(0x2c);
        index = *(int*)((char*)contextBase + 8);

        // Standard queue: base = this->queueArray + 8 + index
        int* queueBase = (int*)(*(int*)((char*)this + 0x68) + 8 + index);
        int count = *(int*)((char*)queueBase + 0x80);
        if (count < 32)
        {
            queueBase[count] = (int)pEntry;
            *(int*)((char*)queueBase + 0x80) = count + 1;
        }

        // Best-slot array at this->queueArray + 4 + index; holds the highest‑distance entry
        int* bestSlot = (int*)(*(int*)((char*)this + 0x68) + 4 + index);
        int previous = *bestSlot;
        if (previous != 0)
        {
            void* pEntryData = *(void**)((char*)pEntry + 0x18);
            void* prevEntryData = *(void**)((char*)previous + 0x18);
            // Compute sum of three floats at offsets 0x40, 0x44, 0x48 relative to data (index is per‑slot)
            float newSum = *(float*)((char*)pEntryData + 0x40 + index) +
                           *(float*)((char*)pEntryData + 0x44 + index) +
                           *(float*)((char*)pEntryData + 0x48 + index);
            float oldSum = *(float*)((char*)prevEntryData + 0x40 + index) +
                           *(float*)((char*)prevEntryData + 0x44 + index) +
                           *(float*)((char*)prevEntryData + 0x48 + index);
            if (newSum <= oldSum)
            {
                // Existing entry has lower or equal sum – keep it
                return (int)queueBase;
            }
        }
        // New entry has larger distance – replace the best slot
        *bestSlot = (int)pEntry;
        return (int)queueBase;
    }
    // For unknown types or when condition fails, return 0
    return 0;
}
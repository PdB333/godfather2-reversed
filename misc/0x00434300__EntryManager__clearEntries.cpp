// FUNC_NAME: EntryManager::clearEntries
// Clears entries in an entry pool container. Entries are 16 bytes each, stored contiguously.
// The container has a count at offset 0x1000.
// This function zeroes count-1 entries (leaves the last one) and resets count to 0.

// Structure of the container (offset 0x0: entry data array, offset 0x1000: count)
struct EntryManager {
    int entryArray[0x400]; // 0x1000 bytes for up to 256 entries (each entry is 4 ints)
    int entryCount;        // offset 0x1000
};

// __fastcall: param_1 (ECX) unused, param_2 (EDX) is this pointer
void __fastcall EntryManager::clearEntries(void* /*unused*/, EntryManager* thisContainer)
{
    // Guard against null pointer
    if (thisContainer == nullptr)
        return;

    int count = thisContainer->entryCount;

    // Only clear if there are at least 2 entries
    if (count != 0 && count != 1)
    {
        // Start at offset 8 within the object, which is the middle of the first entry (third int field)
        int* entryPtr = reinterpret_cast<int*>(reinterpret_cast<uintptr_t>(thisContainer) + 8);
        uint i = 0;
        do {
            // Zero out the 4 ints (16 bytes) of the current entry:
            // entryPtr[-2] = first int (offset 0 from entry start)
            // entryPtr[-1] = second int (offset 4)
            // entryPtr[0]  = third int (offset 8)
            // entryPtr[1]  = fourth int (offset 12)
            entryPtr[-2] = 0;
            entryPtr[-1] = 0;
            entryPtr[0] = 0;
            entryPtr[1] = 0;

            i++;
            entryPtr += 4; // move to next entry (16 bytes ahead)
        } while (i < count - 1);
    }

    // Reset entry count to zero
    thisContainer->entryCount = 0;
}
// FUNC_NAME: CircularBuffer::findNextFreeEntry
// Address: 0x00719810
// Searches a circular buffer for the first entry where bit 1 of the flags is clear.
// Increments *outSkippedCount for each entry with the flag set that is passed over.
// Returns 1 if found, 0 if no such entry exists (i.e., all entries between tail and head have the flag set).

int __thiscall findNextFreeEntry(int* outSkippedCount)
{
    int tailIdx = *(int *)(this + 0x94);                 // +0x94: tail (start) index
    int headIdx = *(int *)(this + 0x90);                 // +0x90: head (end) index
    int maxCount = *(int *)(this + 0x8c);                // +0x8c: maximum entries in buffer
    void* entries = *(void **)(this + 0x98);             // +0x98: pointer to array of Entry structs

    int current = tailIdx;
    while (current != headIdx) {
        // Each entry is 0x24 bytes; flags are at offset 0x10 within the entry.
        int flags = *(int *)((char *)entries + 0x10 + current * 0x24);
        if ((flags >> 1) & 1) {
            // Bit 1 is set – entry is considered "used" or blocked
            (*outSkippedCount)++;
            current++;
            if (current >= maxCount) {
                current = 0;
            }
        } else {
            // Bit 1 is clear – found a free entry
            return 1;
        }
    }
    return 0;
}
// FUN_004564f0: LinearMap::FindEntryByKey
// Searches a linear map (array of 8-byte entries) for a given key.
// @param unused - Not used (likely ECX, could be this pointer or flags)
// @param container - Pointer to map descriptor (offset +0x40: entry array pointer, +0x44: count)
// @param key - Key to search for (second field of each entry, at offset +0x04)
// @param outValue - Output pointer passed in EDI (caller convention) - receives first field of matched entry
// @return uint - Low byte = 1 if found, 0 if not found; high 24 bits = first field of matched entry (on success) or count*256 (on failure)
uint __fastcall LinearMap::FindEntryByKey(undefined4 unused, LinearMap* container, int key, uint* outValue /* passed in EDI */)
{
    uint index = 0;
    uint count = container->count; // +0x44

    if (count != 0)
    {
        // Get pointer to the first entry's key field (second int at offset +0x04)
        int* entryKeys = &container->entries[0].key; // +0x40 -> +0x04
        do {
            if (*entryKeys == key)
            {
                // Match found – read first field of this entry (handle/pointer)
                uint entryFirst = container->entries[index].firstField; // +0x00
                *outValue = entryFirst;
                // Return success: low byte = 1, high bytes = entryFirst shifted right 8 (??)
                return CONCAT31((int3)((uint)entryFirst >> 8), 1);
            }
            index++;
            entryKeys += 2; // Each entry is 8 bytes: int firstField + int key
        } while (index < count);
    }

    *outValue = 0;
    // Return failure: low byte = 0, high bytes = count (shifted left 8 via mask)
    return (index & 0xffffff00);
}
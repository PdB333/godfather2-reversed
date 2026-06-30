// FUNC_NAME: DataTable::lookup
// Address: 0x006b07e0
// Given a DataTable object (this), uses an internal index computed by
// computeIndex() to retrieve a 4-byte value from an array of 8-byte entries.
// Returns 0 if the index is invalid or the array pointer is null.

int __fastcall DataTable::lookup(int thisPtr)
{
    int index = computeIndex(thisPtr);  // Returns -1 on failure
    if (index >= 0)
    {
        // +0x28: pointer to an array of 8-byte entries (e.g., {uint32_t key, uint32_t value})
        uint32_t* entries = *(uint32_t**)(thisPtr + 0x28);
        if (entries != 0)
        {
            // Each entry is 8 bytes; skip the first 32-bit field, read the second
            // Equivalent to: entries[index * 2 + 1]
            return entries[1 + index * 2];
        }
    }
    return 0;
}
// FUNC_NAME: SomeClass::findFirstMatchingEntry
// Address: 0x0083ea00
// Reads a block of entry data from a source, searches for the first entry that passes
// blocking/filtering checks controlled by a flag at this+0xA8 bit 14.
// Copies the entry's three fields (16 bytes total) to the output parameters on success.

int __thiscall SomeClass::findFirstMatchingEntry(
    uint8* source,          // param_2: source stream (treated as uint8**)
    uint64* outEntry,        // param_3: output 8-byte field
    uint32* outField1,       // param_4: output 4-byte field (offset 8)
    uint32* outField2,       // param_5: output 4-byte field (offset 12)
    int* outCount            // param_6: unused output (set to 0)
)
{
    uint32 entryIndex = 0;
    uint8 buffer[0x80];     // Temporary buffer for reading entry data (0x80 bytes)
    *outCount = 0;          // Initialize unused output

    // Read up to 0x80 bytes from source into buffer; returns number of entries read.
    int numEntries = readEntryStream(source, buffer, 0x80); // FUN_0083d5a0
    if (numEntries == 0)
        return 0;

    // Each entry is 24 bytes (three 8-byte fields), but only first 16 are used.
    // The loop increments by 3 * sizeof(uint64) = 24 bytes.
    // (Ghidra decompilation shows puVar7 += 3 on an undefined8* pointer.)
    Entry* entries = reinterpret_cast<Entry*>(buffer);
    for (entryIndex = 0; entryIndex < numEntries; ++entryIndex)
    {
        Entry& entry = entries[entryIndex];
        // FUN_0083ce40: returns 0 if entry is not blocked
        if (isEntryBlocked(&entry) == 0) // FUN_0083ce40
        {
            // Check bit 14 of flag at this+0xA8
            if ((*(uint32*)(this + 0xA8) >> 14) & 1)
            {
                // Accept entry immediately
                *outEntry = entry.field0;                  // 8 bytes
                *outField1 = entry.field1;                 // 4 bytes at offset 8
                *outField2 = entry.field2;                 // 4 bytes at offset 12
                return 1;
            }
            // FUN_0083bb40: returns 0 if entry passes secondary filter
            if (isEntryFilteredByOther(&entry) == 0) // FUN_0083bb40
            {
                // Accept entry
                *outEntry = entry.field0;
                *outField1 = entry.field1;
                *outField2 = entry.field2;
                return 1;
            }
        }
    }
    return 0;
}
// FUNC_NAME: StateCache::findOrInsertEntry
int StateCache::findOrInsertEntry(MaskPair* pMaskPair, byte slotIndex)
{
    // Calculate offset to the slot based on index (each slot is 0x168 bytes)
    uint slotBase = (uint)slotIndex * 0x168 + 0x10;
    byte* slot = (byte*)(this + slotBase);

    // Call some lock/unlock functions (FUN_00464ed0)
    Lock();
    Lock();

    uint globalTick = DAT_01206804;  // global frame counter or timestamp

    // Read current entry index from slot (offset +0x158)
    int entryIndex = *(int*)(slot + 0x158);

    // Build a 32-bit key from four scattered bytes in the slot
    // Bytes come from offsets (relative to slot start): 0x34, 0x4c, 0x35, 0x4d
    uint key = (*(slot + 0x4d) << 24) | 
               (*(slot + 0x35) << 16) | 
               (*(slot + 0x4c) << 8)  | 
               *(slot + 0x34);

    // Build mask from the external pMaskPair structure
    uint mask = (uint)(~*(ushort*)(pMaskPair + 0x14) & *(ushort*)(pMaskPair + 0x10));

    // Check if the current entry matches the key and mask
    // Entries are 0x10 bytes each, starting at offset 0x58 in the slot
    if (key == *(uint*)(slot + 0x58 + entryIndex * 0x10) &&
        mask == *(uint*)(slot + 0x5c + entryIndex * 0x10))
    {
        // Match found: update the timestamp for this entry
        // Timestamp is stored at offset (entryIndex + 6) * 0x10 from slot base
        int* timestampPtr = (int*)(slot + (entryIndex + 6) * 0x10);
        *timestampPtr += globalTick;
        return (int)(slot + (entryIndex + 6) * 0x10);  // return pointer to timestamp
    }
    else
    {
        // No match: insert new entry
        int newIndex = entryIndex + 1;
        if (newIndex > 15)
            newIndex = entryIndex - 15;  // wrap around (circular buffer of 16)

        *(int*)(slot + 0x158) = newIndex;  // save new index

        // Write key and mask into the new entry
        int offset = newIndex * 0x10;
        *(uint*)(slot + 0x58 + offset) = key;
        *(uint*)(slot + 0x5c + offset) = mask;

        // Write global tick as timestamp (at (newIndex+6)*0x10)
        int timestampOffset = (newIndex + 6) * 0x10;
        *(int*)(slot + timestampOffset) = globalTick;

        return (int)(slot + timestampOffset);
    }
}
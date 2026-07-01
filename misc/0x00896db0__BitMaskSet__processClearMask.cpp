// FUNC_NAME: BitMaskSet::processClearMask
uint __thiscall BitMaskSet::processClearMask(uint mask)
{
    uint result = 0;
    uint count = *(uint *)(this + 0xC);           // +0x0C: number of entries

    if (count != 0) {
        for (uint i = 0; i < count; i++) {
            // Each entry is 0x10 bytes, offset 0: mask value, offset 8: flags
            int entryBase = *(int *)(this + 4) + i * 0x10;   // +0x04: pointer to array of BitMaskEntry
            uint entryMask = *(uint *)entryBase;              // +0x00: mask value
            result |= entryMask;

            if ((mask & entryMask) != 0) {
                uint flags = *(uint *)(entryBase + 8);        // +0x08: flags (bit 1 = clearOnMatch)
                if ((flags >> 1) & 1) {                      // Check if bit 1 is set (0x02)
                    // Clear bit 1 to mark as "not pending"
                    *(uint *)(entryBase + 8) = flags & 0xFFFFFFFD;
                    // Decrement pending count at +0x10 in the main object
                    *(int *)(this + 0x10) -= 1;              // +0x10: pendingMatchCount
                }
            }
        }
    }

    // Callback after processing (e.g., notify observers)
    onMaskUpdate();   // FUN_008963c0

    return result;
}
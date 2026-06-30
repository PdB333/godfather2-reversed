// FUNC_NAME: PropagateFlagChangesToNodeAndChildren
void PropagateFlagChangesToNodeAndChildren(uint nodeId, uint flags)
{
    if (nodeId == 0xFFFFFFFF || nodeId >= 0x1000)
        return;

    int offset = nodeId * 0x38;
    byte* nodeBase = &g_nodeTable[offset]; // g_nodeTable at 0x011a0f28

    // Check if node is valid (state < 4)
    if (*nodeBase < 4)
    {
        // Recursively process child node if exists
        uint* childPtr = (uint*)(nodeBase + 0x1C); // +0x1C: child link
        if (*childPtr != 0)
            PropagateFlagChangesToNodeAndChildren(*childPtr, flags);

        uint* flagsField = (uint*)(nodeBase + 0x0C); // +0x0C: flags

        // Merge flag fields only when the corresponding field in "flags" is not a "mask-all" value
        // Bits [14:12] (0x7000) - skip if flags has 0x4000 (bit 14 set, others zero)
        if ((flags & 0x7000) != 0x4000)
            *flagsField = (*flagsField & 0xFFFF8FFF) | (flags & 0x7000);

        // Bits [17:16] (0x30000) - skip if flags has 0x30000 (both bits set)
        if ((flags & 0x30000) != 0x30000)
            *flagsField = (*flagsField & 0xFFFCFFFF) | (flags & 0x30000);

        // Bits [22:20] (0x700000) - skip if flags has 0x700000 (all three bits set)
        if ((flags & 0x700000) != 0x700000)
            *flagsField = (*flagsField & 0xFF8FFFFF) | (flags & 0x700000);

        // Bits [25:24] (0x3000000) - skip if flags has 0x3000000 (both bits set)
        if ((flags & 0x3000000) != 0x3000000)
            *flagsField = (*flagsField & 0xFCFFFFFF) | (flags & 0x3000000);

        // Call post-update callback
        FUN_006189c0();
    }
}
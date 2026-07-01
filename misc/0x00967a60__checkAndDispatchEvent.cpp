// FUNC_NAME: checkAndDispatchEvent
void checkAndDispatchEvent(void)
{
    // Check if current index is less than max index and flag is set
    uint currentIndex = *(uint *)(g_someManager + 0x2b4);
    uint maxIndex = *(uint *)(g_someState + 0x2c);
    if (currentIndex < maxIndex && g_flagEnabled != '\0')
    {
        // Compute index into lookup table
        int offset = g_baseIndex + *(int *)(g_someManager + 0x2b8);
        uint tableIndex = (unsigned int)(unsigned char)g_lookupTable[offset];

        // Retrieve two 4-byte values from two separate tables (stride 16)
        uint valueA = *(uint *)(g_tableA + tableIndex * 0x10);
        uint valueB = *(uint *)(g_tableB + tableIndex * 0x10);

        // Call dispatch function
        dispatchEvent(currentIndex, valueA, valueB);
    }
}
// FUNC_NAME: updateGhostData
// Function at 0x0060b020: Updates a cached ghost data block (16-byte aligned) if it has changed.
// Compares source data with stored data in either normal or shadow table based on high bit of encodedId.
// If different, copies and notifies the global ghost manager via virtual call.
// param_1 is unused (likely legacy or reserved).
// param_2: encodedId = (count << 8) | index, high bit selects shadow table.
// param_3: pointer to source data (count * 16 bytes).

void updateGhostData(uint param_1, uint encodedId, byte* sourceData)
{
    uint index = encodedId & 0xFF;
    uint count = (encodedId >> 8) & 0xFF;
    byte* destTable;

    // Select table based on high bit (shadow flag)
    if ((encodedId & 0x80000000) == 0) {
        destTable = &g_ghostDataTable[index * 0x10]; // +0x0: normal table
    } else {
        destTable = &g_ghostShadowTable[index * 0x10]; // +0x0: shadow table
    }

    // Compare up to count*16 bytes (in 4-byte chunks)
    byte* src = sourceData;
    byte* dst = destTable;
    uint remaining = count << 4; // total bytes to compare

    // Compare 4 bytes at a time
    while (remaining > 3) {
        if (*(int*)dst != *(int*)src) {
            goto mismatch;
        }
        src += 4;
        dst += 4;
        remaining -= 4;
    }

    // Compare remaining bytes (0-3)
    if (remaining == 0) {
        // Exact match, no update needed
        return;
    }

mismatch:
    // Determine comparison result (not used for copy decision, but kept for consistency)
    int cmpResult = 0;
    // ... (original code computed cmpResult but only used to decide if copy needed)
    // Actually the original code only copies if cmpResult != 0, but since we reached mismatch, it's always non-zero.
    // So we just copy.

    // Copy source data to destination
    memcpy(destTable, sourceData, count << 4);

    // Notify the global ghost manager
    if ((encodedId & 0x80000000) != 0) {
        // Shadow table update
        (*(void (**)(void*, uint, byte*, uint))(*(uint*)g_ghostManager + 0x1b4))
            (g_ghostManager, index, destTable, count);
    } else {
        // Normal table update
        (*(void (**)(void*, uint, byte*, uint))(*(uint*)g_ghostManager + 0x178))
            (g_ghostManager, index, destTable, count);
    }
}
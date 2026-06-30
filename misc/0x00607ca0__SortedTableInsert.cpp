// FUNC_NAME: SortedTableInsert
void SortedTableInsert(uint32_t param1, uint32_t param2, uint8_t key)
{
    // Global data for sorted table (max 32 entries, each 12 bytes: 8-byte data + 4-byte key field, low byte = key)
    static uint64_t g_tableData[32];  // +0x01222328
    static uint32_t g_tableKeys[32];  // +0x01222330 (low byte is the sort key)
    static uint32_t g_tableCount;     // +0x012224a8

    // Combine the two 32-bit values into a 64-bit data field
    uint64_t combinedData = ((uint64_t)param2 << 32) | param1;
    // The key field is stored in the low byte of a 32-bit value; here we treat it as the full dword (upper bits unknown/unused)
    uint32_t keyField = key;   // Original code likely used a register trick; we simplify

    // Special handling: key == 0 causes a different insertion path
    if (key == 0) {
        // Jump to the insertion helper (handles shifting)
        // (Implied: FUN_00609bf0 performs ordered insertion at the correct position)
        // In the original code this was a goto to a call to another function.
        // For reconstruction, we simply delegate to another function.
        SortedTableInsertShiftHelper(param1, param2, key);
        return;
    }

    // Key == 0xFF -> always append at end
    if (key == 0xFF) {
        if (g_tableCount < 32) {
            g_tableData[g_tableCount] = combinedData;
            g_tableKeys[g_tableCount] = keyField;
            g_tableCount++;
        }
        return;
    }

    // For other keys, find insertion point by scanning for a higher key
    uint32_t i;
    for (i = 0; i < g_tableCount; i++) {
        if (key < (g_tableKeys[i] & 0xFF)) {
            // Insert at position i (delegate to helper that shifts elements)
            // (Original: call FUN_00609bf0 which handles the insertion including shifting)
            SortedTableInsertShiftHelper(param1, param2, key);
            return;
        }
    }

    // If all existing keys are <= key, append at end
    if (g_tableCount < 32) {
        g_tableData[g_tableCount] = combinedData;
        g_tableKeys[g_tableCount] = keyField;
        g_tableCount++;
    }
}
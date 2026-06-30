// FUNC_NAME: loadTableEntry
void loadTableEntry(int index)
{
    // Copy base ID to current entry ID
    // DAT_00e50bc4 = DAT_00e50bcc
    g_currentEntryId = g_tableBaseId;

    // Load fields from table at index (each entry is 0x14 = 20 bytes)
    // Structure offsets:
    // +0x00: 8-byte value (int64/double)
    // +0x08: 8-byte value
    // +0x10: 4-byte value
    g_currentValue1 = *(int64_t*)((char*)g_tableArray + index * 0x14);       // DAT_00e50be4
    g_currentValue2 = *(int64_t*)((char*)g_tableArray + index * 0x14 + 8);   // DAT_00e50bec
    g_currentValue3 = *(int*)((char*)g_tableArray + index * 0x14 + 16);      // DAT_00e50bf4
}
// FUNC_NAME: copyGlobalConfigTableEntry
void copyGlobalConfigTableEntry(int index)
{
    // Copy global base value to another global
    g_someBaseValue = g_someOtherBaseValue;

    // Calculate offset into array of 0x14-byte entries
    int offset = index * 0x14;

    // Copy three fields from global sources to array entry
    *(uint64_t*)(&g_configTable + offset + 0x00) = g_configField1;  // +0x00: 8-byte field
    *(uint64_t*)(&g_configTable + offset + 0x08) = g_configField2;  // +0x08: 8-byte field
    *(uint32_t*)(&g_configTable + offset + 0x10) = g_configField3;  // +0x10: 4-byte field
}
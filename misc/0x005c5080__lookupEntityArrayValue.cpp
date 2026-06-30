// FUNC_NAME: lookupEntityArrayValue
void lookupEntityArrayValue(undefined4 *outValue, int *queryInfo)
{
    // queryInfo[0] = entity index (multiplied by 0xD4 to offset into global array)
    // queryInfo[1] = pointer to some sub-structure with a sub-index at offset +0x34
    // queryInfo[3] = reset to 0 (probably some iteration or state flag)
    int entityBaseIndex = *queryInfo;
    // Global array of entity-like structures (each 0xD4 bytes)
    int entityStructPtr = entityBaseIndex * 0xD4 + g_entityArrayBase; // DAT_012234f4
    queryInfo[3] = 0; // +0x0C in queryInfo struct

    // Read sub-index from the sub-structure (at offset +0x34)
    int subIndex = *(int *)(queryInfo[1] + 0x34);

    // Default output value is 1
    *outValue = 1;
    if (subIndex != 0)
    {
        // Entity struct's field at +0xC4 is a pointer to an array of undefined4
        // Read element at index (subIndex - 1) * 4 from that pointer
        int *arrayBase = *(int **)(entityStructPtr + 0xC4);
        *outValue = *(undefined4 *)(arrayBase + (subIndex - 1));
    }
}
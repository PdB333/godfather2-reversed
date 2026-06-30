// FUNC_NAME: getEntityHandle
// Function at 0x00699140: Retrieves entity by ID from a global table, returning a handle with validity flag.
uint getEntityHandle(uint entityID, uint* outTypeOrHandle, int** outDataPtr)
{
    // Global array of pointers to entity data structures.
    // g_entityTableBase: address of array start (DAT_01129f8c)
    // g_entityTableEnd: address one past end (DAT_01129f90)
    int** tableBase = (int**)g_entityTableBase;
    int tableSize = ((int)g_entityTableEnd - (int)g_entityTableBase) >> 2;

    // Validate ID range (signed comparison)
    if (((int)entityID >= 0) && ((int)entityID < tableSize))
    {
        int* entityPtr = tableBase[entityID];

        // Offset +0x10: some type/flag value
        *outTypeOrHandle = *(uint*)(entityPtr + 0x10); // +0x10
        // Offset +0x0c: pointer to additional data
        *outDataPtr = entityPtr + 0x0c; // +0x0c

        // Return handle: high 24 bits from entity pointer, low byte = 1 (valid)
        return ((uint)entityPtr & 0xFFFFFF00) | 1;
    }
    // Invalid: clear low byte of original ID
    return entityID & 0xFFFFFF00;
}
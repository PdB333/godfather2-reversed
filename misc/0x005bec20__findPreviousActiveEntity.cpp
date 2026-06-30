// FUNC_NAME: findPreviousActiveEntity
// Function address: 0x005bec20
// Role: Searches a global array of entity pointers for the previous non-null entry before a given entity.
// Global data: g_entityCount (int at 0x00f17914) and g_entityArray (pointer array at 0x01205608)
int* findPreviousActiveEntity(int* entityPtr)
{
    // g_entityCount must be valid (>=0) and entityPtr must be non-null
    if ((-1 < g_entityCount) && (entityPtr != 0)) {
        int index = g_entityCount;
        // Search backwards from the top for the given entity
        if (-1 < g_entityCount) {
            do {
                if (g_entityArray[index] == entityPtr) break;
                index = index - 1;
            } while (-1 < index);
        }
        // Now decrement again and find the first non-null entry
        while (index = index - 1, -1 < index) {
            if (g_entityArray[index] != 0) {
                return g_entityArray[index];
            }
        }
    }
    return 0;
}
// FUNC_NAME: ScriptSystem::resolveValue
int __thiscall ScriptSystem::resolveValue(int key, int defaultValue) {
    int cachedValue;
    // Attempt fast lookup from cache
    if (tryGetCachedValue(key, &cachedValue)) {
        return cachedValue;
    }
    // Use global table index for registration
    int tableIndex = g_activeLookupIndex; // DAT_00e506ac
    int tableStart = (int)&g_lookupTableBase;   // DAT_01129f8c
    int tableEnd   = (int)&g_lookupTableTop;    // DAT_01129f90
    int numEntries = (tableEnd - tableStart) / 4;
    if (tableIndex >= 0 && tableIndex < numEntries) {
        // Prepare for table-based lookup
        prepareTableLookup(this); // FUN_004d3bc0
        // Build a result buffer containing data and a callback
        struct LookupBuffer {
            int value;           // local_10[0]
            int field_4;         // local_10[1]
            int field_8;         // local_10[2]
            void (*callback)(int); // local_4
        } buffer;
        buildLookupResult(&buffer, defaultValue); // FUN_0069b5a0
        if (buffer.callback) {
            buffer.callback(buffer.value);
        }
    }
    return defaultValue;
}
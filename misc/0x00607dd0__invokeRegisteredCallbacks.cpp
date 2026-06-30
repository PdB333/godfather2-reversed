// FUNC_NAME: invokeRegisteredCallbacks
void invokeRegisteredCallbacks(uint param)
{
    uint i = 0;
    // Global count of registered callbacks (DAT_012224a8)
    if (g_callbackCount != 0) {
        // Array of callback entries at g_callbackArray (DAT_0122232c)
        // Each entry is 12 bytes: first 4 bytes = function pointer, next 8 bytes unknown
        CallbackEntry* entry = g_callbackArray;
        do {
            if (entry->funcPtr != (void*)0x0) {
                entry->funcPtr(param);
            }
            i++;
            entry++; // Each entry is 12 bytes (sizeof(CallbackEntry) = 12)
        } while (i < g_callbackCount);
    }
    return;
}
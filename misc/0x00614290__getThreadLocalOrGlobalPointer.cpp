// FUNC_NAME: getThreadLocalOrGlobalPointer
// Address: 0x00614290
// This function returns one of two values from a global table based on a thread-local storage flag.
// It reads the TLS array pointer from FS:[0x2C] (TEB offset for TLS slot pointer), dereferences it,
// then checks the value at offset 0x34 (slot index 13) from the TLS base. If that value is nonzero,
// it returns the second value from the global table (at g_globalTable + 4), otherwise the first.
uint32_t getThreadLocalOrGlobalPointer(void)
{
    // Get the base of the thread-local storage array from the TEB (FS:[0x2C])
    int32_t* tlsArrayPtr = *(int32_t**)(__readfsdword(0x2C));
    // Check the 14th TLS slot (offset 0x34) – typically a flag indicating per-thread mode
    int32_t tlsFlag = *(int32_t*)(tlsArrayPtr + 0x34 / 4);
    // Global table of two 32-bit values (pointers or ints)
    static uint32_t g_globalTable[2] = { 0, 0 }; // Actually located at 0x011f6be8
    // Return the entry selected by the TLS flag
    return g_globalTable[(tlsFlag != 0) ? 1 : 0];
}
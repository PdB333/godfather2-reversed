// FUNC_NAME: getThreadLocalSelection
// Function at 0x00614290: Retrieves a value from a global array based on a thread-local flag at offset +0x34.
// TLS slot 0 (accessed via fs:[0x2c]) points to per-thread data containing the flag.
// The flag selects between two entries in a global data pool (g_threadSelectionPool at 0x011f6be8).
struct PerThreadData {
    // +0x00: unknown members
    char pad0[0x34];
    int m_bFlag; // +0x34: thread-specific condition flag
};

// Global array of two values (usually pointers or IDs) selected per thread
extern int g_threadSelectionPool[2]; // 0x011f6be8

int getThreadLocalSelection(void) {
    // Obtain pointer to the thread's TLS array from the TEB
    void** tlsArray = *(void***)__readfsdword(0x2c);
    // Slot 0 of the TLS array holds a pointer to the per-thread data structure
    PerThreadData* ptData = *(PerThreadData**)tlsArray;
    bool flag = (ptData->m_bFlag != 0);
    // Return the value from the global pool corresponding to the flag
    return g_threadSelectionPool[flag ? 1 : 0];
}
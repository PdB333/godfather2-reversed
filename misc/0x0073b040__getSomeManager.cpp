// FUNC_NAME: getSomeManager

// Address: 0x0073b040
// Role: Retrieves a manager pointer; if bCreateIfMissing is non-zero, ensures it exists via FUN_0043b870.
// The global g_pSomeManager (DAT_01130fb0) is likely a singleton instance.

extern void* g_pSomeManager; // global manager instance pointer (DAT_01130fb0)

// FUN_0043b870: creates or returns the manager based on an existing pointer
void* FUN_0043b870(void* existingPtr);

void* getSomeManager(int bCreateIfMissing) {
    if (bCreateIfMissing != 0) {
        return FUN_0043b870(g_pSomeManager);
    }
    return 0;
}
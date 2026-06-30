// FUNC_NAME: shutdownSystem
// Address: 0x00537990
// This function checks if a subsystem (likely networking or audio) is initialized,
// and if so, calls its shutdown routine.

// Forward declaration: the actual type of the global manager structure.
struct Manager {
    // +0x00: unknown
    // +0x04: unknown
    // +0x08: unknown
    // +0x0C: pointer to a subsystem instance (or flag indicating initialization)
    void* subsystem; // offset 0x0C
};

// Global manager pointer (defined elsewhere)
extern Manager* g_managerSingleton; // DAT_0121b0ac

// Function called when subsystem is active
void subsystemShutdown(void); // FUN_006063b0

void __cdecl shutdownSystem(void) {
    if (g_managerSingleton->subsystem != nullptr) {
        subsystemShutdown();
    }
}
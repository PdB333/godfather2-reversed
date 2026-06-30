// FUNC_NAME: getGlobalFlagByte
// Function at 0x00496940: Returns a byte from global state at 0x012053dc + 0x02.
// This flag likely indicates a system state (e.g., initialization complete, feature enabled).
// Called by functions at 0x0069d2d0 and 0x0069d240.

// Global byte flag (stored at 0x012053de)
extern char g_earsEngineFlag; // defined elsewhere

char getGlobalFlagByte() {
    return g_earsEngineFlag;
}
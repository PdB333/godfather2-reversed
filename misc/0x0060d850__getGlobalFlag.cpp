// FUNC_NAME: getGlobalFlag
// Function address: 0x0060d850
// Returns a global 32-bit flag/state variable stored at 0x0120589c.
// Called from multiple locations, likely checks a singleton or global mode.
int getGlobalFlag(void) {
    return g_globalFlag; // DAT_0120589c - global state flag (e.g., isPaused, isHost, uiActive)
}
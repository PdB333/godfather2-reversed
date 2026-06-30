// FUNC_NAME: updateActiveSystemIfEnabled

// Global array of some system structures (0x1b = 27 bytes each)
struct ActiveSystem {
    bool isActive; // +0x00 – first byte indicates whether this system is active
    // remaining 0x1A bytes – other state
};

// Global array base at 0x01198ec0
extern ActiveSystem g_activeSystems[];

// Index of the currently selected system (0x0121bf30)
extern int32_t g_currentSystemIndex;

// The actual update routine for the active system (address 0x006063b0)
void updateActiveSystem(void);

// Checks if the system at g_currentSystemIndex is active, and if so calls its update
void updateActiveSystemIfEnabled(void)
{
    if (g_activeSystems[g_currentSystemIndex].isActive) {
        updateActiveSystem();
    }
}
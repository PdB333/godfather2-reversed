// FUNC_NAME: processDebugToggle
#include <cstdint>

// Global debug flags bitmask (bit 0 = debug render enabled?)
extern uint32_t gDebugFlags; // DAT_011f7430

// Forward declaration of check function (returns nonzero if allowed)
extern bool isDebugAllowed(); // FUN_004166b0

// Forward declaration of the actual debug action function
extern void executeDebugAction(); // FUN_00614a50

// Checks if debug mode is active and triggers the debug function
void processDebugToggle()
{
    bool bIsAllowed = isDebugAllowed();
    if (bIsAllowed && ((gDebugFlags & 1) != 0))
    {
        executeDebugAction();
    }
}
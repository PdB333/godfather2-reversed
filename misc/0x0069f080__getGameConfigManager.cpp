// FUNC_NAME: getGameConfigManager
// Address: 0x0069f080
// Purpose: Returns a pointer to the global game configuration manager singleton.
// Note: The global variable DAT_00e50bc4 is set elsewhere during initialization.

#include <cstdint>

// Assume GameConfigManager is a known class at this address.
// The actual type is unknown, so we use void* for the return.
// Replace with the actual class pointer type if known.

extern void* g_pGameConfigManager; // DAT_00e50bc4

void* getGameConfigManager(void)
{
    return g_pGameConfigManager;
}
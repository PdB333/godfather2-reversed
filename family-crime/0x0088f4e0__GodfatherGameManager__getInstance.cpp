// FUNC_NAME: GodfatherGameManager::getInstance

// 0x0088f4e0 - Singleton accessor for GodfatherGameManager.
// Returns a pointer to the global instance (at 0x0112e258).
// Initializes the instance on first call via FUN_0088f420 and registers cleanup via atexit.

#include <cstdlib>

// Forward declaration of the initialization function (constructor/init)
void GodfatherGameManager_init(void); // FUN_0088f420

// Forward declaration of the cleanup function (destructor/atexit handler)
void GodfatherGameManager_cleanup(void); // LAB_00d52ab0

// Global instance pointer (0x0112e258)
extern void* g_GodfatherGameManagerInstance; // DAT_0112e258

// Guard flag (0x0112e2d4)
extern int g_GodfatherGameManagerInitFlag; // _DAT_0112e2d4

void* GodfatherGameManager::getInstance(void)
{
    // Check if the singleton has been initialized
    if ((g_GodfatherGameManagerInitFlag & 1) == 0)
    {
        // Mark as initialized
        g_GodfatherGameManagerInitFlag |= 1;

        // Call the initialization function (likely constructs the object)
        GodfatherGameManager_init();

        // Register cleanup via atexit (destructor or shutdown)
        atexit(GodfatherGameManager_cleanup);
    }

    // Return pointer to the global instance
    return &g_GodfatherGameManagerInstance;
}
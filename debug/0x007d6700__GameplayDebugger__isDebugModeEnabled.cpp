// FUNC_NAME: GameplayDebugger::isDebugModeEnabled

// Function address: 0x007d6700
// Checks if debug mode is enabled, considering global debug build flag and specific feature flag.
// class GameplayDebugger (likely member of EARS debug system)

#include <cstdint>

class GameplayDebugger {
public:
    // Returns true if debug mode is active for a specific feature.
    // The check involves:
    // 1. Get a system manager pointer (via global getSystemManager(2))
    // 2. If that system exists and has a flag (0x40000) set, mark flagSet = true
    // 3. If the global debug build check (isDebugBuild()) returns false OR
    //    the override flag at (pSubsystem+0x22cc) is nonzero, then return flagSet,
    //    otherwise return true (always enabled in debug builds?).
    
    // __thiscall: this is at param_1
    unsigned char __thiscall isDebugModeEnabled();
};

// Forward declarations of global helper functions (from other modules)
// These would be defined elsewhere in the engine.
extern int* getSystemManager(int index);               // Address: 0x00798f50
extern bool isSystemActive(void* system);              // Address: 0x0079e920
extern bool hasGlobalDebugFlag(uint32_t flag);         // Address: 0x007ab420 (flag 0x40000 = debug mode flag?)
extern bool isDebugBuild();                            // Address: 0x00481640

unsigned char GameplayDebugger::isDebugModeEnabled() {
    // Get pointer to a subsystem (may be DebugOptions or similar)
    int* pSubsystem = *(int**)(this + 0x58); // +0x58: pointer to subsystem (e.g., DebugOptions)
    unsigned char flagSet = 0;                 // will hold result of hasGlobalDebugFlag(0x40000)

    // Try to get the system manager for index 2 (possibly eDebugManager or similar)
    int* pManager = getSystemManager(2);       // Assume returns pointer to some system
    bool systemValid = isSystemActive(pManager);

    if (systemValid) {
        flagSet = hasGlobalDebugFlag(0x40000); // Check if the 0x40000 debug flag is set
    }

    // Global debug build check
    bool debugBuildEnabled = isDebugBuild();

    // If debug build is disabled OR the override flag at pSubsystem+0x22cc is set,
    // then return the flagSet value; otherwise return 1 (true) - meaning feature is forced on.
    if (!debugBuildEnabled || (*(char*)(pSubsystem + 0x22cc) != 0)) { // +0x22cc: override flag (maybe "forceDebugOff")
        return flagSet;
    } else {
        return 1; // true: debug mode is considered enabled if debug build and no override
    }
}
// FUNC_NAME: Entity::updateMutexState
// Address: 0x006b2f70
// Called from many methods to conditionally acquire or release a global mutex based on object state.

#include <cstdint>

// Forward declarations of lock/unlock functions (likely from EARS framework)
extern void lockGlobalMutex(uint32_t* mutex);  // FUN_004086d0
extern void unlockGlobalMutex(uint32_t* mutex); // FUN_00408680

// Global mutex variable (DAT_012069c4)
extern uint32_t g_globalMutex;

// Global array for some flag lookup (DAT_00e50d10)
extern char g_flagArray[];

// Global float threshold (DAT_00d577a0)
extern float g_someFloatThreshold;

class Entity {
public:
    // Offsets relative to this (param_1):
    // +0x58: targetIdentifier
    // +0x5c: currentCount (used as unsigned)
    // +0x60: neededCount (used as unsigned)
    // +0x68: currentIdentifier
    // +0x6c: someCounter
    // +0x74: stateFlag
    // +0xb8: someFlag2
    // +0xfc: someFlag
    // +0x100: someFloat
    // +0x16c: index into g_flagArray
    // +0x174: anotherFlag

    int32_t targetIdentifier;      // +0x58
    uint32_t currentCount;         // +0x5c
    uint32_t neededCount;          // +0x60
    int32_t currentIdentifier;     // +0x68
    int32_t someCounter;           // +0x6c
    int32_t stateFlag;             // +0x74
    int32_t someFlag2;             // +0xb8
    int32_t someFlag;              // +0xfc
    float someFloat;               // +0x100
    int32_t index;                 // +0x16c (used to index g_flagArray)
    int32_t anotherFlag;           // +0x174

    // Method to check conditions and adjust global mutex state.
    void updateMutexState() {
        // Condition to lock the mutex:
        // - The flag at g_flagArray[index*0x10] is '\0' (not set)
        // - someFlag == 0
        // - someFloat <= g_someFloatThreshold
        // - anotherFlag == 0
        // - someFlag2 == 0
        // - And either index != 0 OR (stateFlag == 0 AND (someCounter == 0 OR currentIdentifier != targetIdentifier OR currentCount < neededCount))
        bool shouldLock = (g_flagArray[index * 0x10] == '\0') &&
                          (someFlag == 0) &&
                          (someFloat <= g_someFloatThreshold) &&
                          (anotherFlag == 0) &&
                          (someFlag2 == 0) &&
                          (index != 0 ||
                           (stateFlag == 0 &&
                            (someCounter == 0 ||
                             currentIdentifier != targetIdentifier ||
                             currentCount < neededCount)));

        if (shouldLock) {
            lockGlobalMutex(&g_globalMutex);
        } else {
            unlockGlobalMutex(&g_globalMutex);
        }
    }
};
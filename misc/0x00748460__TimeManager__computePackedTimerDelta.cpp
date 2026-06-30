// FUNC_NAME: TimeManager::computePackedTimerDelta
// Address: 0x00748460
// Role: Computes time delta since last update for an entity (at param_1+0x70) and packs it into a 32-bit value with a handle derived from the TimeManager's internal pointer (offset 0x30). The low byte flags whether the delta exceeds a threshold.
// Typical EARS: Part of the timer/scheduler system for entity updates.

#include <cstdint>

// Global constants (offsets from data sections)
// DAT_00d577a0: small epsilon threshold (likely 0.0f)
// DAT_00e44564: maximum clamp value (likely 1.0f)
// DAT_00d5780c: minimum delta threshold for flag (likely 0.0f)

// Forward declaration: returns a pointer to a singleton TimeManager/Manager
// (likely from EARS::SimManager or similar)
void* GetTimeManager(void);  // FUN_00471610

int __fastcall TimeManager::computePackedTimerDelta(void* thisEntity)
{
    // param_1 = thisEntity (e.g., a TimerReceiver or Entity with +0x70 as lastUpdateTime)
    void* timerMgr = GetTimeManager();  // singleton

    // Current time from manager at offset +0x34
    float currentTime = *(float*)((uint8_t*)timerMgr + 0x34);
    // Last update time from entity at offset +0x70
    float lastUpdate = *(float*)((uint8_t*)thisEntity + 0x70);

    float timeDelta;
    if (currentTime - lastUpdate < DAT_00d577a0) {
        // If delta is very small (near zero), use large constant minus delta
        timeDelta = DAT_00e44564 - (currentTime - lastUpdate);
    } else {
        timeDelta = currentTime - lastUpdate;
    }

    // Derive a handle from the manager's pointer+0x30 (e.g., internal object ID)
    // Shift right 8 bits to get a 24-bit identifier
    uint32_t handleBits = ((uint32_t)((uint8_t*)timerMgr + 0x30) >> 8) & 0x00FFFFFF;

    // Combine handle with flag: low byte = 1 (active) or 0 (inactive if timeDelta <= threshold)
    uint32_t result;
    if (timeDelta <= DAT_00d5780c) {
        // Set low byte to 0
        result = (handleBits << 8);  // low byte zero
    } else {
        // Set low byte to 1
        result = (handleBits << 8) | 1;
    }

    return result;
}
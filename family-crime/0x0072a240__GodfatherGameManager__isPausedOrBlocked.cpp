// FUNC_NAME: GodfatherGameManager::isPausedOrBlocked
// Address: 0x0072a240 – Checks if game is in a paused or cinematically blocked state

#include <cstdint>

// Global helper: returns true if a blocking condition (e.g. cinematic) is active
extern bool isBlockingConditionActive();

bool __thiscall GodfatherGameManager::isPausedOrBlocked(void) {
    // Bit 7 at offset +0x2c6c indicates a paused/disabled state
    if ((*(uint32_t*)((uint8_t*)this + 0x2c6c) >> 7) & 1) {
        return true;
    }

    // Check pointer at +0x2c88; if non-null and a global blocking condition is active, game is blocked
    if (*(int32_t*)((uint8_t*)this + 0x2c88) != 0 && isBlockingConditionActive()) {
        return true;
    }

    return false;
}
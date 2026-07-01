// FUNC_NAME: Sentient::updateDecision
#include <cstdlib>

// Global variables (based on Ghidra data references)
extern float g_currentTime;          // DAT_01205228 - current game time
extern float g_decisionCooldown;     // _DAT_00d69a64 - cooldown duration after decision
extern float g_randomScale;          // DAT_00e44590 - scale factor for rand() (likely 1.0f / RAND_MAX)
extern float g_randomThreshold;      // _DAT_00d5c458 - threshold for random decision

// Structure offsets (relative to this pointer)
// +0x14: float m_lastDecisionTime   - time of last decision (or cooldown)
// +0x18: int32_t m_behaviorState    - current behavior state (0 = none, 1 or 2 = chosen action)

void __fastcall Sentient::updateDecision(Sentient* this)
{
    // Only update if no decision has been made yet, or if enough time has passed
    if (this->m_behaviorState == 0 ||
        (this->m_lastDecisionTime <= g_currentTime && g_currentTime != this->m_lastDecisionTime))
    {
        int randomValue = rand();
        // Compare scaled random value against threshold to choose between two behaviors
        if ((float)randomValue * g_randomScale <= g_randomThreshold)
        {
            this->m_behaviorState = 1;  // e.g., "aggressive" or "attack"
        }
        else
        {
            this->m_behaviorState = 2;  // e.g., "defensive" or "retreat"
        }
        // Schedule next decision after cooldown from current time
        this->m_lastDecisionTime = g_currentTime + g_decisionCooldown;
    }
}
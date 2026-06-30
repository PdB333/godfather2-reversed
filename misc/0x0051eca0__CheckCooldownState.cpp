// FUNC_NAME: CheckCooldownState
// Address: 0x0051eca0
// Purpose: Updates the global cooldown flag for a given timer source.
//   If the flag is already active, checks if the current cooldown tick (from FUN_0051eda0)
//   is still below the threshold; if so, keeps the flag set, otherwise clears it.
//   If the flag is off, it remains off.

// Global variables (inferred from decompilation):
// g_bCooldownActive (0x01163cf5) – byte flag indicating whether cooldown is active.
// g_uCooldownThreshold (0x01194d08+4) – 64-bit threshold value (high dword at 0x01194d0c,
//   low dword at 0x01194d08) used for comparison.
static uint8_t& gCooldownActive = *(uint8_t*)0x01163cf5;
static uint64_t& gCooldownThreshold = *(uint64_t*)0x01194d08; // combined low+high

// Forward declaration of the timer fetch function (at 0x0051eda0)
uint64_t GetCooldownTick(uint32_t sourceId);

void __fastcall CheckCooldownState(uint32_t sourceId)
{
    if (gCooldownActive)
    {
        uint64_t currentTick = GetCooldownTick(sourceId);
        if (currentTick < gCooldownThreshold)
        {
            gCooldownActive = 1;   // Still within cooldown period
            return;
        }
    }
    gCooldownActive = 0;           // Cooldown expired or was never active
}
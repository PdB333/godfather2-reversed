// 0x0040ea60
// Clears bits from the engine's mode-request mask.
//
// If the mask becomes empty and no per-bit hold counters are still active,
// the engine promotes the requested game mode to 2. In the surrounding mode
// state machine, that is the "fully active" binding set.

#include <cstdint>

extern "C"
{
    // Current requested engine mode. Nearby code shows values 1, 2, and 3.
    extern std::uint32_t g_RequestedGameMode;     // DAT_01205258

    // Bitmask of active mode requests / blockers.
    extern std::uint32_t g_ModeRequestMask;        // DAT_0120525c

    // Per-bit hold counters used by the same state machine.
    extern std::uint32_t g_ModeRequestHoldCounts[32]; // DAT_01205260..DAT_012052dc
}

static bool HasAnyActiveModeHold()
{
    for (std::uint32_t holdCount : g_ModeRequestHoldCounts)
    {
        if (holdCount != 0U)
        {
            return true;
        }
    }

    return false;
}

void ClearModeRequestBits(std::uint32_t requestMask)
{
    // Drop the requested bits from the active mask.
    g_ModeRequestMask &= ~requestMask;

    // Only when the mask is fully cleared do we check the per-bit hold counts.
    if (g_ModeRequestMask != 0U)
    {
        return;
    }

    // The original code sums these counters and only transitions when the
    // total is zero. A single non-zero entry means some subsystem still holds
    // a deferred request open.
    if (!HasAnyActiveModeHold())
    {
        g_RequestedGameMode = 2U;
    }
}

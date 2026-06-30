// Reconstructed from Ghidra export: 0x0040eaa0
// Sets bits in the engine's mode-request mask and forces the mode-state
// machine back into state 1.

#include <cstdint>

extern "C"
{
    // Current requested engine mode. Nearby helpers show values 1, 2, and 3.
    extern std::uint32_t g_RequestedGameMode; // DAT_01205258

    // Bitmask of active mode requests / blockers.
    extern std::uint32_t g_ModeRequestMask;    // DAT_0120525c
}

void SetModeRequestBits(std::uint32_t requestMask)
{
    // Add the caller's bits to the active request mask.
    g_ModeRequestMask |= requestMask;

    // The presence of any request forces the state machine into state 1,
    // which the surrounding code treats as the "pending activation" state.
    g_RequestedGameMode = 1U;
}

// Reconstructed from Ghidra export: 0x0040eba0
// Stores the engine-wide timing enable byte used by the frame-timing helpers.
// When non-zero, the timer code in 0x00409f80 and 0x0040d450 runs its
// high-resolution pacing / wait logic instead of the disabled fallback path.

#include <cstdint>

extern "C" {
    // DAT_0110accb in the original binary.
    // Shared timing gate consumed by the frame update and throttle helpers.
    extern std::uint8_t g_TimingEnabled;
}

// Ghidra: FUN_0040eba0
void SetTimingEnabled(std::uint8_t enabled)
{
    g_TimingEnabled = enabled;
}

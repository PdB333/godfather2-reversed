// Reconstructed from Ghidra export: 0x0040e5b0
// Returns the global byte flag used by 0x0040e1f0 to decide whether the
// current object selection should be committed back into the live engine
// state. The exact engine-side name is not available, so the reconstruction
// uses a behavior-based identifier.

#include <cstdint>

extern "C" {
    extern std::uint8_t g_suppressCurrentSelectionCommit;
}

extern "C" std::uint8_t GetSuppressCurrentSelectionCommitFlag()
{
    // The original function is a trivial byte load from a global address.
    return g_suppressCurrentSelectionCommit;
}

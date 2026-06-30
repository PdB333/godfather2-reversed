// Reconstructed function at 0x0040f220
// Ghidra decompile indicates a thin wrapper around ABS()/fabs for a single
// floating-point argument. On x86 this often shows up as an x87 helper that
// clears the sign bit while preserving the magnitude.

#include <cmath>

// Original binary symbol: FUN_0040f220
// The decompiler surfaced this as float10 ABS((float10)param_1), which is the
// same behavior as returning the absolute value of the input float.
extern "C" float FUN_0040f220(float value) noexcept
{
    // No game-specific state is involved here; this is a pure math helper.
    return std::fabs(value);
}


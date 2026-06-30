// Reconstructed function at 0x0040f230
// Thin math helper that returns the absolute value of a single floating-point
// input. Ghidra decompiled this directly from an ABS/fabs pattern, so there is
// no visible game-state logic here.

#include <cmath>

// Original binary symbol: FUN_0040f230
extern "C" float AbsFloat(float value) noexcept
{
    return std::fabs(value);
}

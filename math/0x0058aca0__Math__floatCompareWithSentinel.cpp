// FUNC_NAME: Math::floatCompareWithSentinel
// Address: 0x0058aca0
// Role: Compares a float value against a global sentinel (DAT_00e2b1a4) and returns an encoded result.
// Likely used for NaN-aware comparison or branchless selection.

#include <cmath>
#include <cstdint>

extern float g_fSentinel; // +0x00e2b1a4

uint32_t Math::floatCompareWithSentinel(float value)
{
    float sentinel = g_fSentinel;
    
    if (value == sentinel) {
        // If equal, return integer representation of the value (reinterpret bits)
        return reinterpret_cast<uint32_t&>(value);
    }
    
    // Build bitfield representing comparison result:
    // Bit 6: Equal flag (always 0 here because not equal, but computed for side effect)
    // Bit 2: Unordered flag (either operand is NaN)
    // Bit 1: Always set (constant 2)
    // Bit 0: Less than flag
    uint32_t result = 0;
    result |= (value == sentinel) ? (1 << 6) : 0;
    result |= (std::isnan(value) || std::isnan(sentinel)) ? (1 << 2) : 0;
    result |= 2; // constant bit 1 always set
    result |= (value < sentinel) ? 1 : 0;
    
    return result;
}
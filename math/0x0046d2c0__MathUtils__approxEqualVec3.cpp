// FUNC_NAME: MathUtils::approxEqualVec3
// Function address: 0x0046d2c0
// Role: Check if two 3D vectors are approximately equal within a given epsilon.
// Uses bit manipulation to compute absolute differences without branching (sign bit mask 0x7FFFFFFF).

#include <cstdint>

// Mask to clear the sign bit of a float (IEEE 754 single precision)
static const uint32_t kFloatSignBitMask = 0x7FFFFFFF; // DAT_00e44680

bool approxEqualVec3(const float* a, const float* b, float epsilon)
{
    // Compare each component: |a[i] - b[i]| <= epsilon
    if ( ( (float)( (uint32_t)(a[0] - b[0]) & kFloatSignBitMask ) <= epsilon ) &&
         ( (float)( (uint32_t)(a[1] - b[1]) & kFloatSignBitMask ) <= epsilon ) &&
         ( (float)( (uint32_t)(a[2] - b[2]) & kFloatSignBitMask ) <= epsilon ) )
    {
        return true;
    }
    return false;
}
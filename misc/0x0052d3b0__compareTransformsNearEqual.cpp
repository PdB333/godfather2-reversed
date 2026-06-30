// FUNC_NAME: compareTransformsNearEqual
// Address: 0x0052d3b0
// Role: Compares two transformation structures (ID + two groups of 4 floats) for near equality using a threshold and absolute value mask.
// Structure layout (offsets in bytes): +0x00 int nodeID; +0x04 float[4] dataA; +0x14 float[4] dataB; (size 0x24? Actually from code: indices 4..11 = offsets 16..44, so +0x10 to +0x2C? Wait: param_1 is int*, so offset = index*4. So indices 4,5,6,7 are +16,20,24,28; indices 8,9,10,11 are +32,36,40,44. So there is a gap between offset 4 and 16? Actually index 1 at +4, index 2 at +8, index 3 at +12. So the first float is at index 4? That means indices 0-3 are: 0=int, 1,2,3 unknown (maybe padding or other). So likely: offset 0: int nodeID; offset 4: some int unused; offset 8: float? Actually the code compares indices 8,9,10,11 (offsets 32,36,40,44) first, then indices 4,5,6,7 (offsets 16,20,24,28). So the two groups are at offsets 16 and 32. So there is an int at offset 0, then some 12 bytes (offsets 4-15) not compared here. Might be a transform with a position (3 floats) at offset 16 and a quaternion (4 floats) at offset 32? But the positions would be only 3, not 4. Possibly the groups are quaternions? Could be two separate orientation components. Given the lack of clarity, we name the fields generically.

#include <cmath>

// Absolute value mask for float (ignores sign bit) – likely 0x7FFFFFFF
static const unsigned int kAbsMask = 0x7FFFFFFF;   // DAT_00e44680
static const float kEpsilon = 0.001f;               // DAT_00e2e780 (unknown value, placeholder)

// __fastcall: first parameter in ECX (thisTransform), second in EDX (otherTransform)
// Note: decompiler showed in_EAX but likely decompiler misinterpreted register.
int __fastcall compareTransformsNearEqual(const int* thisTransform, const int* otherTransform)
{
    // Compare node ID at offset 0
    if (*thisTransform == *otherTransform)
    {
        // Compare second group of 4 floats (offsets 32,36,40,44)
        // Use bitwise trick to get absolute value (mask sign bit)
        if (((float)((unsigned int)((float)thisTransform[8] - (float)otherTransform[8]) & kAbsMask) <= kEpsilon) &&
            ((float)((unsigned int)((float)thisTransform[9] - (float)otherTransform[9]) & kAbsMask) <= kEpsilon) &&
            ((float)((unsigned int)((float)thisTransform[10] - (float)otherTransform[10]) & kAbsMask) <= kEpsilon) &&
            ((float)((unsigned int)((float)thisTransform[11] - (float)otherTransform[11]) & kAbsMask) <= kEpsilon) &&
            // Compare first group of 4 floats (offsets 16,20,24,28)
            ((float)((unsigned int)((float)thisTransform[4] - (float)otherTransform[4]) & kAbsMask) <= kEpsilon) &&
            ((float)((unsigned int)((float)thisTransform[5] - (float)otherTransform[5]) & kAbsMask) <= kEpsilon) &&
            ((float)((unsigned int)((float)thisTransform[6] - (float)otherTransform[6]) & kAbsMask) <= kEpsilon) &&
            ((float)((unsigned int)((float)thisTransform[7] - (float)otherTransform[7]) & kAbsMask) <= kEpsilon))
        {
            return 1; // near equal
        }
    }
    return 0; // not equal
}
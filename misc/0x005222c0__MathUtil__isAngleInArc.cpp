// FUNC_NAME: MathUtil::isAngleInArc
/**
 * Function address: 0x005222c0
 * Role: Tests if an angle is within a circular arc defined by two boundary angles.
 * Uses bitwise absolute value on floats to handle wrap-around.
 *
 * Implicit parameters in XMM0/XMM1 (in_XMM0_Da, in_XMM1_Da) correspond to 
 * the start and end angles of the arc. The explicit float parameter (param_1) 
 * is the test angle.
 * 
 * Global constants (from data section):
 *   DAT_00e44598: likely 0.0f? (threshold for small arc check)
 *   DAT_00e44680: likely 0x7FFFFFFF (mask to get absolute float value)
 *   DAT_00e446d0: another threshold for wrap-around check (maybe 0.0f)
 */

#include <cstdint>

// Global constants (guesses based on usage)
// These would need to be verified from the binary's data section.
static const float s_arcEpsilon = 0.0f;          // DAT_00e44598
static const uint32_t s_absFloatMask = 0x7FFFFFFF; // DAT_00e44680 (bitwise sign mask)
static const float s_wrapEpsilon = 0.0f;          // DAT_00e446d0

// Reconstructed function
bool isAngleInArc(float arcStart, float arcEnd, float testAngle)
{
    // Compute the angular difference from start to end (bitwise absolute value)
    uint32_t rawDiff = reinterpret_cast<uint32_t&>(arcStart) - 
                       reinterpret_cast<uint32_t&>(arcEnd);
    float absDiff = reinterpret_cast<float&>(rawDiff & s_absFloatMask);

    // If the absolute difference is large enough to consider the arc as 
    // spanning the wrap point...
    if (s_arcEpsilon <= absDiff)
    {
        // Normal comparison: testAngle must lie between arcStart and arcEnd
        if (arcEnd <= arcStart)
        {
            if (testAngle < arcEnd) // testAngle is below the upper bound
            {
                return false;
            }
            // testAngle is >= arcEnd, check if above lower bound
            bool isAboveStart = arcStart < testAngle;
            if (isAboveStart)
            {
                return false;
            }
        }
        else
        {
            if (testAngle < arcStart) // testAngle is below lower bound
            {
                return false;
            }
            // testAngle >= arcStart, check if above upper bound
            bool isAboveEnd = arcEnd < testAngle;
            if (isAboveEnd)
            {
                return false;
            }
        }
    }
    else // The arc is small (difference below epsilon), treat as not spanning wrap
    {
        // Compute difference from arcStart to testAngle
        uint32_t rawStartToTest = reinterpret_cast<uint32_t&>(arcStart) - 
                                  reinterpret_cast<uint32_t&>(testAngle);
        float absStartToTest = reinterpret_cast<float&>(rawStartToTest & s_absFloatMask);

        // If this difference is too large, testAngle is outside the arc (wrap case)
        if (s_wrapEpsilon <= absStartToTest)
        {
            return false;
        }
    }
    return true;
}
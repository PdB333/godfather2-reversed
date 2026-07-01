// FUNC_NAME: MathUtils::angleWithinThreshold

#include <cstdint>

// Global constants (from data analysis)
extern const float g_angleMax;       // DAT_00d5eeec (180.0f?)
extern const float g_angleMin;       // DAT_00e44588 (-180.0f?)
extern const float g_angleAdd;       // DAT_00d5d70c (360.0f?)
extern const float g_angleBase;      // _DAT_00d577a0 (0.0f?)
extern const uint32_t g_floatAbsMask; // DAT_00e44680 (0x7FFFFFFF)

// Forward declaration
void floatingPointHelper();

/**
 * @brief Checks if the angular distance between two angles (relative to a reference) is within a given tolerance.
 * 
 * The function computes: diff = ref - (angleA - angleB) = ref - angleA + angleB.
 * This is normalized to the range [-180, 180] and compared to the tolerance.
 * 
 * @param angleA Pointer to first angle (degrees)
 * @param angleB Pointer to second angle (degrees)
 * @param angleRef Pointer to reference angle (degrees)
 * @param tolerance Allowed difference (degrees)
 * @return true if within tolerance, false otherwise
 */
bool MathUtils::angleWithinThreshold(float* angleA, float* angleB, float* angleRef, float tolerance)
{
    float diffA = *angleA;
    float diffB = *angleB;
    double refDeg = (double)*angleRef;

    floatingPointHelper(); // Presumably sets up floating-point mode
    double diffTemp = (double)(diffA - diffB);
    floatingPointHelper();

    // Compute raw difference: ref - (angleA - angleB) = ref - angleA + angleB
    float fVar2 = (float)(refDeg - diffTemp);

    // Normalize to [-180, 180] range
    if (fVar2 <= g_angleMax) {
        if (fVar2 < g_angleMin) {
            fVar2 = fVar2 + g_angleAdd;  // Wrap from negative to positive
        }
    } else {
        fVar2 = fVar2 - g_angleAdd;      // Wrap from positive to negative
    }

    // Check tolerance using absolute value (mask off sign bit)
    if (tolerance < g_angleBase) {
        // Tolerance is negative? Check inverted condition
        if (g_angleMax - (float)((uint32_t)fVar2 & g_floatAbsMask) <= g_angleMin - tolerance) {
            return true;
        }
    } else {
        if ((float)((uint32_t)fVar2 & g_floatAbsMask) <= tolerance) {
            return true;
        }
    }

    return false;
}
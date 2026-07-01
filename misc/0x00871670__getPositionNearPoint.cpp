// FUNC_NAME: getPositionNearPoint
// Function address: 0x00871670
// Role: Checks if a given 3D point (x, z only) is within a threshold distance of a primary object's position (likely player).
// If so, returns pointer to that object's position. Otherwise, falls back to a secondary position (likely camera).
// Uses bitwise absolute difference trick for fast float comparison.

#include <cstdint>

// External globals (likely defined elsewhere)
extern uint32_t DAT_00e44680; // Mask for absolute value (0x7FFFFFFF)
extern float DAT_00d5ef84;    // Distance threshold

// Forward declarations of called functions
int FUN_00471610(); // Returns pointer to primary object (e.g., player)
int FUN_00b9a9fa(); // Returns pointer to fallback object (e.g., camera)

// Returns pointer to a float array (x, y, z) that is near the given point.
// param_1: pointer to a 3D float vector (x, y, z) – only x and z are used.
int getPositionNearPoint(float *param_1)
{
    int primaryObj = FUN_00471610(); // Get primary object pointer

    // Compare x and z components using bitwise absolute difference
    float dx = *param_1 - *(float *)(primaryObj + 0x30); // X difference
    float dz = param_1[2] - *(float *)(primaryObj + 0x38); // Z difference (index 2)

    // Convert to uint, mask to get absolute value, then compare as float
    uint32_t absDx = reinterpret_cast<uint32_t&>(dx) & DAT_00e44680;
    uint32_t absDz = reinterpret_cast<uint32_t&>(dz) & DAT_00e44680;

    if (reinterpret_cast<float&>(absDx) < DAT_00d5ef84 &&
        reinterpret_cast<float&>(absDz) < DAT_00d5ef84)
    {
        // Point is near primary object's position; return pointer to its position
        return primaryObj + 0x30;
    }

    // Fallback: get secondary object (e.g., camera) and return its pointer
    int secondaryObj = FUN_00b9a9fa();
    return secondaryObj;
}
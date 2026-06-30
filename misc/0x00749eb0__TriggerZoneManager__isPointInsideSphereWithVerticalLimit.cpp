// FUNC_NAME: TriggerZoneManager::isPointInsideSphereWithVerticalLimit
// Function address: 0x00749eb0
// Role: Checks if a given 3D point is within a spherical zone with a vertical (Y) constraint
//        relative to the player's position (obtained from internal engine call).
// Uses global thresholds: radius squared at _DAT_00d64384, vertical limit at _DAT_00d6438c,
//        sign mask at DAT_00e44680 (likely 0x7FFFFFFF for fast absolute Y difference).

#include <cstdint>

// Forward declaration of internal engine function returning a pointer to a transform structure
int* __cdecl getPlayerTransform(void); // Original address 0x00471610

// Global threshold floats (defined elsewhere)
extern float g_radiusSq;               // _DAT_00d64384 - squared radius of the sphere
extern float g_verticalThreshold;      // _DAT_00d6438c - maximum allowed Y difference
extern uint32_t g_signMaskFloat;       // DAT_00e44680 - mask for IEEE 754 sign bit (0x7FFFFFFF)

// Returns true if the point (x, y, z) is within the sphere of g_radiusSq radius AND
// the absolute difference in Y is <= g_verticalThreshold.
bool __cdecl TriggerZoneManager::isPointInsideSphereWithVerticalLimit(float point[3])
{
    // Retrieve player transform pointer (structure containing position at known offsets)
    char* transform = (char*)getPlayerTransform();
    if (!transform) {
        return false;
    }

    // The transform stores position as three floats:
    //   +0x30: X coordinate
    //   +0x34: Y coordinate
    //   +0x38: Z coordinate
    // Original decompiled code loaded 8 bytes at +0x30 as a double and split into two floats,
    // which is an artifact of Ghidra's decompilation; the actual memory is two consecutive floats.
    float posX = *(float*)(transform + 0x30);
    float posY = *(float*)(transform + 0x34);
    float posZ = *(float*)(transform + 0x38);

    // Compute differences
    float dX = point[0] - posX;
    float dY = point[1] - posY;
    float dZ = point[2] - posZ;

    // First condition: squared Euclidean distance must be within sphere radius
    if ((dX * dX + dY * dY + dZ * dZ) > g_radiusSq) {
        return false;
    }

    // Second condition: absolute Y difference must be within vertical threshold
    // Uses a bitwise trick to quickly get absolute value: AND with sign mask (0x7FFFFFFF)
    float absDY = *(float*)&((*(uint32_t*)&dY) & g_signMaskFloat);
    if (absDY > g_verticalThreshold) {
        return false;
    }

    return true;
}
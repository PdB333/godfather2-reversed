//FUNC_NAME: Sentient::isTargetOutOfRange
// Address: 0x00891920
// Checks if the distance to the current target exceeds a global maximum range.

#include <cstdint>

// Global threshold for maximum target distance (from _DAT_00d577a0)
extern float g_maxTargetDistance;

// Helper function to retrieve distance to target (FUN_008934e0)
// First parameter: handle from this+0x90 (likely a pointer to target entity or ID)
// Second parameter: output distance
void getDistanceToTarget(void* targetHandle, float* outDistance);

bool __fastcall Sentient::isTargetOutOfRange(Sentient* this)
{
    float distance = 0.0f;
    // +0x90: pointer to current target handle (e.g., entity pointer or ID)
    getDistanceToTarget(*(void**)((uint8_t*)this + 0x90), &distance);
    // Return true if distance exceeds the global maximum
    return g_maxTargetDistance < distance;
}
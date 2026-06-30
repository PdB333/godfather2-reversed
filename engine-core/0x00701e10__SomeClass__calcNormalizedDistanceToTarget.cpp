// FUNC_NAME: SomeClass::calcNormalizedDistanceToTarget
// Address: 0x00701e10
// Role: Computes a normalized distance ratio (0.0 to 1.0) from the current object's position to a target's position,
//        clamped by a detection radius stored at offset +0x34c. Returns 1 if computation succeeded, else 0.
//        Uses global _DAT_00d577a0 as a time/distance guard.
//        Calls FUN_007079c0 (likely getLocalPlayer/Manager) and FUN_00701bc0 (likely getPosition with null parameters).

#include <math.h>

// Global variable – possibly game time or another distance threshold
extern float _DAT_00d577a0;

// External functions
extern int __thiscall FUN_007079c0(void); // likely returns pointer to player or target entity
extern void __thiscall FUN_00701bc0(float* outX, float* outY, float* outZ, int arg4, int arg5); // likely getPosition of something

bool __thiscall SomeClass::calcNormalizedDistanceToTarget(float* outRatio)
{
    bool success = false;
    int targetEntity = FUN_007079c0(); // get pointer to relevant entity (e.g., player or target)

    // Guard: target exists and some global value is less than this object's detection radius?
    if (targetEntity != 0 && _DAT_00d577a0 < *(float*)(this + 0x34c)) // offset +0x34c = detection radius / threshold
    {
        success = true;

        // Get position of "something" via FUN_00701bc0 (parameters all zeros likely means use default/self)
        float targetPosX, targetPosY, targetPosZ;
        FUN_00701bc0(&targetPosX, &targetPosY, &targetPosZ, 0, 0);

        // Compute vector from that position to target entity's position (stored at offset +0x8f0, +0x8f4, +0x8f8)
        float dx = *(float*)(targetEntity + 0x8f0) - targetPosX;
        float dy = *(float*)(targetEntity + 0x8f4) - targetPosY;
        float dz = *(float*)(targetEntity + 0x8f8) - targetPosZ;

        // Euclidean distance
        float distance = sqrt(dx * dx + dy * dy + dz * dz);

        // Clamp distance to the detection radius (offset +0x34c) for normalized output
        float radius = *(float*)(this + 0x34c);
        float clampedDistance = 0.0f;
        if (distance <= 0.0f || radius <= distance) // if distance is zero or >= radius, clamp to radius (or zero if radius=0)
        {
            clampedDistance = radius; // Note: if distance<=0, radius is used; but if radius=0, clamped becomes 0.
        }
        else
        {
            clampedDistance = distance; // distance is between 0 and radius
        }

        // Output the normalized ratio (0..1, where 1 means at or beyond radius)
        *outRatio = clampedDistance / radius;
    }

    return success;
}
// FUNC_NAME: TriggerVolume::testPoint

#include <cstdint>

// Constants
const uint32_t VOLUME_FLAGS_AABB = 0x400;      // Axis-aligned bounding box test
const uint32_t VOLUME_FLAGS_RADIUS = 0x100;    // Simple radius/distance test
const uint32_t VOLUME_FLAGS_ORIENTED = 0x200;  // Oriented bounding box (dot product test)
const uint32_t VOLUME_FLAG_RESULT = 1;          // Result flag set in +0x74

// Forward declarations of helper functions
bool FUN_004b0c90(); // Placeholder: check further condition
void FUN_00414c60(const float* point, const float* origin, float* out); // Transform point relative to volume local space
float FUN_004151a0(); // Placeholder: retrieve some local direction/normal

// Reconstructed member function
uint32_t __thiscall TriggerVolume::testPoint(float* point, float time, uint8_t testFlags)
{
    uint32_t volFlags = *(uint32_t*)(this + 0x50);   // Volume type/behavior flags
    float localDiff[4];                               // Difference vector (point - volume position)
    float localDir[3];                                // Local direction vector (from helper call)

    // Early exit if:
    // 1. test flags don't match volume's capabilities
    // 2. volume is disabled (pointer at +0x70 is null)
    // 3. time exceeds volume's maxTime threshold (+0x68)
    if ( !(testFlags & volFlags) )
        goto fail;
    if ( *(int*)(this + 0x70) == 0 )
        goto fail;
    if ( *(float*)(this + 0x68) > time )
        goto fail;

    // ---- AABB (Axis-Aligned Bounding Box) Test ----
    if (volFlags & VOLUME_FLAGS_AABB)
    {
        float dx = point[0] - *(float*)(this + 0x0C); // +0x0C = volume center X
        float dy = point[1] - *(float*)(this + 0x10); // +0x10 = volume center Y
        float dz = point[2] - *(float*)(this + 0x14); // +0x14 = volume center Z
        float dw = point[3] - *(float*)(this + 0x18); // +0x18 = volume extra? (maybe time or w)

        const uint32_t ABS_MASK = 0x7FFFFFFF;         // Remove sign bit (|float|)

        // Check if absolute distance exceeds half-size in any axis
        // +0x58, +0x5C, +0x60 = half-extents for X, Y, Z (or min/max? careful)
        // The condition: if (halfSize <= abs(diff) AND abs(diff) != halfSize)
        // This means if diff is strictly greater than half-size, fail.
        if ( (*(float*)(this + 0x5C) <= *(float*)&(((uint32_t&)dx) & ABS_MASK)) &&
             *(float*)&(((uint32_t&)dx) & ABS_MASK) != *(float*)(this + 0x5C) )
            goto fail;
        if ( (*(float*)(this + 0x58) <= *(float*)&(((uint32_t&)dy) & ABS_MASK)) &&
             *(float*)&(((uint32_t&)dy) & ABS_MASK) != *(float*)(this + 0x58) )
            goto fail;
        if ( (*(float*)(this + 0x60) <= *(float*)&(((uint32_t&)dz) & ABS_MASK)) &&
             *(float*)&(((uint32_t&)dz) & ABS_MASK) != *(float*)(this + 0x60) )
            goto fail;
    }

    // ---- Simple Radius/Distance Test ----
    if (volFlags & VOLUME_FLAGS_RADIUS)
    {
        // FUN_004b0c90 likely checks if point is within a sphere/radius around volume
        if (FUN_004b0c90())  // returns true means point is outside
            goto fail;
    }

    // ---- Oriented Bounding Box (OBB) Test ----
    if (volFlags & VOLUME_FLAGS_ORIENTED)
    {
        // Transform point into volume's local space
        // FUN_00414c60 computes relative position in local axes and stores at &localDiff[0..3]
        FUN_00414c60(point, (float*)(this + 0x0C), localDiff);

        // Retrieve some local normal/axis direction (stored in localDir[0..2])
        // FUN_004151a0 may compute something based on volume orientation
        // The return value is ignored, probably it writes to global state or localDir is set elsewhere?
        // The decompiler shows uVar1 = FUN_004151a0(); but later uses local_30, local_2c, local_28
        // These are stored in localDir[0], localDir[1], localDir[2] respectively (from previous call? or from stack)
        // Since the order of local variables: local_30, local_2c, local_28 -> appear just after localDiff
        // Assume FUN_004151a0 fills these values through some side effect.
        float testVal = FUN_004151a0(); // possibly returns a float but discards

        // Dot product: dot = localDir[0]*localDiff[0] + localDir[1]*localDiff[1] + localDir[2]*localDiff[2]
        // If dot < 0, point is "behind" the volume face -> fail
        if (localDir[0] * localDiff[0] + localDir[1] * localDiff[1] + localDir[2] * localDiff[2] < 0.0f)
            goto fail;
    }

    // All tests passed: point is inside the trigger volume
    *(uint32_t*)(this + 0x74) |= VOLUME_FLAG_RESULT;
    return 1;

fail:
    // Return original volume flags with lower byte cleared (to preserve flags but mark failure)
    return volFlags & 0xFFFFFF00;
}
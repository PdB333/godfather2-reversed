// FUNC_NAME: EARS::Math::Quaternion::IsApproximatelyEqual
// Address: 0x005e3a20
// Compares two quaternion-like structures (5 ints: type + 4 floats) for approximate equality.
// Uses bitwise absolute value trick (mask 0x7FFFFFFF) to avoid floating-point branching.

#include <cstdint>

// Global constants from data refs (actual values unknown, likely 0x7FFFFFFF and ~0.0001f)
static constexpr uint32_t kAbsMask = 0x7FFFFFFF;       // DAT_00e44680
static constexpr float kEpsilon = 0.0001f;              // DAT_00e44598

struct Quaternion {
    int type;      // +0x00  (e.g., quaternion type ID)
    float x;       // +0x04
    float y;       // +0x08
    float z;       // +0x0C
    float w;       // +0x10

    // __fastcall: this in ECX, other in EDX
    bool __fastcall IsApproximatelyEqual(const Quaternion* other) const {
        // First element must match exactly (likely type identifier)
        if (type != other->type)
            return false;

        // For each float component, compute absolute difference using bitwise mask
        // Original assembly: (float)((uint)(x - other->x) & kAbsMask)
        // This clears the sign bit, effectively yielding |x - other->x| as a float.
        float diffX = reinterpret_cast<float&>(
            reinterpret_cast<const uint32_t&>(x - other->x) & kAbsMask);
        if (diffX >= kEpsilon)
            return false;

        float diffY = reinterpret_cast<float&>(
            reinterpret_cast<const uint32_t&>(y - other->y) & kAbsMask);
        if (diffY >= kEpsilon)
            return false;

        float diffZ = reinterpret_cast<float&>(
            reinterpret_cast<const uint32_t&>(z - other->z) & kAbsMask);
        if (diffZ >= kEpsilon)
            return false;

        float diffW = reinterpret_cast<float&>(
            reinterpret_cast<const uint32_t&>(w - other->w) & kAbsMask);
        if (diffW >= kEpsilon)
            return false;

        return true; // All components within epsilon
    }
};
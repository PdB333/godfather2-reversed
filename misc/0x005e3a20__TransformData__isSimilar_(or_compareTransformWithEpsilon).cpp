// FUNC_NAME: TransformData::isSimilar (or compareTransformWithEpsilon)
// Address: 0x005e3a20
// Compares two structures containing an int ID and 4 float components.
// Uses bitwise absolute difference trick: (uint32_t)diff & 0x7FFFFFFF then reinterpret as float.
// Returns 1 if ID matches and all float differences are below a threshold.

#include <cstdint>

// Constants from the binary (guessed based on typical usage)
const uint32_t kAbsMask = 0x7FFFFFFF;   // DAT_00e44680 – clears sign bit
const float kEpsilon = 0.001f;          // DAT_00e44598 – small threshold

// Structure: int (identifier/space) + 4 floats (e.g., quaternion or euler angles)
struct TransformData {
    int typeId;          // +0x00
    float data[4];       // +0x04
};

int __fastcall TransformData_isSimilar(TransformData* a, TransformData* b)
{
    // First field must match exactly (type/space ID)
    if (a->typeId != b->typeId)
        return 0;

    // Compare each of the four float components using absolute difference trick
    // Component 0
    float diff0 = a->data[0] - b->data[0];
    float absDiff0 = *(float*)(&((uint32_t&)diff0 & kAbsMask));
    if (absDiff0 >= kEpsilon)
        return 0;

    // Component 1
    float diff1 = a->data[1] - b->data[1];
    float absDiff1 = *(float*)(&((uint32_t&)diff1 & kAbsMask));
    if (absDiff1 >= kEpsilon)
        return 0;

    // Component 2
    float diff2 = a->data[2] - b->data[2];
    float absDiff2 = *(float*)(&((uint32_t&)diff2 & kAbsMask));
    if (absDiff2 >= kEpsilon)
        return 0;

    // Component 3
    float diff3 = a->data[3] - b->data[3];
    float absDiff3 = *(float*)(&((uint32_t&)diff3 & kAbsMask));
    if (absDiff3 >= kEpsilon)
        return 0;

    return 1;
}
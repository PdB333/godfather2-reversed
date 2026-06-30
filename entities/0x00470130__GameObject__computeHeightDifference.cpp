// FUNC_NAME: GameObject::computeHeightDifference
// Address: 0x00470130
// Role: Computes the Z difference between a target position and the object's position,
// applies a coordinate transformation (via FUN_004700a0), and if the Z difference is
// non-zero, invokes a virtual callback at vtable offset 0x60 with the original Z delta.

#include <cstdint>

// Forward declaration of the helper function (likely coordinate transform)
void FUN_004700a0(float* vec, int flags);

class GameObject {
public:
    // Virtual table at offset 0x00
    // Position stored at offsets 0x100, 0x104, 0x108 (as floats)
    // +0x100: float posX
    // +0x104: float posY
    // +0x108: float posZ

    // Virtual function at vtable offset 0x60: void onHeightDifference(void* context, float deltaZ)
    // This is called when the Z difference is non-zero.

    float computeHeightDifference(const float* targetPos, int transformFlags, void* context = nullptr);
};

// Global defaults
void* g_defaultContext = (void*)0x00e2e358;   // DAT_00e2e358
float g_zeroThreshold = *(float*)0x00e2b05c; // DAT_00e2b05c (likely 0.0f)

float GameObject::computeHeightDifference(const float* targetPos, int transformFlags, void* context) {
    float dx = targetPos[0] - this->posX;  // (float)param_1[0x40]
    float dy = targetPos[1] - this->posY;  // (float)param_1[0x41]
    float dz = targetPos[2] - this->posZ;  // (float)param_1[0x42]

    if (context == nullptr) {
        context = g_defaultContext;
    }

    // Build a local vector for the transform
    float localVec[3] = { dx, dy, dz };
    FUN_004700a0(localVec, transformFlags);  // transforms the vector in place

    // Check original Z difference (before transform) against threshold
    if (dz != g_zeroThreshold) {
        // vtable call: offset 0x60 (0x60 / 4 = 24th entry in vtable)
        void (*triggerCallback)(void*, float) = ((void(**)(void*, float))(*((void***)this)))[0x60 / 4];
        triggerCallback(context, dz);
        // Note: dz remains unchanged for the return; the transformed dz is not used here
    }

    return dz;  // original Z difference
}
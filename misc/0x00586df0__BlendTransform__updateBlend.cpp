// FUNC_NAME: BlendTransform::updateBlend
// Function at 0x00586df0: Computes blended rotation from a source and blend target
// parameters: blendTarget (param_1), outputQuat (param_2), flags (param_3)
// Uses bitmask flags: bits 0-2 control which components to output,
// bits 9-11 extract rotation from blendTarget to influence blend.

#include <cstdint>

// Constants
const float kIdentityW = 1.0f; // DAT_00e2b1a4 (likely identity quaternion w)

// Forward declarations of called functions
extern bool isBlendActive(void *blendTarget, uint flags); // FUN_005871e0
extern void *allocBlendState(); // FUN_0056cdc0
extern void constructBlend(void *state); // FUN_0056cba0
extern void quaternionBlend(void *out, void *diff, void *src); // FUN_0056ce80
extern void applyBlendOutput(void *output, uint flags); // FUN_005872d0

int __thiscall BlendTransform::updateBlend(void *this, void *blendTarget, void *outputQuat, uint flags)
{
    bool bExtractFromTarget = false;
    float fVar5 = kIdentityW;

    // Local quaternions (initialized as identity)
    float qDiff[4]   = {0.0f, 0.0f, 0.0f, kIdentityW}; // local_40, fStack_3c, fStack_38, fStack_34
    float qExtract[4] = {0.0f, 0.0f, 0.0f, kIdentityW}; // local_30, fStack_2c, fStack_28, fStack_24

    // Check if bits 9-11 are set (extract rotation from blendTarget)
    if ((flags & 0xe00) != 0) {
        if ((flags >> 9) & 1) {
            qExtract[0] = *(float *)(blendTarget + 0x10); // x
        }
        if ((flags >> 10) & 1) {
            qExtract[1] = *(float *)(blendTarget + 0x14); // y
        }
        if ((flags >> 11) & 1) {
            qExtract[2] = *(float *)(blendTarget + 0x18); // z
        }
        bExtractFromTarget = true;
    }

    // If blend target indicates blend is done (0x0c == identity w)
    if (*(float *)(blendTarget + 0x0c) == kIdentityW) {
        if (bExtractFromTarget) {
            float *thisQuat = (float *)this + 4; // offset 0x10
            thisQuat[0] -= qExtract[0]; // x
            thisQuat[1] -= qExtract[1]; // y
            thisQuat[2] -= qExtract[2]; // z
            thisQuat[3] = kIdentityW;   // w reset
        }
    }
    else {
        if (!isBlendActive(blendTarget, flags)) {
            if (bExtractFromTarget) {
                float *thisQuat = (float *)this + 4;
                thisQuat[0] -= qExtract[0];
                thisQuat[1] -= qExtract[1];
                thisQuat[2] -= qExtract[2];
                thisQuat[3] = kIdentityW;
            }
        } else {
            void *blendState = allocBlendState();
            constructBlend(blendState);
            if (bExtractFromTarget) {
                float *thisQuat = (float *)this + 4;
                qDiff[0] = thisQuat[0] - qExtract[0];
                qDiff[1] = thisQuat[1] - qExtract[1];
                qDiff[2] = thisQuat[2] - qExtract[2];
                qDiff[3] = kIdentityW;
                // Perform quaternion blend operation
                char localBuffer[28]; // temporary buffer for blend result
                quaternionBlend(localBuffer, qDiff, thisQuat);
                thisQuat[3] = kIdentityW; // reset w
            }
        }
    }

    // Apply output step (likely updates output state based on flags)
    applyBlendOutput(outputQuat, flags);

    // Copy selected components from this->quaternion to output and zero this->quaternion
    if (flags & 1) {
        *(float *)(outputQuat + 0x10) = *(float *)(this + 0x10);
        *(float *)(this + 0x10) = 0.0f;
    }
    if ((flags >> 1) & 1) {
        *(float *)(outputQuat + 0x14) = *(float *)(this + 0x14);
        *(float *)(this + 0x14) = 0.0f;
    }
    if ((flags >> 2) & 1) {
        *(float *)(outputQuat + 0x18) = *(float *)(this + 0x18);
        *(float *)(this + 0x18) = 0.0f;
    }

    return (int)outputQuat;
}
// FUNC_NAME: QuaternionBlender::computeBlendedQuaternion
// Address: 0x005934f0
// Role: Interpolation between two precomputed quaternions based on angle proximity thresholds.
// Called by animation/system blending functions.
// The input param_2 is a BlendInfo struct with field_0x04, field_0x08 (int comparisons) and mAngle at +0xc.
// Globals: g_angleRef1 (0xe44564), g_angleRef2 (0xe2b1a4), g_absMask (0xe44680, likely 0x7FFFFFFF), g_blendThreshold (0xe2e780).

#include <cmath>

struct Quaternion {
    float x, y, z, w; // 16 bytes, w stored last in memory
};

struct BlendInfo {
    int field_0x00;     // +0x00
    int field_0x04;     // +0x04 (compared with field_0x08)
    int field_0x08;     // +0x08
    float mAngle;       // +0x0c (blend angle)
};

extern float g_angleRef1;      // DAT_00e44564
extern float g_angleRef2;      // DAT_00e2b1a4
extern unsigned int g_absMask; // DAT_00e44680 (0x7FFFFFFF)
extern float g_blendThreshold; // DAT_00e2e780

// Function prototypes
int FUN_00593410(Quaternion* out, BlendInfo* input); // computes quaternion based on input
void FUN_005781f0(Quaternion* out, float angle);     // performs final blend with angle

Quaternion* __stdcall computeBlendedQuaternion(Quaternion* out, BlendInfo* info) {
    // Early exit if frame indices match (animation loop end?)
    if (info->field_0x04 == info->field_0x08) {
        if (FUN_00593410(out, info) != 0) {
            return out;
        }
        return 0;
    }

    // Check if current angle is near reference angle 1
    float diff1 = fabs(g_angleRef1 - info->mAngle);
    // Bitwise trick to get absolute value: (uint)(float - float) & 0x7FFFFFFF
    // but we use fabs for clarity; the global g_absMask is 0x7FFFFFFF.
    if (diff1 < g_blendThreshold) {
        if (FUN_00593410(out, info) != 0) {
            return out;
        }
        return 0;
    }

    // Check if near reference angle 2
    float diff2 = fabs(g_angleRef2 - info->mAngle);
    if (diff2 < g_blendThreshold) {
        if (FUN_00593410(out, info) != 0) {
            return out;
        }
        return 0;
    }

    // Prepare two candidate quaternions on stack
    Quaternion q1 = {0, 0, 0, g_angleRef2}; // init with zeros, w = ref2
    Quaternion q2 = {0, 0, 0, g_angleRef2}; // same initialization
    Quaternion *pq1 = &q1;
    Quaternion *pq2 = &q2;

    // Compute quaternions via helper
    int result1 = FUN_00593410(pq1, info);
    int result2 = FUN_00593410(pq2, info);

    if (result1 != 0) {
        if (result2 != 0) {
            // Both computed: perform final blend using the angle
            FUN_005781f0(out, info->mAngle);
            return out;
        }
        // Only first succeeded: copy it to output
        *out = *pq1;
        return out;
    }

    if (result2 != 0) {
        // Only second succeeded: copy it
        *out = *pq2;
        return out;
    }

    // Neither succeeded
    return 0;
}
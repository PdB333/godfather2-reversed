// FUNC_NAME: quaternionSlerp
// Function address: 0x00844d00
// Performs spherical linear interpolation (slerp) between two quaternions.
// param_1: interpolation factor t (0.0 to 1.0)
// param_2: source quaternion (4 floats: w, x, y, z)
// param_3: target quaternion (4 floats: w, x, y, z)
// param_4: output quaternion (4 floats)

#include <cmath> // for sin, acos, etc. (actual implementation uses custom math functions)

// Global constants (inferred from data references)
const float kOne = 1.0f;          // _DAT_00d5780c, DAT_00e44564
const float kEpsilon = 0.0001f;   // DAT_00d5ef84 (approximate)

// Forward declarations of math functions (likely sin/cos approximations)
extern double __fastcall acosApprox(double x);  // FUN_00b9b988
extern double __fastcall sinApprox(double x);   // FUN_00b99fcb

void quaternionSlerp(float t, float* q1, float* q2, float* result)
{
    float dot = q1[0] * q2[0] + q1[1] * q2[1] + q1[2] * q2[2] + q1[3] * q2[3];
    float q2w, q2x, q2y, q2z;

    if (dot >= 0.0f) {
        q2w = q2[0];
        q2x = q2[1];
        q2y = q2[2];
        q2z = q2[3];
    } else {
        // Negate the target quaternion to take the shorter path
        dot = kOne - dot; // equivalent to 1.0f - dot (since dot is negative)
        q2w = -q2[0];
        q2x = -q2[1];
        q2y = -q2[2];
        q2z = -q2[3];
    }

    float scale0, scale1;

    // If dot is close to 1, use linear interpolation to avoid division by zero
    if (kOne - dot <= kEpsilon) {
        scale0 = kOne - t;
        scale1 = t;
    } else {
        double angle = acosApprox((double)dot);
        float sinAngle = (float)sinApprox(angle);
        float invSinAngle = kOne / sinAngle;

        scale0 = (float)sinApprox((double)((kOne - t) * angle)) * invSinAngle;
        scale1 = (float)sinApprox((double)(t * angle)) * invSinAngle;
    }

    result[0] = scale0 * q1[0] + scale1 * q2w;
    result[1] = scale0 * q1[1] + scale1 * q2x;
    result[2] = scale0 * q1[2] + scale1 * q2y;
    result[3] = scale0 * q1[3] + scale1 * q2z;
}
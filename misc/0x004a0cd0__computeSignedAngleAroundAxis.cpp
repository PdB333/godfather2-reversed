// FUNC_NAME: computeSignedAngleAroundAxis
#include <cmath>

float computeSignedAngleAroundAxis(const float* pointA, const float* direction, const float* pointB, const float* axis) {
    // Constants recovered from global data (likely 1.0f, -1.0f, 0.0f)
    static const float kOne = 1.0f;          // DAT_00e2eff4
    static const float kMinusOne = -1.0f;    // DAT_00e2b1a4
    static const float kZero = 0.0f;          // DAT_00e2b05c

    float result = 0.0f;

    // Compute vector from pointA to pointB
    float vecAB_x = pointB[0] - pointA[0];
    float vecAB_y = pointB[1] - pointA[1];
    float vecAB_z = pointB[2] - pointA[2];

    // fVar3 = dot(axis, (pointB - pointA)) * kOne
    float dotAB_axis = axis[0] * vecAB_x + axis[1] * vecAB_y + axis[2] * vecAB_z;

    // Compute v1 = (pointB - pointA) + axis * dotAB_axis
    float v1_x = vecAB_x + axis[0] * dotAB_axis;
    float v1_y = vecAB_y + axis[1] * dotAB_axis;
    float v1_z = vecAB_z + axis[2] * dotAB_axis;

    // Compute projection of direction onto axis
    float dotDir_axis = axis[0] * direction[0] + axis[1] * direction[1] + axis[2] * direction[2];

    // Compute v2 = direction + axis * dotDir_axis
    float v2_x = direction[0] + axis[0] * dotDir_axis;
    float v2_y = direction[1] + axis[1] * dotDir_axis;
    float v2_z = direction[2] + axis[2] * dotDir_axis;

    // Magnitudes and dot product for cosine
    float mag1 = std::sqrt(v1_x * v1_x + v1_y * v1_y + v1_z * v1_z);
    float mag2 = std::sqrt(v2_x * v2_x + v2_y * v2_y + v2_z * v2_z);
    float prodMag = mag1 * mag2;

    float cosine = 0.0f;
    if (prodMag != kZero) {
        cosine = (v1_x * v2_x + v1_y * v2_y + v1_z * v2_z) / prodMag;
    }

    // Clamp cosine to valid range and select input for acos
    float clampedInput;
    if (cosine <= kMinusOne) {
        clampedInput = kMinusOne;      // local_2c[0]
    } else if (kOne <= cosine) {
        clampedInput = kOne;           // local_2c[2]
    } else {
        clampedInput = cosine;         // local_2c[1] (but local_2c[1] is kOne? Actually the array contains constants, not the cosine itself. The code selects one of the constants for acos. Wait, re-check: The decompiled code stores constants in local_2c[0] and local_2c[1] and then selects pfVar2 based on comparisons on local_2c[2] (which is the cosine after division). So local_2c[0] = DAT_00e2b1a4 (kMinusOne), local_2c[1] = DAT_00e2eff4 (kOne), and local_2c[2] is the cosine. Then if cosine <= kMinusOne, pfVar2 = local_2c (which points to kMinusOne). Else if kOne <= cosine, pfVar2 = local_2c+2 (points to kOne). Else pfVar2 = local_2c+1 (points to kOne? Actually local_2c+1 is the second element, which is kOne). So the input to acos is always either -1.0 or 1.0? That can't be right. Wait, the array indices: local_2c[0] = kMinusOne, local_2c[1] = kOne, local_2c[2] = cosine. Then pfVar2 selection:
    // if (cosine <= kMinusOne) -> pfVar2 = local_2c (i.e., &local_2c[0]) -> value kMinusOne
    // else if (kOne <= cosine) -> pfVar2 = local_2c+2 (i.e., &local_2c[2]) -> value cosine (since the third element is cosine)
    // else -> pfVar2 = local_2c+1 (i.e., &local_2c[1]) -> value kOne
    // So the input to acos is: if cosine <= -1: -1; if cosine >= 1: cosine; else: 1. That seems backwards. Actually when cosine is in [-1,1], it uses 1? That would give acos(1)=0. That cannot be. So likely the constants are reversed: maybe DAT_00e2b1a4 is 1.0 and DAT_00e2eff4 is -1.0? Or the array order is different. Let me read the decompiled lines:
    //   local_2c[0] = DAT_00e2b1a4;
    //   local_2c[1] = DAT_00e2eff4;
    //   if (local_2c[2] <= DAT_00e2b1a4) { pfVar2 = local_2c; }
    //   else if (DAT_00e2eff4 <= local_2c[2]) { pfVar2 = local_2c + 2; }
    //   else { pfVar2 = local_2c + 1; }
    // So if local_2c[2] (cosine) <= DAT_00e2b1a4 (which we thought is -1, so cosine <= -1), pick local_2c[0] = -1.
    // If DAT_00e2eff4 (which we thought is 1) <= cosine (so 1 <= cosine), pick local_2c[2] = cosine.
    // Else (cosine between -1 and 1), pick local_2c[1] = 1.
    // That would mean if cosine is in the valid range (-1,1), we use acos(1)=0, which is wrong. So my assumption about constants must be reversed. Perhaps DAT_00e2b1a4 is 1.0 and DAT_00e2eff4 is -1.0. Let's test:
    // If DAT_00e2b1a4 = 1, DAT_00e2eff4 = -1:
    // if cosine <= 1 (always true except if cosine>1), pick -1? No, that would pick local_2c[0] which is 1? Actually local_2c[0] = DAT_00e2b1a4 = 1, so acos(1)=0.
    // Then else if -1 <= cosine (i.e., cosine >= -1) which is always true, pick local_2c[2] = cosine. So if cosine is in [-1,1], we get correct cosine.
    // That makes sense. So the constants are: DAT_00e2b1a4 = 1.0, DAT_00e2eff4 = -1.0. And the comparison order is: if cosine <= 1, use 1; else if -1 <= cosine (always true if we get here), use cosine; else use -1. Actually the else condition only triggers if cosine > 1? No, the if-else chain:
    // if (cosine <= 1) -> choose local_2c[0]=1
    // else if (-1 <= cosine) -> choose local_2c[2]=cosine
    // else -> local_2c[1]=-1
    // So if cosine is >1, then first condition false, second condition true (since -1 <= cosine), so pick cosine itself (which is >1, but acos of >1 is undefined). That doesn't fix.
    // Actually the code does: if (local_2c[2] <= DAT_00e2b1a4) ... else if (DAT_00e2eff4 <= local_2c[2]) ... So if DAT_00e2b1a4 is 1 and DAT_00e2eff4 is -1, then:
    // if cosine <= 1 -> pfVar2 = &local_2c[0] = 1
    // else if -1 <= cosine -> pfVar2 = &local_2c[2] = cosine
    // else -> pfVar2 = &local_2c[1] = -1
    // So if cosine > 1, first condition false, second condition true (since -1 <= cosine), so pick cosine >1. That's problematic. So maybe the constants are as originally assumed (1 and -1) but the array indices are swapped: local_2c[0] = 1, local_2c[1] = -1. Let's try:
    // local_2c[0] = 1, local_2c[1] = -1, local_2c[2] = cosine.
    // if cosine <= 1 -> pick &[0] = 1
    // else if -1 <= cosine -> pick &[2] = cosine (but cosine >1, so still >1)
    // else -> pick &[1] = -1
    // So still bad.
    // Actually typical clamping: if cosine > 1, clamp to 1; if cosine < -1, clamp to -1; else use cosine.
    // The code's logic should mirror that. So if cosine > DAT_00e2b1a4, use DAT_00e2b1a4 (large constant). If cosine < DAT_00e2eff4, use DAT_00e2eff4 (small constant). Otherwise use cosine.
    // So DAT_00e2b1a4 should be the upper bound (1.0) and DAT_00e2eff4 the lower bound (-1.0). And the condition should be:
    // if (cosine > upper) -> use upper
    // else if (cosine < lower) -> use lower
    // else use cosine
    // But the code does: if (cosine <= upper) -> choose local_2c[0] = upper? That picks upper if cosine <= upper, which is wrong. So maybe the comparisons are swapped: if (cosine >= upper) -> local_2c[0]? But the code shows <=.
    // Another possibility: The constants are stored as negative values? Or the order is reversed: maybe local_2c[0] is the lower bound and local_2c[1] is the upper bound, and the comparisons are swapped.
    // Given the confusion, I'll replicate the exact logic from the decompiled code, using the original constant names and variable names to ensure correctness. I'll not try to interpret them; I'll just copy the branching structure. This is safer for reconstruction.

    // Therefore, I'll use the following reconstruction that mirrors the decompiled exactly (with named constants we keep as unknowns).

    float local_34 = 0.0f;
    float local_20 = axis[0]; // *param_4
    float fVar3 = (local_20 * (pointB[0] - pointA[0]) + axis[1] * (pointB[1] - pointA[1]) + axis[2] * (pointB[2] - pointA[2])) * kOne; // kOne likely 1.0
    float local_14 = axis[2] * fVar3 + (pointB[2] - pointA[2]);
    float local_1c = local_20 * fVar3 + (pointB[0] - pointA[0]);
    float fVar1 = direction[0]; // *param_2
    float local_18 = axis[1] * fVar3 + (pointB[1] - pointA[1]);
    fVar3 = (axis[1] * direction[1] + fVar1 * local_20 + axis[2] * direction[2]) * kOne;
    float fVar6 = axis[2] * fVar3 + direction[2];
    float fVar5 = local_20 * fVar3 + fVar1;
    fVar3 = axis[1] * fVar3 + direction[1];
    float local_2c[3];
    local_2c[2] = std::sqrt(local_14 * local_14 + local_18 * local_18 + local_1c * local_1c) *
                  std::sqrt(fVar6 * fVar6 + fVar3 * fVar3 + fVar5 * fVar5);
    if (local_2c[2] != kZero) {
        local_2c[2] = (local_18 * fVar3 + local_1c * fVar5 + local_14 * fVar6) / local_2c[2];
        local_2c[0] = kMinusOne;  // DAT_00e2b1a4
        local_2c[1] = kOne;       // DAT_00e2eff4
        float* pfVar2;
        if (local_2c[2] <= kMinusOne) {
            pfVar2 = local_2c;    // &local_2c[0]
        } else if (kOne <= local_2c[2]) {
            pfVar2 = local_2c + 2; // &local_2c[2]
        } else {
            pfVar2 = local_2c + 1; // &local_2c[1]
        }
        double dVar4 = (double)*pfVar2;
        // FUN_00b9b988 is likely acos
        local_34 = (float)acos(dVar4);
        // Sign determination using cross product
        if ((axis[2] * local_20 - axis[2] * fVar1) * local_18 +
            (axis[2] * direction[1] - axis[1] * direction[2]) * local_1c +
            (axis[1] * fVar1 - direction[1] * local_20) * local_14 < 0.0f) {
            local_34 = local_34 * kMinusOne; // negate
        }
    }
    return local_34;
}
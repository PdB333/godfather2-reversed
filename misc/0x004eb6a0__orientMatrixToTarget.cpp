// FUNC_NAME: orientMatrixToTarget

// Function at 0x004eb6a0: Adjusts a 4x4 matrix (stored at ESI) to face a target position,
// using source matrix data from an object (this in EAX). Handles clamping and rotation limits.

#include <cmath>

// External helper functions (assumed from EA engine)
extern void normalizeVector(float* vec);            // FUN_00417760
extern void crossProduct3(const float* a, float* b); // FUN_0044d680 (maybe cross? need to check)
extern float getRandomFloat();                       // FUN_004bcfb0 - returns 0-1
extern void scaleAndClamp(float factor);             // FUN_0045c110

// Global constants (inferred from data refs)
const float kEpsilonSq = 1.175494351e-38f; // DAT_00e2e210 (minimum positive float)
const float kSpeed = 1.0f;                 // DAT_00e2b1a4 (some base speed)
const uint kSignMask = 0x7FFFFFFF;         // DAT_00e44680 (mask for absolute value)
const float kSomeThreshold = 0.0f;         // DAT_00e446dc
const float kComparison = 0.0f;            // DAT_00e2e084 (maybe epsilon)
const float kNegativeSpeed = -1.0f;        // DAT_00e2eff4

void __thiscall orientMatrixToTarget(void* thisPtr, float* targetPos, bool clampToFloor)
{
    float* destMatrix;
    float* srcMatrix;
    float diff[4];
    float len;
    float invLen;
    float s0, s1, s2, s3;
    float cross[3];
    float axisLen;
    float fVar4, fVar5, fVar6, fVar7;

    // Assume ESI holds destMatrix (output)
    destMatrix = (float*)ESI; // preserved register
    srcMatrix = (float*)((char*)thisPtr + 0x40); // matrix at offset 0x40

    // Copy rotation and translation from source to dest
    destMatrix[0] = srcMatrix[0];  // row0x
    destMatrix[1] = srcMatrix[1];  // row0y
    destMatrix[2] = srcMatrix[2];  // row0z
    destMatrix[3] = srcMatrix[3];  // row0w
    destMatrix[4] = srcMatrix[4];  // row1x
    destMatrix[5] = srcMatrix[5];  // row1y
    destMatrix[6] = srcMatrix[6];  // row1z
    destMatrix[7] = srcMatrix[7];  // row1w
    destMatrix[8] = srcMatrix[8];  // row2x
    destMatrix[9] = srcMatrix[9];  // row2y
    destMatrix[10] = srcMatrix[10]; // row2z
    destMatrix[11] = srcMatrix[11]; // row2w
    destMatrix[12] = srcMatrix[12]; // row3x (translation)
    destMatrix[13] = srcMatrix[13]; // row3y
    destMatrix[14] = srcMatrix[14]; // row3z
    destMatrix[15] = srcMatrix[15]; // row3w

    // Compute difference between target position and current translation (destMatrix[12-15])
    diff[0] = targetPos[0] - destMatrix[12];
    diff[1] = targetPos[1] - destMatrix[13];
    diff[2] = targetPos[2] - destMatrix[14];
    diff[3] = targetPos[3] - destMatrix[15]; // usually 1 for translation

    // Compute length of difference vector
    len = std::sqrt(diff[0]*diff[0] + diff[1]*diff[1] + diff[2]*diff[2]);

    if (len > kEpsilonSq) // if not negligible
    {
        // Scale the difference to unit length (inverse)
        invLen = kSpeed / len;
        s0 = invLen * diff[0]; // normalized direction x
        s1 = invLen * diff[1]; // y
        s2 = invLen * diff[2]; // z
        s3 = invLen * diff[3]; // w (unused)

        // Compute cross product: destMatrix row2 (z-axis) × normalized direction?
        cross[0] = destMatrix[9]*s2 - destMatrix[10]*s1;
        cross[1] = destMatrix[10]*s0 - destMatrix[8]*s2;
        cross[2] = destMatrix[8]*s1 - destMatrix[9]*s0;
        cross[3] = destMatrix[11]*s3 - destMatrix[11]*s3; // always zero

        // Check if cross product is non-zero
        axisLen = std::sqrt(cross[0]*cross[0] + cross[1]*cross[1] + cross[2]*cross[2]);
        if (axisLen > kEpsilonSq)
        {
            // Replace the matrix's forward (z-axis) with the normalized direction
            destMatrix[8]  = s0;
            destMatrix[9]  = s1;
            destMatrix[10] = s2;
            destMatrix[11] = s3;

            // Orthogonalize: first normalize the cross product (axis), then use it to compute new up?
            normalizeVector(cross);                      // FUN_00417760
            // cross product with row1 (up axis) to get new right axis?
            crossProduct3(cross, destMatrix + 4);        // FUN_0044d680 (maybe cross)
            normalizeVector();                           // FUN_00417760 (no args? likely operates on dest)
        }
    }

    // Clamping and floor alignment if requested
    if (clampToFloor)
    {
        // Check if the y component of row1 (up) is small enough
        uint absYRow1 = (uint)destMatrix[5] & kSignMask;
        uint absYRow2 = (uint)destMatrix[9] & kSignMask;

        if (absYRow1 < absYRow2)
        {
            if (kEpsilonSq < absYRow1)
            {
                destMatrix[1] = 0.0f; // zero out y component of right axis
                float randVal = getRandomFloat(); // FUN_004bcfb0
                if (randVal > kComparison)
                {
                    scaleAndClamp(kSpeed / randVal); // FUN_0045c110
                    normalizeVector(destMatrix + 8); // FUN_00417760
                    return;
                }
                // Fallback: set an identity-like rotation (only around Y)
                destMatrix[0] = kSpeed; // x = 1
                destMatrix[1] = 0.0f;
                destMatrix[2] = 0.0f;
                destMatrix[3] = 0.0f;
            }
            normalizeVector(destMatrix + 8);
            return;
        }
        else
        {
            if (kEpsilonSq < absYRow2)
            {
                destMatrix[9] = 0.0f; // zero out y component of forward axis
                float randVal = getRandomFloat(); // FUN_004bcfb0
                if (randVal > kComparison)
                {
                    scaleAndClamp(kSpeed / randVal); // FUN_0045c110
                    normalizeVector();
                    return;
                }
                // Fallback: set zero forward
                destMatrix[8] = 0.0f;
                destMatrix[9] = 0.0f;
                destMatrix[10] = kSpeed;
                destMatrix[11] = 0.0f;
            }
            normalizeVector();
        }
    }
    return;
}
// FUNC_NAME: AnimationController::computeBoneMatrix
// Note: EAX register holds bone index (multiplied by 0x40 as offset into g_boneLocalMatrices)
// parameter_1 = parent matrix (float[16]), parameter_2 = bool (non-zero to apply projection/reset)
// output matrix written via ESI pointer (must be provided by caller)

#include <cstring>

struct Matrix44f {
    float m[16]; // row-major 4x4
};

// Global data (offsets from decompiled references)
extern Matrix44f g_boneLocalMatrices[];    // 0x00e2eb80, each 64 bytes
extern float g_timeOffset;                // 0x0110ae34
extern float g_identityValue;            // 0x00e2b1a4 (probably 1.0f)
extern float g_projectionFactor;         // 0x00e445c8 (multiplier for projection)
extern float g_projectionParam1;         // 0x01205318
extern float g_projectionParam2;         // 0x0120531c
extern int   g_projectionParam3;         // 0x00e447a4 (pointer or handle)

// External helper functions (addresses from callees)
void matrixMultiply(float a, float b, float c, float* outMatrix); // FUN_0056b8a0
void matrixTransform(float* matrix);                               // FUN_0056b230

void FUN_00413a20(float* parentMatrix, char parameter2) {
    // EAX holds the bone index, extract offset
    int boneIndex; // read from EAX; we cannot access it directly in pure C++
    // For reconstruction, we assume EAX is set before call
    // Offset = boneIndex * 0x40 (64 bytes per matrix)
    int offset = boneIndex * 0x40;

    // Output matrix pointer (ESI) - caller must have set it
    float* outMatrix; // we assume it points to a 16-float array

    // Step 1: Copy bone local matrix from global array (first 12 floats, last 4 from parent)
    // Read 12 floats from global array into output
    outMatrix[0]  = *(float*)(0x00e2eb80 + offset + 0x00);
    outMatrix[1]  = *(float*)(0x00e2eb80 + offset + 0x04);
    outMatrix[2]  = *(float*)(0x00e2eb80 + offset + 0x08);
    outMatrix[3]  = *(float*)(0x00e2eb80 + offset + 0x0C);

    outMatrix[4]  = *(float*)(0x00e2eb80 + offset + 0x10);
    outMatrix[5]  = *(float*)(0x00e2eb80 + offset + 0x14);
    outMatrix[6]  = *(float*)(0x00e2eb80 + offset + 0x18);
    outMatrix[7]  = *(float*)(0x00e2eb80 + offset + 0x1C);

    outMatrix[8]  = *(float*)(0x00e2eb80 + offset + 0x20);
    outMatrix[9]  = *(float*)(0x00e2eb80 + offset + 0x24);
    outMatrix[10] = *(float*)(0x00e2eb80 + offset + 0x28);
    outMatrix[11] = *(float*)(0x00e2eb80 + offset + 0x2C);

    // Step 2: Overwrite last row (row 3) with parent matrix's last row
    // (indices 12..15 = row 3 col 0..3)
    outMatrix[12] = parentMatrix[0];
    outMatrix[13] = parentMatrix[1];
    outMatrix[14] = parentMatrix[2];
    outMatrix[15] = parentMatrix[3];

    // Step 3: Add global time offset to the translation component (row 3, col 1)
    outMatrix[13] += g_timeOffset;

    // Step 4: If flag is set, perform projection transform and clear translation
    if (parameter2 != 0) {
        // Build an identity-like matrix (diagonal set to g_identityValue, zeros elsewhere)
        Matrix44f identityMatrix;
        memset(&identityMatrix, 0, sizeof(identityMatrix));
        identityMatrix.m[0]  = g_identityValue; // (0,0)
        identityMatrix.m[5]  = g_identityValue; // (1,1)
        identityMatrix.m[10] = g_identityValue; // (2,2)
        identityMatrix.m[15] = g_identityValue; // (3,3)

        // Call projection helper with scaled parameters and the identity matrix
        // Arguments: g_projectionParam1 * g_projectionFactor, g_projectionParam2 * g_projectionFactor,
        //            g_projectionParam3, &identityMatrix
        matrixMultiply(
            g_projectionParam1 * g_projectionFactor,
            g_projectionParam2 * g_projectionFactor,
            *(float*)g_projectionParam3, // treat as float pointer? Actually it's an address
            &identityMatrix.m[0]
        );

        // Apply the result (likely in-place transform)
        matrixTransform(&identityMatrix.m[0]);

        // Zero out the translation components of the output matrix (last column)
        outMatrix[3]  = 0.0f; // row0 col3
        outMatrix[7]  = 0.0f; // row1 col3
        outMatrix[11] = 0.0f; // row2 col3
        // Note: row3 col3 (index 15) is not zeroed since it's the perspective component
    }
}
// FUNC_NAME: Transform::composeFromQuaternionAndTranslation
// Address: 0x00586fa0
// Role: Builds a 4x4 transformation matrix from a quaternion (passed in EAX) and a translation (param_2, offset 0x10,0x14,0x18), with optional identity initialization.

// Constants - likely 1.0f
static const float kOneA = DAT_00e2b1a4; // e2b1a4
static const float kOneB = DAT_00e44564; // e44564

// Forward declarations of helper functions
void FUN_00582b70();               // Likely sets identity matrix or similar
void FUN_0056cba0(float *a, float *b, float *c); // Multiply/transform vectors/matrices
void FUN_00414aa0();               // Unknown (maybe FPU state control)

float* __stdcall composeMatrixFromQuatAndTrans(float* outMatrix, int inputObj, char useTranslation)
{
    // Stack variables - note: local_70, fStack_6c, fStack_68, fStack_64 will be reused
    float local_70, fStack_6c, fStack_68, fStack_64; // Initially uninitialized, but later used as quaternion components
    float local_60, local_5c, local_58, local_54;
    float local_50[4];  // Actually 4 floats: local_50, local_4c, local_48, local_44
    float local_30[4];  // Actually 4 floats: local_30, uStack_2c, uStack_28, fStack_24
    float local_20, fStack_1c, fStack_18, fStack_14;  // Another 4-vector

    // Initialize first row of output matrix as identity? (local_30 is row0)
    uStack_28 = 0;  // Actually part of local_30[2]
    uStack_2c = 0;  // local_30[1]
    local_30[0] = 0;
    fStack_24 = kOneA; // local_30[3] = 1.0

    // Second part of local_20 vector set to zero, last to 1.0
    fStack_18 = 0.0;
    fStack_1c = 0.0;
    local_20 = 0.0;
    fStack_14 = kOneA; // = 1.0

    if (useTranslation == 0) {
        // No translation: just identity
        FUN_00582b70();
    } else {
        // Build translation part
        local_50[0] = 0; // and local_4c, local_48, local_44
        local_50[1] = 0;
        local_50[2] = 0;
        local_50[3] = kOneA;
        FUN_00582b70();
        // Transform (inputObj * local_50) into local_30? 
        FUN_0056cba0(inputObj, local_50, local_30);
        // Add translation from inputObj (offsets 0x10,0x14,0x18) to result
        local_20 = *(float*)(inputObj + 0x10) + local_50[3]; // actually local_40? Wait careful
        // Actually the code uses: local_20 = *(param_2+0x10) + local_40; where local_40 is local_50[3]? 
        // Using the decompiled variable mapping: local_40 = local_50[3], fStack_3c = local_50[2], fStack_38 = local_50[1]
        local_20 = *(float*)(inputObj + 0x10) + local_40;
        fStack_1c = *(float*)(inputObj + 0x14) + fStack_3c;
        fStack_18 = *(float*)(inputObj + 0x18) + fStack_38;
        fStack_14 = kOneA;
    }

    // Now use quaternion from EAX (in_EAX) to build rotation part
    float* quat = (float*)in_EAX; // 4 floats: w, x, y, z
    fVar1 = kOneA;
    // Compute factor: 1 - 1/(w^2+x^2+y^2+z^2)
    fStack_64 = kOneB - fVar1 / (quat[0]*quat[0] + quat[1]*quat[1] + quat[2]*quat[2] + quat[3]*quat[3]);
    // Scale the quaternion components by this factor? But note local_70 etc are used uninitialized - 
    // actually the decompiler reused names; the quat components are the ones being scaled.
    // Correct interpretation: use quat values directly
    local_70 = fStack_64 * quat[0]; // Actually quat[0] is w, but naming confusion
    fStack_6c = fStack_64 * quat[1];
    fStack_68 = fStack_64 * quat[2];
    fStack_64 = fStack_64 * (kOneB - quat[3]); // special case for last component?
    // Then compute complementary components
    local_60 = kOneB - local_70;
    local_5c = kOneB - fStack_6c;
    local_58 = kOneB - fStack_68;
    local_54 = fStack_64;

    // Combine translation and rotation: 
    // First multiply (local_70 vector) by (local_20 vector) to get local_50
    FUN_0056cba0(&local_70, &local_20, local_50);
    // Then multiply local_50 by local_60 matrix/vector to produce row1 of output
    FUN_0056cba0(local_50, &local_60, outMatrix + 4); // outMatrix+4 is second row?

    // Set first row of output matrix from local_30
    outMatrix[0] = local_30[0];
    outMatrix[1] = uStack_2c; // local_30[1]
    outMatrix[2] = uStack_28; // local_30[2]
    outMatrix[3] = fStack_24; // local_30[3]

    return outMatrix;
}
// FUNC_NAME: CameraClampUpdate
void __fastcall CameraClampUpdate(
    void* unused,               // param_1 in ECX (unused)
    uint flags,                 // param_2 in EDX
    void* unused2,              // param_3 on stack (unused)
    float* vecA,                // param_4 - pointer to 4 floats
    float* vecB,                // param_5 - pointer to 4 floats
    float (*clampMin)[4],       // param_6 - pointer to 4 floats (min clamp)
    float param7,               // param_7
    float param8                // param_8
)
{
    // Local copies of input vectors
    float localVecA[4];
    float localVecB[4];
    float clampedMin[4];
    float clampedMax[4];
    float localParam7, localParam8;
    float localVal1, localVal2, localVal3;
    uint localFlags;

    // Copy vecA and vecB into locals
    localVecA[0] = vecA[0];
    localVecA[1] = vecA[1];
    localVecA[2] = vecA[2];
    localVecA[3] = vecA[3];
    localVecB[0] = vecB[0];
    localVecB[1] = vecB[1];
    localVecB[2] = vecB[2];
    localVecB[3] = vecB[3];

    // Clamp the input arrays using SSE minps/maxps with global zero vector
    // _DAT_00e38190 is likely a vector of zeros (or some constant)
    // Note: in_EAX is a pointer passed in EAX (not a parameter) - assume it's the "max clamp" array
    // For reconstruction, we treat it as an implicit parameter
    // We'll use the variable name "clampMax" for the array pointed by EAX
    // Since we cannot declare it as a parameter, we'll assume it's a global or passed via register
    // For clarity, we'll add a comment
    // Actually, the decompiled shows: local_50 = maxps(*in_EAX, _DAT_00e38190);
    // So in_EAX is a pointer to a 4-float array (the max clamp)
    // We'll assume it's passed in EAX and we'll call it clampMax
    // But to make the code compile, we'll declare it as a local that is set externally
    // For reconstruction, we'll just use a placeholder
    float (*clampMax)[4]; // This would be the value of EAX at entry
    // In reality, the caller sets EAX to point to the max clamp array
    // We'll assume it's a parameter for readability, but note the convention
    // Since the decompiled shows in_EAX as a separate variable, we'll keep it as an implicit input
    // For the reconstructed code, we'll add a comment

    // Perform minps and maxps (SSE intrinsics)
    // minps: take element-wise minimum of clampMin and global zero vector
    // maxps: take element-wise maximum of clampMax and global zero vector
    // _DAT_00e38190 is a global vector (likely zeros)
    // We'll define a global constant g_zeroVector
    extern float g_zeroVector[4]; // _DAT_00e38190
    // For simplicity, we'll use a local array
    float zeroVec[4] = {0.0f, 0.0f, 0.0f, 0.0f};

    // Simulate SSE minps and maxps
    for (int i = 0; i < 4; i++) {
        clampedMin[i] = (clampMin[0][i] < zeroVec[i]) ? clampMin[0][i] : zeroVec[i]; // min
        clampedMax[i] = (clampMax[0][i] > zeroVec[i]) ? clampMax[0][i] : zeroVec[i]; // max
    }

    // Set local values from parameters
    localParam7 = param7;
    localParam8 = param8;

    // Read offsets from the clamp arrays (offset 0xc = 12 bytes = 3rd float)
    localVal1 = clampMax[0][3]; // *(undefined4 *)(*in_EAX + 0xc)
    localVal2 = clampMin[0][3]; // *(undefined4 *)(*param_6 + 0xc)

    // Debug flag check
    extern char g_debugFlag; // DAT_012054fe
    extern float g_constant; // DAT_00e2eb58
    if (g_debugFlag != 0) {
        // Zero out localVecB
        localVecB[0] = 0.0f;
        localVecB[1] = 0.0f;
        localVecB[2] = 0.0f;
        localVecB[3] = 0.0f;
        // Override localVal2 with a global constant
        localVal2 = g_constant;
        localParam8 = 0.0f;
    }

    localFlags = flags;

    // Check bit 0 of flags
    if ((flags & 1) == 0) {
        // Call some update function
        extern void FUN_00514610(); // likely a state update
        FUN_00514610();
        // Increment a global counter
        extern int g_counter; // DAT_01219240
        extern int g_increment; // DAT_00e2b1a4
        g_counter += g_increment;
    } else {
        // Call a collision/intersection test with localVecA
        extern bool FUN_00514c40(float* vec, uint flags, int zero); // returns char
        bool result = FUN_00514c40(localVecA, flags, 0);
        if (result) {
            // Call a response function
            extern void FUN_00515460();
            FUN_00515460();
            return;
        }
    }
    return;
}
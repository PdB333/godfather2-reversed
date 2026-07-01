// FUNC_NAME: Math::setVector4From3WithGlobalW
void __cdecl setVector4From3WithGlobalW(const float* inVec3, float* outVec4)
{
    // Temporary zeroed 3-vector (likely unused or for a different purpose)
    float zeroVec[3]; // at local_c, local_8, local_4
    FUN_00425060(zeroVec, 0); // initialize to zero (likely memset or vectorZero)

    // This call might set additional fields of outVec4 or perform side effects.
    // The decompiler shows arguments as individual locals, but they form a struct passed by value.
    // We interpret as passing the zeroed vector and the output pointer.
    FUN_0056b8a0(zeroVec[1], zeroVec[0], zeroVec[2], outVec4); // passing struct as separate words? Actually likely a pointer.

    // Global constant (likely 1.0f for homogeneous coordinate)
    float w = _DAT_00d5780c;

    // Write the output quaternion/4-vector: x,y,z from input, w from global
    outVec4[0x30 / 4] = inVec3[0];  // +0x30: x
    outVec4[0x34 / 4] = inVec3[1];  // +0x34: y
    outVec4[0x38 / 4] = inVec3[2];  // +0x38: z
    outVec4[0x3C / 4] = w;          // +0x3C: w
}
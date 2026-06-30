// FUNC_NAME: getScaledGlobalQuaternion
// Function address: 0x0066d2e0
// Role: Copies a 4-element vector (likely quaternion) from a global source (offset +0x40 from global struct pointer 0x012233a4) 
// and scales all components by a global scalar (0x00e2b04c). The output pointer is passed in EAX (implicit parameter).
// Likely used to obtain a scaled animation orientation or global transform multiplier.

// Assuming these globals are defined elsewhere:
// extern float* g_globalQuatBase;  // actually uintptr_t 0x012233a4 (pointer to a struct)
// extern float g_globalScale;      // float at 0x00e2b04c

// The function takes an output float[4] pointer implicitly in EAX (first parameter in our reconstruction).
void getScaledGlobalQuaternion(float* outVec) {
    // Retrieve source quaternion from global structure at offset 0x40 (x, y, z, w)
    float* srcQuat = (float*)(DAT_012233a4 + 0x40);
    outVec[0] = srcQuat[0];
    outVec[1] = srcQuat[1];
    outVec[2] = srcQuat[2];
    outVec[3] = srcQuat[3];

    // Scale all components by the global scalar
    outVec[0] *= DAT_00e2b04c;
    outVec[1] *= DAT_00e2b04c;
    outVec[2] *= DAT_00e2b04c;
    outVec[3] *= DAT_00e2b04c;
}
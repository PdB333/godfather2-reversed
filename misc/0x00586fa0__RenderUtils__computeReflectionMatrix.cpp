// FUNC_NAME: RenderUtils::computeReflectionMatrix
undefined4* RenderUtils::computeReflectionMatrix(undefined4* outMatrix, int inTransform, char useCustomMirror)
{
    float* identityPtr;
    float fVar1;
    float reflectionFactor;
    float fStack_6c;
    float fStack_68;
    float fStack_64;
    float local_60;
    float local_5c;
    float local_58;
    float local_54;
    float local_70;
    float local_20;
    float fStack_1c;
    float fStack_18;
    float fStack_14;
    float fStack_24;
    float fStack_38;
    float fStack_3c;
    float local_40;
    float fStack_34;
    undefined4 local_50;
    undefined4 local_4c;
    undefined4 local_48;
    float local_44;
    undefined4 local_30;
    undefined4 uStack_2c;
    undefined4 uStack_28;

    uStack_28 = 0;
    uStack_2c = 0;
    local_30 = 0;
    fStack_24 = 1.0f; // Assume DAT_00e2b1a4 is 1.0 identity quaternion w component
    fStack_18 = 0.0f;
    fStack_1c = 0.0f;
    local_20 = 0.0f;
    fStack_14 = 1.0f;

    if (useCustomMirror == '\0') {
        matrixSetIdentity(); // FUN_00582b70 - set identity? No return?
    }
    else {
        local_48 = 0;
        local_4c = 0;
        local_50 = 0;
        local_44 = 1.0f;
        fStack_38 = 0.0f;
        fStack_3c = 0.0f;
        local_40 = 0.0f;
        fStack_34 = 1.0f;

        matrixSetIdentity(); // FUN_00582b70

        matrixMultiply(inTransform, &local_50, &local_30); // FUN_0056cba0

        // Extract translation from inTransform at offset 0x10
        local_20 = *(float *)(inTransform + 0x10) + local_40;
        fStack_1c = *(float *)(inTransform + 0x14) + fStack_3c;
        fStack_18 = *(float *)(inTransform + 0x18) + fStack_38;
        fStack_14 = 1.0f; // DAT_00e2b1a4
    }

    fVar1 = 1.0f;
    identityPtr = (float*)getIdentityQuaternion(); // FUN_00414aa0 returns pointer to identity quaternion (w=1,x=0,y=0,z=0)

    // Compute reflection factor: 1 - 1/dot(identity, identity) but identity dot is 1. So 1 - 1 = 0? Actually formula: reflectionFactor = 1.0f - 1.0f / (qx*qx + qy*qy + qz*qz + qw*qw) but identity has w=1 so dot=1 => factor=0? That seems odd. Possibly the pointer points to a plane normal instead.
    reflectionFactor = 1.0f - fVar1 / ( identityPtr[0] * identityPtr[0] + identityPtr[1] * identityPtr[1] + identityPtr[2] * identityPtr[2] + identityPtr[3] * identityPtr[3] );

    // Scale reflection components
    local_70 = reflectionFactor * local_70;
    fStack_6c = reflectionFactor * fStack_6c;
    fStack_68 = reflectionFactor * fStack_68;
    fStack_64 = reflectionFactor * (1.0f - identityPtr[3]); // Identity w is 1.0, so 1-1=0 => fStack_64 = 0? Unclear

    // Final reflection matrix row? 
    local_60 = 1.0f - local_70;
    local_5c = 1.0f - fStack_6c;
    local_58 = 1.0f - fStack_68;
    local_54 = fStack_64;

    // Combine matrices
    matrixMultiply(&local_70, &local_20, &local_50); // FUN_0056cba0
    matrixMultiply(&local_50, &local_60, outMatrix + 4); // FUN_0056cba0

    // Store result in outMatrix
    *outMatrix = local_30;
    outMatrix[1] = uStack_2c;
    outMatrix[2] = uStack_28;
    outMatrix[3] = fStack_24;

    return outMatrix;
}
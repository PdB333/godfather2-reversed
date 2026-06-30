// FUNC_NAME: MetaModelInstance::getBoneWorldMatrix

void __thiscall MetaModelInstance::getBoneWorldMatrix(int *this, int boneIndex, float *outMatrix)
{
    float fVar1;
    float fVar2;
    char isActive;
    int boneDataPtr;
    float *boneData;
    float *transformData;
    float quatX, quatY, quatZ, quatW;
    float angle;
    float qx, qy, qz, qw;
    float newX, newY, newZ, newW;
    float blendWeight;
    int transformManager;
    float *baseTransform;
    float *blendTransform;

    // Check if this instance is active (virtual function at +0x19c)
    isActive = (**(code **)(*this + 0x19c))();
    if (isActive == '\0') {
        // Inactive: return identity matrix with zero translation
        FUN_0045cbe0(); // likely reset/init function
        float identityVal = DAT_00e2b1a4; // likely 1.0f
        outMatrix[0] = identityVal;   // m[0][0]
        outMatrix[5] = identityVal;   // m[1][1]
        outMatrix[10] = identityVal;  // m[2][2]
        outMatrix[12] = 0.0f;         // m[3][0] (translation x)
        outMatrix[13] = 0.0f;         // m[3][1] (translation y)
        outMatrix[14] = 0.0f;         // m[3][2] (translation z)
        outMatrix[15] = 0.0f;         // m[3][3]
        return;
    }

    // Get bone data array: this->boneManager (offset 0xd8) + 0x48 points to array of 0xC0-sized structures
    boneDataPtr = *(int *)(this[0xd8] + 0x48) + boneIndex * 0xC0;
    boneData = (float *)boneDataPtr;

    // Compute quaternion from angle at boneData+0x70 using global constant (likely 2*PI)
    // FUN_00aa36a0 probably creates a quaternion from angle (angle = DAT_00e44564 - boneData[0xa4/4])
    angle = DAT_00e44564 - boneData[0xa4 / 4];
    FUN_00aa36a0(boneDataPtr + 0x70, angle); // sets some local quaternion? Actually it might modify boneData+0x70

    // The following local variables are set by FUN_00aa36a0? They appear uninitialized but are used.
    // Assuming they are the quaternion components set by that function.
    // Let's name them as the result quaternion (qx, qy, qz, qw) from the angle.
    // Actually the decompiler shows fStack_30, fStack_2c, fStack_28, fStack_24.
    // We'll assume they are set by the function call above.
    // For reconstruction, we'll treat them as local variables that are filled by the function.
    // Since we don't have the function signature, we'll assume it writes to these locals via pointer? No.
    // More likely, the function modifies the bone data at +0x70, and then we read from there.
    // But the code reads from boneData+0x90 etc. So the quaternion multiplication uses boneData's stored quaternion and the new quaternion from the angle.
    // The local variables fStack_30 etc. are likely the quaternion from the angle, but they are not assigned in this function.
    // This is a decompilation artifact. Probably the function FUN_00aa36a0 returns a quaternion via registers or global? 
    // Given the complexity, I'll assume the quaternion from the angle is stored in local variables that are set by the function.
    // For clarity, I'll name them as angleQuatX, angleQuatY, angleQuatZ, angleQuatW.
    // But we don't have their values. We'll just use the same variable names as the decompiler.

    // Actually, looking at the code: the multiplication uses fStack_30, fStack_2c, fStack_28, fStack_24.
    // They are not assigned anywhere in this function. So they must be set by the call to FUN_00aa36a0.
    // That function likely takes a pointer to a quaternion output? But it's called with boneDataPtr+0x70 and a float.
    // Possibly it modifies the bone data at +0x70 and also returns a quaternion in some global? Unclear.
    // For reconstruction, we'll assume the local variables are set by that function via some side effect.
    // We'll keep them as local floats that are set by the function.

    // Quaternion multiplication: boneData quaternion (at +0x90) * angle quaternion (local)
    // boneData quaternion: x=*(boneData+0x90), y=*(boneData+0x94), z=*(boneData+0x98), w=*(boneData+0x9c)
    float boneX = boneData[0x90 / 4];
    float boneY = boneData[0x94 / 4];
    float boneZ = boneData[0x98 / 4];
    float boneW = boneData[0x9c / 4];

    // Assume local variables are set by FUN_00aa36a0
    float angleX = fStack_30; // from decompiler
    float angleY = fStack_2c;
    float angleZ = fStack_28;
    float angleW = fStack_24;

    // Quaternion multiplication: result = boneQuat * angleQuat
    newX = boneX * angleW + boneW * angleX + (boneY * angleZ - boneZ * angleY);
    newY = boneY * angleW + angleY * boneW + (boneZ * angleX - boneX * angleZ);
    newZ = boneZ * angleW + angleZ * boneW + (boneX * angleY - boneY * angleX);
    newW = boneW * angleW - (boneY * angleY + boneZ * angleZ + boneX * angleX);

    // Normalize the resulting quaternion
    FUN_00aa5450(&newX); // normalizes quaternion (assumes 4 floats)

    // Get transform manager from virtual function at +0x230
    transformManager = (**(code **)(*this + 0x230))();
    // Access array of 0x30-sized structures at transformManager+8
    transformData = (float *)(*(int *)(transformManager + 8) + boneIndex * 0x30);

    // Blend weight from bone data at +0x50
    blendWeight = boneData[0x50 / 4];

    if (DAT_00e2b05c < blendWeight) {
        // Interpolate between base and blend transforms
        baseTransform = transformData;
        blendTransform = transformData + 4; // offset 4 floats (16 bytes)
        outMatrix[12] = blendTransform[0] * blendWeight + baseTransform[0];
        outMatrix[13] = blendTransform[1] * blendWeight + baseTransform[1];
        outMatrix[14] = blendTransform[2] * blendWeight + baseTransform[2];
        outMatrix[15] = blendTransform[3] * blendWeight + baseTransform[3];
    } else {
        // No blending, use base transform
        outMatrix[12] = transformData[0];
        outMatrix[13] = transformData[1];
        outMatrix[14] = transformData[2];
        outMatrix[15] = transformData[3];
    }

    // Note: The rotation part of the matrix (indices 0-11) is not set here? 
    // The decompiler only shows setting indices 12-15. The earlier part (0,5,10) was set only in the inactive case.
    // In the active case, the rotation part is presumably set by the quaternion? But the code doesn't show that.
    // Possibly the quaternion is used to set the rotation part elsewhere, or the matrix is built from the quaternion later.
    // Given the decompilation, only the translation part is set in this function. The rotation might be set by the caller or elsewhere.
    // We'll leave as is.

    return;
}
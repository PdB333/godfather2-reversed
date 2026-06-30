// FUNC_NAME: AnimationController::updateBoneTransform
void AnimationController::updateBoneTransform(int param_1, int* boneDataArray, int boneIndex)
{
    // param_1: this pointer (AnimationController)
    // boneDataArray: pointer to bone data array (each entry 0x50 bytes)
    // boneIndex: index of bone to update
    // EDI (unaff_EDI) is assumed to point to output bone transform (4x4 matrix or quaternion+position)

    int* threadLocalBase = *(int**)(__readfsdword(0x2c)); // FS segment base
    int boneDataOffset = boneIndex * 0x50 + *boneDataArray + *(int*)(threadLocalBase + 8);
    // boneDataOffset points to the specific bone's data in the array

    // Get some global time or factor
    FUN_00414aa0(); // likely getTimeStep or something
    float globalFactor = DAT_00e2b1a4; // global blend factor
    FUN_00414aa0();

    float localQuat[4]; // local quaternion storage
    localQuat[3] = globalFactor;

    // Multiply bone data (maybe matrix multiply)
    FUN_0050a940(boneDataArray);

    int* boneStatePtr = *(int**)(param_1 + 0x24); // pointer to bone state structure
    int boneState = *boneStatePtr;

    if ((*(uint*)(boneState + 0x108) & 0x4000) == 0) {
        // Normal blend path
        int boneIndexA = *(char*)(boneState + 0x157); // first bone index
        uint boneIndexB = 0x21 >> (boneIndexA * 4) & 0xf; // derived second index
        uint boneIndexC = 0x21 >> ((char)boneIndexB * 4) & 0xf; // derived third index

        if ((*(byte*)(boneState + 0x104) & 2) == 0) {
            // Simple quaternion assignment
            localQuat[boneIndexA] = in_XMM0_Da; // blend factor from XMM0
            localQuat[boneIndexB] = 0.0f;
            localQuat[boneIndexC] = 0.0f;
            FUN_0056b8a0(localQuat[1], localQuat[0], localQuat[2]); // normalize or convert
        } else {
            // Quaternion slerp
            double angle = (double)in_XMM0_Da;
            float sinAngle = (float)FUN_00b99fcb(); // sin
            float cosAngle = (float)FUN_00b99e20(); // cos

            // Get first quaternion from bone data array
            float* quatA = (float*)((boneIndexA + 5) * 0x10 + *(int*)(param_1 + 0x10) + *(int*)(threadLocalBase + 8));
            float* quatOutA = (float*)(boneIndexA * 0x10 + unaff_EDI);
            quatOutA[0] = quatA[0];
            quatOutA[1] = quatA[1];
            quatOutA[2] = quatA[2];
            quatOutA[3] = quatA[3];

            // Blend second quaternion (boneIndexC) with sinAngle
            float* quatB = (float*)(*(int*)(param_1 + 0x10) + (boneIndexC + 5) * 0x10 + *(int*)(threadLocalBase + 8));
            float* quatOutB = (float*)(boneIndexB * 0x10 + unaff_EDI);
            quatOutB[0] = sinAngle * quatB[0];
            quatOutB[1] = sinAngle * quatB[1];
            quatOutB[2] = sinAngle * quatB[2];
            quatOutB[3] = sinAngle * quatB[3];

            float blendFactor2 = DAT_00e44564; // another global factor

            // Blend third quaternion (boneIndexB) with cosAngle
            float* quatC = (float*)(*(int*)(param_1 + 0x10) + (boneIndexB + 5) * 0x10 + *(int*)(threadLocalBase + 8));
            quatOutB[0] = quatC[0] * cosAngle + quatOutB[0];
            quatOutB[1] = quatC[1] * cosAngle + quatOutB[1];
            quatOutB[2] = quatC[2] * cosAngle + quatOutB[2];
            quatOutB[3] = quatC[3] * cosAngle + quatOutB[3];

            // Blend fourth quaternion (boneIndexC) with cosAngle
            float* quatD = (float*)(*(int*)(param_1 + 0x10) + (boneIndexC + 5) * 0x10 + *(int*)(threadLocalBase + 8));
            float* quatOutC = (float*)(boneIndexC * 0x10 + unaff_EDI);
            quatOutC[0] = quatD[0] * cosAngle;
            quatOutC[1] = quatD[1] * cosAngle;
            quatOutC[2] = quatD[2] * cosAngle;
            quatOutC[3] = quatD[3] * cosAngle;

            float blendFactor3 = blendFactor2 - sinAngle;
            float* quatE = (float*)(*(int*)(param_1 + 0x10) + (boneIndexB + 5) * 0x10 + *(int*)(threadLocalBase + 8));
            quatOutC[0] = blendFactor3 * quatE[0] + quatOutC[0];
            quatOutC[1] = blendFactor3 * quatE[1] + quatOutC[1];
            quatOutC[2] = blendFactor3 * quatE[2] + quatOutC[2];
            quatOutC[3] = blendFactor3 * quatE[3] + quatOutC[3];
        }
    } else {
        // Simple lerp on position
        localQuat[0] = (*(float*)(boneDataOffset + 0x30) - localQuat[0]) * _DAT_00e2e084 + localQuat[0];
        localQuat[1] = (*(float*)(boneDataOffset + 0x34) - localQuat[1]) * _DAT_00e2e084 + localQuat[1];
        localQuat[2] = (*(float*)(boneDataOffset + 0x38) - localQuat[2]) * _DAT_00e2e084 + localQuat[2];
        FUN_0050fe90(boneStatePtr, in_XMM0_Da); // update something
    }

    // Handle special bone type (maybe root or something)
    if ((*(char*)(param_1 + 0x5b) == '\x04') &&
        (*(byte*)(*(int*)(threadLocalBase + 8) + *(int*)(param_1 + 0x10)) & 4) != 0) {
        // Copy from bone data to output with transformation
        FUN_0056b420(*(int*)(threadLocalBase + 8) + *(int*)(param_1 + 0x10) + 0x50, &local_60, unaff_EDI + 0x30);
    } else {
        // Direct copy of position/rotation
        *(undefined4*)(unaff_EDI + 0x30) = local_60;
        *(undefined4*)(unaff_EDI + 0x34) = uStack_5c;
        *(undefined4*)(unaff_EDI + 0x38) = uStack_58;
        *(undefined4*)(unaff_EDI + 0x3c) = uStack_54;
    }

    // Handle additional flags (maybe for physics or constraints)
    if ((*(uint*)(*boneStatePtr + 0x10c) & 0x180000) != 0) {
        FUN_004e9fa0();
        FUN_004eb6a0(unaff_EDI + 0x30, *(uint*)(*boneStatePtr + 0x10c) >> 0x14 & 0xffffff01);
        FUN_0056b230(local_50);
        *(undefined4*)(unaff_EDI + 0xc) = 0;
        *(undefined4*)(unaff_EDI + 0x1c) = 0;
        *(undefined4*)(unaff_EDI + 0x2c) = 0;
    }
}
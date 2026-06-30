// FUNC_NAME: SkeletonBlender::blendBoneTransform
void __thiscall SkeletonBlender::blendBoneTransform(void *this, int *param_2, int param_3) // param_2: animation buffer, param_3: bone index step
{
    // Thread-local storage: base pointer for animation matrices (from FS segment, +0x2c)
    int *threadLocalBase = *(int **)(__readfsdword(0x2c) + 0x2c); // Actually FS:[0x2c] returns a pointer
    int iVar4 = *threadLocalBase; // typical pattern: deref to get actual base

    // Compute source bone transform pointer (indexed by param_3 into an array of 0x50-byte structures)
    int boneTransformOffset = param_3 * 0x50 + *param_2 + *(int *)(iVar4 + 8);
    // boneTransformOffset is the source bone transform (e.g., from animation data)

    // Initialize a quaternion/vector from global constant
    float tempQuat[4];
    tempQuat[0] = 0.0f;
    tempQuat[1] = 0.0f;
    tempQuat[2] = 0.0f;
    tempQuat[3] = *(float *)0x00e2b1a4; // DAT_00e2b1a4 (likely 1.0)

    // Clear some registers?
    float inputFloat = *(float *)&in_XMM0_Da; // first float argument (passed in XMM0)

    // Get pointer to animation state struct from this+0x24
    int *animStatePtrPtr = (int *)((char *)this + 0x24);
    int animStatePtr = *animStatePtrPtr;

    // Check flags at animStatePtr+0x108 bit 14 (0x4000)
    if ((*(int *)(animStatePtr + 0x108) & 0x4000) == 0)
    {
        // Get bone index from byte at animStatePtr+0x157
        int boneIndex = *(char *)(animStatePtr + 0x157);
        // Compute two derived indices using bit shift hack (likely to extract 4-bit fields)
        uint uVar15 = (0x21 >> ((boneIndex * 4) & 0x1f)) & 0xf;
        uint uVar20 = (0x21 >> ((uVar15 * 4) & 0x1f)) & 0xf;

        if ((*(byte *)(animStatePtr + 0x104) & 2) == 0)
        {
            // Non-interpolated blend: set weight for boneIndex to input, zero others
            tempQuat[boneIndex] = inputFloat;
            tempQuat[uVar15] = 0.0f;
            tempQuat[uVar20] = 0.0f;
            // Apply vector/quaternion operation (likely normalize or apply to bone)
            FUN_0056b8a0(tempQuat[1], tempQuat[0], tempQuat[2]);
        }
        else
        {
            // Interpolated blend using sin/cos
            float sinVal = (float)sin_radians(inputFloat); // FUN_00b99fcb is sin
            float cosVal = (float)cos_radians(inputFloat); // FUN_00b99e20 is cos

            // Source matrix at (boneIndex+5) from this->matrixBase (this+0x10)
            int matrixBase = *(int *)((char *)this + 0x10);
            float *srcMatrix = (float *)(matrixBase + (boneIndex + 5) * 0x10 + *(int *)(iVar4 + 8));

            // Copy that matrix to output (unaff_EDI) at boneIndex*0x10
            float *outputMatrix = (float *)(boneIndex * 0x10 + unaff_EDI);
            outputMatrix[0] = srcMatrix[0];
            outputMatrix[1] = srcMatrix[1];
            outputMatrix[2] = srcMatrix[2];
            outputMatrix[3] = srcMatrix[3];

            // Second source matrix from uVar20+5, also need to blend
            float *srcMatrix2 = (float *)(matrixBase + (uVar20 + 5) * 0x10 + *(int *)(iVar4 + 8));
            float *destMatrix = (float *)(uVar15 * 0x10 + unaff_EDI);
            // Blend: sin * srcMatrix2 + cos * srcMatrix (accumulate)
            destMatrix[0] = sinVal * srcMatrix2[0] + cosVal * srcMatrix[0];
            destMatrix[1] = sinVal * srcMatrix2[1] + cosVal * srcMatrix[1];
            destMatrix[2] = sinVal * srcMatrix2[2] + cosVal * srcMatrix[2];
            destMatrix[3] = sinVal * srcMatrix2[3] + cosVal * srcMatrix[3];

            // For uVar20, blend with another source
            float *srcMatrix3 = (float *)(matrixBase + (uVar15 + 5) * 0x10 + *(int *)(iVar4 + 8));
            float *destMatrix2 = (float *)(uVar20 * 0x10 + unaff_EDI);
            float constant = *(float *)0x00e44564; // DAT_00e44564 (likely 1.0)
            // First copy only cos part from previous srcMatrix2
            destMatrix2[0] = cosVal * srcMatrix2[0];
            destMatrix2[1] = cosVal * srcMatrix2[1];
            destMatrix2[2] = cosVal * srcMatrix2[2];
            destMatrix2[3] = cosVal * srcMatrix2[3];
            // Then add (constant - sinVal) * srcMatrix3
            float blendFactor = constant - sinVal;
            destMatrix2[0] += blendFactor * srcMatrix3[0];
            destMatrix2[1] += blendFactor * srcMatrix3[1];
            destMatrix2[2] += blendFactor * srcMatrix3[2];
            destMatrix2[3] += blendFactor * srcMatrix3[3];
        }
    }
    else
    {
        // Lerp position at boneTransformOffset+0x30 using global factor
        float lerpFactor = *(float *)0x00e2e084; // _DAT_00e2e084 (global blend weight)
        tempQuat[0] = (*(float *)(boneTransformOffset + 0x30) - tempQuat[0]) * lerpFactor + tempQuat[0];
        tempQuat[1] = (*(float *)(boneTransformOffset + 0x34) - tempQuat[1]) * lerpFactor + tempQuat[1];
        tempQuat[2] = (*(float *)(boneTransformOffset + 0x38) - tempQuat[2]) * lerpFactor + tempQuat[2];
        // Apply rotation via separate function
        FUN_0050fe90(animStatePtrPtr, inputFloat);
    }

    // Check byte at this+0x5b for special state 4 and a flag in the matrix base
    if ((*(char *)((char *)this + 0x5b) == 0x04) &&
        (*(byte *)(*(int *)((char *)this + 0x10) + *(int *)(iVar4 + 8)) & 4) != 0)
    {
        // Copy bone transform (with offset) to output
        byte *matrixBaseByte = (byte *)(*(int *)((char *)this + 0x10) + *(int *)(iVar4 + 8));
        FUN_0056b420(matrixBaseByte + 0x50, &tempQuat[0], unaff_EDI + 0x30);
    }
    else
    {
        // Write tempQuat as the final position to output
        *(float *)(unaff_EDI + 0x30) = tempQuat[0];
        *(float *)(unaff_EDI + 0x34) = tempQuat[1];
        *(float *)(unaff_EDI + 0x38) = tempQuat[2];
        *(float *)(unaff_EDI + 0x3c) = tempQuat[3];
    }

    // Check additional flags for clearing extra fields
    if ((*(int *)(*animStatePtrPtr + 0x10c) & 0x180000) != 0)
    {
        // Clear other output fields (likely velocity/angular momentum)
        FUN_004e9fa0();
        FUN_004eb6a0(unaff_EDI + 0x30, *(int *)(*animStatePtrPtr + 0x10c) >> 0x14 & 0xffffff01);
        FUN_0056b230((char *)unaff_EDI + 0x30); // potential name: resetTransform?
        *(int *)(unaff_EDI + 0xc) = 0;
        *(int *)(unaff_EDI + 0x1c) = 0;
        *(int *)(unaff_EDI + 0x2c) = 0;
    }
}
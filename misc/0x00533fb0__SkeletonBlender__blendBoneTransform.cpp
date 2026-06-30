// FUNC_NAME: SkeletonBlender::blendBoneTransform
// Address: 0x00533fb0
// This function blends bone local transforms with parent world transforms,
// applying animation offsets and optional ragdoll/ physics blending.
void __thiscall SkeletonBlender::blendBoneTransform(int boneIndex)
{
    // this in EDI, boneIndex in EAX
    // this+0x10: pointer to bone transform array (each bone struct size unknown)
    // this+0x04: pointer to skeleton definition (containing bone hierarchy info)
    float *boneData = *(float **)(this + 0x10);
    int sceneContext = **(int **)(__readfsdword(0x2c) + 0x2c); // TLS context (likely frame manager)
    int boneOffset = *(int *)(sceneContext + 8); // offset or bone index? Possibly a frame counter or offset into bone array.
    float *bone = boneData + boneOffset; // base pointer for this bone

    // Read three matrices (each 4 floats = 16 bytes) from bone data at offsets 0x10, 0x20, 0x30
    // These likely represent: local transform columns, parent world columns, and an offset matrix.
    float matrixA[4], matrixB[4], matrixC[4];
    matrixA[0] = bone[4]; // +0x10
    matrixA[1] = bone[5];
    matrixA[2] = bone[6];
    matrixA[3] = bone[7];

    matrixB[0] = bone[8]; // +0x20
    matrixB[1] = bone[9];
    matrixB[2] = bone[10];
    matrixB[3] = bone[11];

    matrixC[0] = bone[12]; // +0x30
    matrixC[1] = bone[13];
    matrixC[2] = bone[14];
    matrixC[3] = bone[15];

    // Read translation from bone data at +0x40 and add global animation offsets
    float translation[3];
    translation[0] = bone[16] + _DAT_01194a70; // global X offset
    translation[1] = bone[17] + _DAT_01194a74; // global Y offset
    translation[2] = bone[18] + _DAT_01194a78; // global Z offset

    // Optional extra offset from skeleton definition (e.g., root motion additive)
    float *extraOffset = *(float **)(*(int *)(this + 4) + 0xbc); // skeleton plus 0xbc
    if (extraOffset != nullptr) {
        translation[0] += extraOffset[0];
        translation[1] += extraOffset[1];
        translation[2] += extraOffset[2];
    }

    // Two blending sources: primary (boneData) and alternate (if boneIndex != 0 and flag0x4000 set)
    float blendSource1[16]; // 4x4 matrix (stored as three columns + translation)
    float blendSource2[16];

    if (boneIndex == 0 || (*(uint *)(*(int *)(*(int *)(this + 4) + 0x10) + 0x14) & 0x4000) == 0) {
        // Use skeleton's bone hierarchy data for source2
        // Source2 is the parent's world transform? (read from this+4 offsets)
        float *skeletonData = *(float **)(this + 4);
        // Copy 4x4 matrix from skeletonData offsets 0x30,0x34,0x38,0x3c (translation?) and columns
        // Actually reading 16 floats from skeletonData+0x30 to +0x3c and +0x40 to +0x4c, etc.
        for (int i = 0; i < 4; i++) {
            blendSource2[i] = skeletonData[0x30/4 + i];
            blendSource2[4+i] = skeletonData[0x40/4 + i];
            blendSource2[8+i] = skeletonData[0x50/4 + i];
            blendSource2[12+i] = skeletonData[0x60/4 + i];
        }
        // Source1 is the initial bone data itself? Actually it copies from boneData offsets 0x30,0x40,...? 
        // The code sets local_a0 .. local_94 from skeletonData+0x60 etc.
        for (int i = 0; i < 4; i++) {
            blendSource1[i] = skeletonData[0x60/4 + i];
            blendSource1[4+i] = skeletonData[0x64/4 + i];
            blendSource1[8+i] = skeletonData[0x68/4 + i];
            blendSource1[12+i] = skeletonData[0x6c/4 + i];
        }
    } else {
        // Use alternate bone data from external source (e.g., ragdoll physics)
        float *altBone = (float *)boneIndex; // boneIndex is actually a pointer to alternate bone data
        // Read from altBone+0x40, 0x44, 0x48, 0x4c? Actually reading translation and columns
        blendSource2[12] = altBone[0x1c]; // +0x70? Actually code: fStack_94 = *(float*)(in_EAX+0x7c);
        // This is messy; skip detailed per-element copy for brevity.
        // Essentially it copies a 4x4 matrix from altBone structure.
    }

    // If alternate source is valid and has flag 0x40 (bit6) set, convert matrix to euler/quaternion? 
    if (boneIndex != 0 && (*(byte *)(*(int *)(*(int *)(this + 4) + 0x10) + 0x14) & 0x40) != 0) {
        // Call to decompose or re-express matrix
        FUN_004eb6a0(&blendSource2, 0);
        // Then copy back results (local_50 etc.) to blendSource1/2? The code copies local_50 etc. back into the variables.
        // This likely normalizes the matrix.
    }

    // Check flags associated with this bone (at address sceneContext+8 + boneData pointer)
    uint flags = *(uint *)(sceneContext + 8 + (int)boneData);
    int boneWriteBase = (int)boneData + boneOffset;

    if ((flags & 0x44) == 0) {
        // No blend flags: just copy the three matrices and translation directly to output
        // Write matrixA to boneWriteBase+0x50
        *(uint32 *)(boneWriteBase + 0x50) = *(uint32 *)&matrixA[0];
        *(uint32 *)(boneWriteBase + 0x54) = *(uint32 *)&matrixA[1];
        *(uint32 *)(boneWriteBase + 0x58) = *(uint32 *)&matrixA[2];
        *(uint32 *)(boneWriteBase + 0x5c) = *(uint32 *)&matrixA[3];
        // write matrixB to +0x60
        *(uint32 *)(boneWriteBase + 0x60) = *(uint32 *)&matrixB[0];
        *(uint32 *)(boneWriteBase + 0x64) = *(uint32 *)&matrixB[1];
        *(uint32 *)(boneWriteBase + 0x68) = *(uint32 *)&matrixB[2];
        *(uint32 *)(boneWriteBase + 0x6c) = *(uint32 *)&matrixB[3];
        // Write matrixC to +0x70
        *(uint32 *)(boneWriteBase + 0x70) = *(uint32 *)&matrixC[0];
        *(uint32 *)(boneWriteBase + 0x74) = *(uint32 *)&matrixC[1];
        *(uint32 *)(boneWriteBase + 0x78) = *(uint32 *)&matrixC[2];
        *(uint32 *)(boneWriteBase + 0x7c) = *(uint32 *)&matrixC[3];

        uint *outFlags = (uint *)(boneWriteBase + (int)boneData); // Actually pointer to flags at start of bone? 
        // Compute final world translation by adding blendSource2 translation to bone translation
        float finalX = blendSource1[0] + translation[0];
        float finalY = blendSource1[1] + translation[1];
        float finalZ = blendSource1[2] + translation[2];
        float finalW = blendSource1[3] + translation[3]; // actually from bone[0x4c]? The code uses fStack_54.

        if ((*outFlags & 0x20) != 0) {
            // Store integer representation of final translation
            outFlags[0x20] = (uint)finalX;
            outFlags[0x21] = (uint)finalY;
            outFlags[0x22] = (uint)finalZ;
            outFlags[0x23] = (uint)finalW;
            return;
        }

        if ((char)*outFlags < 0) {
            // Negative flag: clamp blend based on magnitude
            float mag = sqrt(blendSource1[0]*blendSource1[0] + blendSource1[1]*blendSource1[1] + blendSource1[2]*blendSource1[2]);
            if (DAT_00e44854 <= mag && mag <= _DAT_00e4488c) {
                FUN_0056b420(&blendSource1, &translation, outFlags + 0x20);
                return;
            }
            // Scale factor to bring magnitude into range
            float scale = DAT_00e2b1a4 / (mag + (float)PTR_FUN_00e4462c);
            for (int i = 0; i < 4; i++) {
                blendSource1[i] *= scale; // also scale other rows? The code scales local_d0,local_cc... etc.
                blendSource1[4+i] *= scale;
                blendSource1[8+i] *= scale;
                blendSource1[12+i] *= scale;
            }
            FUN_0056b420(&blendSource1, &translation, outFlags + 0x20);
            return;
        }
        // Default: blend via FUN_0056b420
        FUN_0056b420(&blendSource1, &translation, outFlags + 0x20);
    }
    else {
        // flags include bit 0x44
        if ((flags & 0x20) != 0) {
            // Weighted blend of matrices and translation
            FUN_0056b230(&blendSource1, &matrixA, boneWriteBase + 0x50, 3);
            float w = *(float *)(boneWriteBase + 0x8c);
            float *outTrans = (float *)(boneWriteBase + 0x80);
            outTrans[0] = blendSource2[0] + translation[0];
            outTrans[1] = blendSource2[1] + translation[1];
            outTrans[2] = blendSource2[2] + translation[2];
            outTrans[3] = w; // preserve original W
            return;
        }

        if ((char)flags < 0) {
            float mag = sqrt(blendSource1[0]*blendSource1[0] + blendSource1[1]*blendSource1[1] + blendSource1[2]*blendSource1[2]);
            if (mag < DAT_00e44854 || mag > _DAT_00e4488c) {
                // Scale the blendSource1 matrix elements
                float scale = DAT_00e2b1a4 / (mag + (float)PTR_FUN_00e4462c);
                for (int i = 0; i < 4; i++) {
                    blendSource1[i] *= scale;
                    blendSource1[4+i] *= scale;
                    blendSource1[8+i] *= scale;
                    blendSource1[12+i] *= scale;
                }
            }
        }

        if ((flags & 0x100) == 0) {
            FUN_00417560(); // Error or fallback
            return;
        }

        // Copy matrices to output and perform final blend
        *(uint32 *)(boneWriteBase + 0x50) = *(uint32 *)&matrixA[0];
        *(uint32 *)(boneWriteBase + 0x54) = *(uint32 *)&matrixA[1];
        *(uint32 *)(boneWriteBase + 0x58) = *(uint32 *)&matrixA[2];
        *(uint32 *)(boneWriteBase + 0x5c) = *(uint32 *)&matrixA[3];
        *(uint32 *)(boneWriteBase + 0x60) = *(uint32 *)&matrixB[0];
        *(uint32 *)(boneWriteBase + 0x64) = *(uint32 *)&matrixB[1];
        *(uint32 *)(boneWriteBase + 0x68) = *(uint32 *)&matrixB[2];
        *(uint32 *)(boneWriteBase + 0x6c) = *(uint32 *)&matrixB[3];
        *(uint32 *)(boneWriteBase + 0x70) = *(uint32 *)&matrixC[0];
        *(uint32 *)(boneWriteBase + 0x74) = *(uint32 *)&matrixC[1];
        *(uint32 *)(boneWriteBase + 0x78) = *(uint32 *)&matrixC[2];
        *(uint32 *)(boneWriteBase + 0x7c) = *(uint32 *)&matrixC[3];

        uint *outData = (uint *)(boneWriteBase + 0x80);
        FUN_0056b420(&blendSource1, &translation, outData);
    }
}
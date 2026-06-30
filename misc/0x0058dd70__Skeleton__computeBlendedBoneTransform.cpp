// FUNC_NAME: Skeleton::computeBlendedBoneTransform

// Function at 0x0058dd70
// Computes the blended world transform for a bone chain starting from a given bone index.
// Parameters:
//   this (ecx) - pointer to Skeleton object
//   eax - bone index to start traversal (initially the target bone)
//   pPose - pointer to pose data containing bone flags and quaternions
//   pOutMatrix - output 4x4 matrix (16 floats)
//   pParentMatrix - parent world matrix to multiply at the end
// Returns 1 on success, 0 if a bone's flag is not 0x02.

bool skeletonComputeBlendedTransform(void* pThis, int boneIndex, void* pPose, float* pOutMatrix, float* pParentMatrix)
{
    float diagonal = DAT_00e2b1a4; // Global identity diagonal value
    int* skeletonData = *(int**)((int)pThis + 0x70); // +0x70: pointer to skeleton data

    // Validate skeleton data and bone index range
    if (skeletonData != nullptr)
    {
        int boneCount = *(int*)(skeletonData + 0x18); // +0x18: number of bones
        int boneArray = *(int*)(skeletonData + 0x1c); // +0x1c: array of bone entries (size 0x18 each)
        short parentBoneIndex = *(short*)((int)pThis + 0x74); // +0x74: parent bone index for hierarchy traversal
        short currentBoneIndex = *(short*)((int)pThis + 0x76); // +0x76: current bone index (used for restart)

        if (boneIndex != -1 && boneCount > 0 && boneArray != 0 &&
            parentBoneIndex >= 0 && parentBoneIndex < boneCount)
        {
            // Entry found: base of bone entry for this index
            int boneEntryBase = boneArray + parentBoneIndex * 0x18; // 0x18 bytes per bone entry
            int maxChildren = *(int*)(boneEntryBase + 0x8); // +0x8: max children count
            if (boneIndex < maxChildren)
            {
                // Valid child slot
                int childTable = *(int*)(boneEntryBase + 0xc); // +0xc: pointer to array of child entries (0x10 each)
                boneIndex = *(int*)(childTable + boneIndex * 0x10); // retrieve next bone index from child table
            }
            else
            {
                boneIndex = -1;
            }
        }
        else
        {
            boneIndex = -1;
        }
    }
    else
    {
        boneIndex = -1;
    }

    // Initialize output matrix to identity (only diagonal set, rest zero)
    pOutMatrix[0] = diagonal;  pOutMatrix[1] = 0.0f;  pOutMatrix[2] = 0.0f;  pOutMatrix[3] = 0.0f;
    pOutMatrix[4] = 0.0f;  pOutMatrix[5] = diagonal;  pOutMatrix[6] = 0.0f;  pOutMatrix[7] = 0.0f;
    pOutMatrix[8] = 0.0f;  pOutMatrix[9] = 0.0f;  pOutMatrix[10] = diagonal; pOutMatrix[11] = 0.0f;
    pOutMatrix[12] = 0.0f; pOutMatrix[13] = 0.0f; pOutMatrix[14] = 0.0f; pOutMatrix[15] = diagonal;

    if (skeletonData != nullptr && boneIndex != -1)
    {
        do
        {
            // Check dirty flag for this bone in the pose data
            // pose flags at pPose + 0x34 + 0x14 + boneIndex: must be 0x02 (blended/marked)
            char* flagPtr = (char*)((int)pPose + 0x34 + 0x14 + boneIndex);
            if (*flagPtr != 0x02)
            {
                return false;
            }

            // Get quaternion for this bone from pose data
            // pose bone array at pPose + 0x38, each entry size 0x20
            float* poseBone = (float*)(*(int*)((int)pPose + 0x38) + boneIndex * 0x20);
            float qx = poseBone[0x10 / 4]; // offset 0x10: x
            float qy = poseBone[0x14 / 4]; // offset 0x14: y
            float qz = poseBone[0x18 / 4]; // offset 0x18: z
            float qw = poseBone[0x1c / 4]; // offset 0x1c: w

            // Normalize quaternion
            float lenSq = qx*qx + qy*qy + qz*qz + qw*qw;
            float invLen;
            if (lenSq <= DAT_00e2cbe0) // small epsilon
            {
                invLen = 0.0f;
            }
            else
            {
                invLen = diagonal / sqrtf(lenSq);
            }
            // Write normalized quaternion back
            float* quatPtr = poseBone + 0x10 / 4; // same as poseBone[4..7]
            quatPtr[0] = qx * invLen;
            quatPtr[1] = qy * invLen;
            quatPtr[2] = qz * invLen;
            quatPtr[3] = qw * invLen;

            // Convert quaternion to rotation matrix (48 bytes = 12 floats)
            float matrixBuf[12]; // local_50
            FUN_0056cef0(quatPtr, matrixBuf); // quaternion to 3x4 matrix

            // Get translation (or additional column) from the result
            // The function likely returns pointer to matrix in ECX; we extract last column
            // The matrix is row-major? We'll copy translation components from offsets 0x10,0x14,0x18
            float tx = *(float*)((int)matrixBuf + 0x10); // +0x10: translation x
            float ty = *(float*)((int)matrixBuf + 0x14); // +0x14: translation y
            float tz = *(float*)((int)matrixBuf + 0x18); // +0x18: translation z
            float tw = diagonal; // homogeneous component

            // Build local 4x4 matrix in local_20..local_14? Actually we blend with accumulated matrix
            // The matrix from FUN_0056cef0 likely fills matrixBuf[0..8] as rotation, and [9..11] as translation
            // Then we call FUN_0048ee40() which multiplies the accumulated matrix by this local matrix
            // But the code copies local_20..local_14 from extraout_ECX+0x10 etc. Hard to infer.

            // For now, we assume the matrix multiplication happens inside FUN_0048ee40
            FUN_0048ee40(); // Multiply accumulated transform with bone's local transform

            // Update bone index for next iteration using the skeleton hierarchy
            // The parent bone index is stored at pThis+0x74
            short parentIdx = *(short*)((int)pThis + 0x74);
            if (parentIdx < 0)
            {
                boneIndex = -1;
            }
            else
            {
                int* skeletonData = *(int**)((int)pThis + 0x70);
                int boneCount = *(int*)(skeletonData + 0x18);
                int boneArray = *(int*)(skeletonData + 0x1c);
                if (parentIdx >= boneCount || boneIndex < 0)
                {
                    boneIndex = -1;
                }
                else
                {
                    int parentEntry = boneArray + parentIdx * 0x18;
                    int maxChildren = *(int*)(parentEntry + 0x8);
                    int childTable = *(int*)(parentEntry + 0xc);
                    if (boneIndex >= maxChildren)
                    {
                        boneIndex = -1;
                    }
                    else
                    {
                        boneIndex = *(int*)(childTable + boneIndex * 0x10);
                    }
                }
            }
        } while (boneIndex != -1);
    }

    // Multiply by parent world matrix
    FUN_0056d530(pOutMatrix, pParentMatrix);

    return true;
}
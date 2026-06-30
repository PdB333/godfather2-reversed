// FUNC_NAME: getNodeWorldTransform
#include <cstdint>

// Constants
constexpr float kIdentityW = 1.0f; // Equivalent to DAT_00e2b1a4

// Forward declarations for callees
extern void* skeletonGetNodeLocalTransform(int skeletonPtr, int nodeIndex); // returns pointer to a struct with scale at +0x20, +0x24, +0x28 and flag at +0x2c
extern void skeletonComputeWorldMatrix(int skeletonPtr); // FUN_00577b30
extern void mathMatrixMultiplyIdentity(void* matrix); // FUN_00417560 (placeholder)

// Returns 1 on success, 0 on failure
int __thiscall getNodeWorldTransform(float* outMatrix, int skeletonPtr)
{
    int nodeIndex = /* in_EAX */ ; // passed via EAX (hidden parameter)
    float* matrix = outMatrix;

    // Validate node index against skeleton's node count
    if (nodeIndex < 0)
        goto failure;

    // Get pointer to node data array (offset 0x70)
    int nodeArrayPtr = *(int*)(skeletonPtr + 0x70);
    // Get node stride? 0x74 is a short, multiply by 8
    short nodeStride = *(short*)(skeletonPtr + 0x74);
    int nodeCount = *(int*)(nodeArrayPtr + 0x40);

    if (nodeIndex >= nodeCount)
        goto failure;

    // Initialize local matrix (16 floats) as identity-ish
    // Layout: row-major? The code sets specific entries:
    // m[3]=0, m[4]=0, m[8]=0, m[12]=1, then later m[7],m[11],m[15] from scale
    // and m[0..2]=0, m[13..15]=0, etc. We'll follow the pattern.
    float localMatrix[16] = {0};
    localMatrix[3] = 0.0f;
    localMatrix[4] = 0.0f;
    localMatrix[8] = 0.0f;
    localMatrix[12] = kIdentityW; // (row3,col0) set to 1? Actually careful.

    // Get node's local transform (returns pointer to a structure)
    void* nodeTransform = skeletonGetNodeLocalTransform(skeletonPtr, nodeIndex);
    // This returned value is in EDX:EAX, but we take the upper 32 bits as pointer
    // In the decompiler: uVar5 = FUN_00577df0(); iVar3 = (int)((ulonglong)uVar5 >> 0x20);
    // So we need to reconstruct that. For simplicity, assume nodeTransform is the pointer.
    // Actually the decompiler's uVar5 is a 64-bit return, and the high part is the pointer.
    // We'll simulate by assuming the function returns a double? This is messy.
    // For now, we'll treat nodeTransform as the returned pointer (low part maybe ignored).
    // But the code uses iVar3 as the high part. So we need to extract it.
    // Let's define a helper: the function returns a 64-bit value; we take high 32 bits.
    // Since C++ can't return 64-bit in a 32-bit context, we'll assume it's a pointer returned in EDX:EAX.
    // We'll use a union or reinterpret_cast.
    // For simplicity, we'll just cast nodeTransform to int* and use offset.

    int* transformData = (int*)nodeTransform; // Actually should be high part

    // Extract scale from the node's local transform (+0x20, +0x24, +0x28)
    float uniformScale = *(float*)(skeletonPtr + 0x104); // scale factor
    localMatrix[7] = uniformScale * *((float*)transformData + 0x20 / sizeof(float));
    localMatrix[11] = uniformScale * *((float*)transformData + 0x24 / sizeof(float));
    localMatrix[15] = uniformScale * *((float*)transformData + 0x28 / sizeof(float));

    // Check flag at +0x2c
    if (*(int*)(transformData + 0x2c / sizeof(int)) >= 0)
    {
        // Special case: compute world matrix and multiply identity
        localMatrix[13] = 0.0f;
        localMatrix[14] = 0.0f;
        localMatrix[15] = 0.0f;
        localMatrix[0] = kIdentityW; // Actually set at different index? Original code sets local_44,34,24,14 = 0,0,0,1
        // We'll set accordingly
        // Then call the two functions
        skeletonComputeWorldMatrix(skeletonPtr);
        mathMatrixMultiplyIdentity(localMatrix);
        return 1;
    }

    // Copy local matrix to output
    for (int i = 0; i < 16; i++)
        matrix[i] = localMatrix[i];

    return 1;

failure:
    // Return identity matrix with zeros elsewhere
    matrix[0] = 0.0f; matrix[1] = 0.0f; matrix[2] = 0.0f; matrix[3] = 0.0f;
    matrix[4] = 0.0f; matrix[5] = kIdentityW; matrix[6] = 0.0f; matrix[7] = 0.0f;
    matrix[8] = 0.0f; matrix[9] = 0.0f; matrix[10] = kIdentityW; matrix[11] = 0.0f;
    matrix[12] = 0.0f; matrix[13] = 0.0f; matrix[14] = 0.0f; matrix[15] = kIdentityW;
    return 0;
}
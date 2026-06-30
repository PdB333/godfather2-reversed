// FUNC_NAME: ObjectTransform::computeWorldMatrix
void __thiscall ObjectTransform::computeWorldMatrix(int slotIndex, const float3x4& parentTransform, float interpolant, const float3& localPosition) {
    // +0x154: m_flags - if zero, use global transform context from TLS
    // +0x14: m_transformSlots[slotIndex] - pointer to output world matrix (4x4)
    float3x4* destMatrix; // puVar3

    // Select destination matrix: either from this or from global TLS
    if (m_flags == 0) {
        // Get global matrix pointer from TLS (FS segment at offset 0x2c)
        int* fsBase = __readfsdword(0x2c);
        destMatrix = (float3x4*)(*(int*)(*fsBase + 0x24));
    } else {
        // Use per-instance slot pointer array
        destMatrix = m_transformSlots[slotIndex];
    }

    // If no interpolant specified, use default from global constant
    if (interpolant <= 0.0f) {
        interpolant = DAT_00e2e704;  // default blend factor
    }

    // Build a temporary matrix from local transform data (position, rotation, scale)
    // In the original, this data was passed via EAX: localPosition.x,y,z
    Matrix4x4 tempMatrix; // local_90
    FUN_0056b8a0(localPosition.y, localPosition.x, localPosition.z, &tempMatrix);

    // Copy parent transform into another temporary matrix, with last element fixed
    Matrix4x4 parentCopy; // local_60
    parentCopy = parentTransform;
    parentCopy.m[3][3] = DAT_00e2b1a4; // constant for homogeneous coordinate

    // Multiply? (FUN_00424470 likely does a matrix combination)
    FUN_00424470(); // side effect on tempMatrix/parentCopy?

    // Copy the first temporary into the destination (offset 0x10..0x1f = third row+?)
    destMatrix->m[4] = tempMatrix.m[0];
    destMatrix->m[5] = tempMatrix.m[1];
    destMatrix->m[6] = tempMatrix.m[2];
    destMatrix->m[7] = tempMatrix.m[3];
    // ... continue for all 16 floats (index 0x10..0x1f)
    // (The decompiler shows assignment of 16 floats from local_90 to puVar3[0x10..0x1f])

    // Second matrix operation (likely interpolation or blending)
    FUN_00423900();  // some reset or compute
    int flag = *(int*)(*fsBase + 0x34); // global flag for second block
    if (flag == 0) {
        FUN_00422c50(destMatrix, &tempMatrix, 0);  // store with flag
    }

    // Another 16-float copy (local_50) to destination (offset 0x0..0xf)
    destMatrix->m[0] = local_50.m[0];
    // ... etc.

    FUN_00423900(); // again
    if (flag == 0) {
        FUN_00422ad0(destMatrix, &local_50, 0); // store second block
    }

    // Finalize with blend factor and global parameter
    FUN_00422fb0(interpolant, DAT_01205878);  // possibly interpolation finalizer
}
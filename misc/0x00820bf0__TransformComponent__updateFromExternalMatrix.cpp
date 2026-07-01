// FUNC_NAME: TransformComponent::updateFromExternalMatrix
void __thiscall TransformComponent::updateFromExternalMatrix(int thisPtr) {
    float* outMatrix;
    float* srcMatrix;
    float fVar3, fVar4, fVar5, fVar6;
    float baseValue = _DAT_00d5780c; // likely 1.0f or 0.0f, used as initializer

    // +0xB0 appears to be a flag indicating whether the transform is driven by external data
    if (*(int*)(thisPtr + 0xB0) == 0) {
        // No external source: zero out matrix and set quaternion to identity?
        *(float*)(thisPtr + 0xC0) = baseValue; // m00
        *(int*)(thisPtr + 0xC4) = 0;            // m01
        *(int*)(thisPtr + 200) = 0;             // m02 (offset 0xC8)
        *(int*)(thisPtr + 0xCC) = 0;            // m03
        *(int*)(thisPtr + 0xD0) = 0;            // m10
        *(float*)(thisPtr + 0xD4) = baseValue; // m11
        *(int*)(thisPtr + 0xD8) = 0;            // m12
        *(int*)(thisPtr + 0xDC) = 0;            // m13
        *(int*)(thisPtr + 0xE0) = 0;            // m20
        *(int*)(thisPtr + 0xE4) = 0;            // m21
        *(float*)(thisPtr + 0xE8) = baseValue; // m22
        *(int*)(thisPtr + 0xEC) = 0;            // m23
        *(float*)(thisPtr + 0xF0) = 0;          // m30 (presumably translation x)
        *(float*)(thisPtr + 0xF4) = 0;          // translation y
        *(float*)(thisPtr + 0xF8) = 0;          // translation z
        *(float*)(thisPtr + 0xFC) = baseValue; // m33 (scale factor?)
        fVar3 = 0.0f;
        fVar5 = 0.0f;
        fVar6 = 0.0f;
    } else {
        // External matrix source (e.g., physics or animation)
        srcMatrix = (float*)FUN_004aaa50(); // returns pointer to a 4x4 matrix (16 floats)
        // Copy matrix row by row (row-major order)
        *(float*)(thisPtr + 0xC0) = srcMatrix[0];  // m00
        *(float*)(thisPtr + 0xC4) = srcMatrix[1];  // m01
        *(float*)(thisPtr + 200) = srcMatrix[2];   // m02 (offset 0xC8)
        *(float*)(thisPtr + 0xCC) = srcMatrix[3];  // m03
        *(float*)(thisPtr + 0xD0) = srcMatrix[4];  // m10
        *(float*)(thisPtr + 0xD4) = srcMatrix[5];  // m11
        *(float*)(thisPtr + 0xD8) = srcMatrix[6];  // m12
        *(float*)(thisPtr + 0xDC) = srcMatrix[7];  // m13
        *(float*)(thisPtr + 0xE0) = srcMatrix[8];  // m20
        *(float*)(thisPtr + 0xE4) = srcMatrix[9];  // m21
        *(float*)(thisPtr + 0xE8) = srcMatrix[10]; // m22
        *(float*)(thisPtr + 0xEC) = srcMatrix[11]; // m23
        *(float*)(thisPtr + 0xF0) = srcMatrix[12]; // m30 (translation x)
        *(float*)(thisPtr + 0xF4) = srcMatrix[13]; // translation y
        *(float*)(thisPtr + 0xF8) = srcMatrix[14]; // translation z
        *(float*)(thisPtr + 0xFC) = srcMatrix[15]; // m33
        fVar3 = srcMatrix[12]; // translation x (redundantly stored)
        fVar5 = srcMatrix[13]; // translation y
        fVar6 = srcMatrix[14]; // translation z
        fVar4 = srcMatrix[15]; // m33
    }

    // Complete the last row (translation) stored at +0xF0..0xFC
    *(float*)(thisPtr + 0xF0) = fVar3;
    *(float*)(thisPtr + 0xF4) = fVar5;
    *(float*)(thisPtr + 0xF8) = fVar6;
    *(float*)(thisPtr + 0xFC) = fVar4;

    // Convert matrix at +0xC0 to quaternion at +0x100
    outMatrix = (float*)(thisPtr + 0xC0);
    float* quat = (float*)(thisPtr + 0x100);
    FUN_0056dbe0(outMatrix, quat); // matrix -> quaternion

    // Normalize quaternion if squared length is too large
    float sqLen = quat[0]*quat[0] + quat[1]*quat[1] + quat[2]*quat[2] + quat[3]*quat[3];
    // The global DAT_00e44768 and DAT_00e44680 form a threshold comparison (likely epsilon for near-incompressible)
    // This reduces to: if (sqLen > (1.0f - epsilon)) but with bit manipulation trick
    if (DAT_00e44768 < (double)((uint)(sqLen - baseValue) & DAT_00e44680)) {
        float invLen = baseValue / sqrtf(sqLen);
        quat[0] *= invLen;
        quat[1] *= invLen;
        quat[2] *= invLen;
        quat[3] *= invLen;
    }
}
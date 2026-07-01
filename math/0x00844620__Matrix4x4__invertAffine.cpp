// FUNC_NAME: Matrix4x4::invertAffine
void __fastcall Matrix4x4::invertAffine(float *outMatrix, float *inMatrix)
{
    float fVar1;
    float fVar2;
    float fVar3;
    float fVar4;
    float fVar5;
    float fVar6;
    float fVar7;
    float fVar8;
    float fVar9;
    float fVar10;
    float fVar11;
    float fVar12;
    float fVar13;
    float fVar14;
    float fVar15;
    float fVar16;
    float fVar17;

    // Extract rotation/scale columns (row-major: columns 0,1,2 are rotation/scale, column 3 is translation)
    fVar1 = inMatrix[0xc]; // +0x30: translation.x
    fVar2 = inMatrix[0xd]; // +0x34: translation.y
    fVar3 = inMatrix[0xe]; // +0x38: translation.z
    fVar4 = inMatrix[0xf]; // +0x3C: translation.w (usually 1.0)

    fVar5 = inMatrix[0];   // +0x00: column0.x
    fVar6 = inMatrix[1];   // +0x04: column0.y
    fVar7 = inMatrix[2];   // +0x08: column0.z
    fVar8 = inMatrix[8];   // +0x20: column2.x
    fVar9 = inMatrix[9];   // +0x24: column2.y
    fVar10 = inMatrix[10]; // +0x28: column2.z
    fVar11 = inMatrix[4];  // +0x10: column1.x
    fVar12 = inMatrix[5];  // +0x14: column1.y
    fVar13 = inMatrix[6];  // +0x18: column1.z

    // Zero out translation components for inverse rotation
    fVar15 = fVar1 - fVar1; // 0.0
    fVar16 = fVar2 - fVar2; // 0.0
    fVar17 = fVar3 - fVar3; // 0.0

    // Write transposed rotation matrix (inverse of orthogonal rotation)
    outMatrix[0] = fVar5;   // +0x00: column0.x = original column0.x
    outMatrix[1] = fVar11;  // +0x04: column0.y = original column1.x
    outMatrix[2] = fVar8;   // +0x08: column0.z = original column2.x
    outMatrix[3] = fVar15;  // +0x0C: column0.w = 0

    outMatrix[4] = fVar6;   // +0x10: column1.x = original column0.y
    outMatrix[5] = fVar12;  // +0x14: column1.y = original column1.y
    outMatrix[6] = fVar9;   // +0x18: column1.z = original column2.y
    outMatrix[7] = fVar16;  // +0x1C: column1.w = 0

    fVar14 = _DAT_00d5780c; // Global constant (likely 1.0 or similar)
    outMatrix[8] = fVar7;   // +0x20: column2.x = original column0.z
    outMatrix[9] = fVar13;  // +0x24: column2.y = original column1.z
    outMatrix[10] = fVar10; // +0x28: column2.z = original column2.z
    outMatrix[0xb] = fVar17; // +0x2C: column2.w = 0

    // Compute inverse translation: -R^T * t
    outMatrix[0xc] = fVar15 - (fVar2 * fVar6 + fVar1 * fVar5 + fVar3 * fVar7);   // +0x30: translation.x
    outMatrix[0xd] = fVar16 - (fVar2 * fVar12 + fVar1 * fVar11 + fVar3 * fVar13); // +0x34: translation.y
    outMatrix[0xe] = fVar17 - (fVar2 * fVar9 + fVar1 * fVar8 + fVar3 * fVar10);   // +0x38: translation.z
    outMatrix[0xf] = (fVar4 - fVar4) - (fVar2 * fVar16 + fVar1 * fVar15 + fVar3 * fVar17); // +0x3C: translation.w (should be 1.0)
    outMatrix[0xf] = fVar14; // Overwrite with global constant (likely 1.0)
}
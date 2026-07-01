// FUNC_NAME: Matrix4x4::invertAffine
void __fastcall Matrix4x4::invertAffine(float *this)
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
    float *outMatrix;
    float fVar15;
    float fVar16;
    float fVar17;

    // Extract rotation matrix columns (row-major, 3x3)
    fVar1 = this[0xc]; // +0x30: rotation[0][0] (column 0, row 0)
    fVar2 = this[0xd]; // +0x34: rotation[0][1] (column 0, row 1)
    fVar3 = this[0xe]; // +0x38: rotation[0][2] (column 0, row 2)
    fVar4 = this[0xf]; // +0x3C: translation[3] (w component, usually 1.0)

    fVar5 = this[0];   // +0x00: rotation[0][0] (column 0, row 0)
    fVar6 = this[1];   // +0x04: rotation[0][1] (column 0, row 1)
    fVar7 = this[2];   // +0x08: rotation[0][2] (column 0, row 2)
    fVar8 = this[8];   // +0x20: rotation[2][0] (column 2, row 0)
    fVar9 = this[9];   // +0x24: rotation[2][1] (column 2, row 1)
    fVar10 = this[10]; // +0x28: rotation[2][2] (column 2, row 2)
    fVar11 = this[4];  // +0x10: rotation[1][0] (column 1, row 0)
    fVar12 = this[5];  // +0x14: rotation[1][1] (column 1, row 1)
    fVar13 = this[6];  // +0x18: rotation[1][2] (column 1, row 2)

    // Compute translation components (negated dot products with rotation rows)
    fVar15 = fVar1 - fVar1; // 0.0
    fVar16 = fVar2 - fVar2; // 0.0
    fVar17 = fVar3 - fVar3; // 0.0

    // Transpose rotation matrix into output
    outMatrix[0] = fVar5;   // rotation[0][0]
    outMatrix[1] = fVar11;  // rotation[1][0]
    outMatrix[2] = fVar8;   // rotation[2][0]
    outMatrix[3] = fVar15;  // 0.0

    outMatrix[4] = fVar6;   // rotation[0][1]
    outMatrix[5] = fVar12;  // rotation[1][1]
    outMatrix[6] = fVar9;   // rotation[2][1]
    outMatrix[7] = fVar16;  // 0.0

    fVar14 = _DAT_00d5780c; // Global constant (likely 1.0 or identity w)
    outMatrix[8] = fVar7;   // rotation[0][2]
    outMatrix[9] = fVar13;  // rotation[1][2]
    outMatrix[10] = fVar10; // rotation[2][2]
    outMatrix[0xb] = fVar17; // 0.0

    // Compute translation: -R^T * t
    outMatrix[0xc] = fVar15 - (fVar2 * fVar6 + fVar1 * fVar5 + fVar3 * fVar7);   // -dot(row0, translation)
    outMatrix[0xd] = fVar16 - (fVar2 * fVar12 + fVar1 * fVar11 + fVar3 * fVar13); // -dot(row1, translation)
    outMatrix[0xe] = fVar17 - (fVar2 * fVar9 + fVar1 * fVar8 + fVar3 * fVar10);   // -dot(row2, translation)
    outMatrix[0xf] = (fVar4 - fVar4) - (fVar2 * fVar16 + fVar1 * fVar15 + fVar3 * fVar17); // 0.0 - 0.0 = 0.0
    outMatrix[0xf] = fVar14; // Set w component to global constant (likely 1.0)
    return;
}
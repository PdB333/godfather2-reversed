// FUNC_NAME: Matrix4x4::invertAffine
void __fastcall Matrix4x4::invertAffine(float *thisMatrix)
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

    // Load rotation/scale columns (columns 0,1,2) and translation (column 3)
    fVar1 = thisMatrix[0xc]; // m[3][0] (translation x)
    fVar2 = thisMatrix[0xd]; // m[3][1] (translation y)
    fVar3 = thisMatrix[0xe]; // m[3][2] (translation z)
    fVar4 = thisMatrix[0xf]; // m[3][3] (homogeneous coordinate, usually 1.0)
    
    fVar5 = thisMatrix[0];   // m[0][0]
    fVar6 = thisMatrix[1];   // m[0][1]
    fVar7 = thisMatrix[2];   // m[0][2]
    fVar8 = thisMatrix[8];   // m[2][0]
    fVar9 = thisMatrix[9];   // m[2][1]
    fVar10 = thisMatrix[10]; // m[2][2]
    fVar11 = thisMatrix[4];  // m[1][0]
    fVar12 = thisMatrix[5];  // m[1][1]
    fVar13 = thisMatrix[6];  // m[1][2]

    // Compute zeros for the inverse's translation row (row 3)
    fVar15 = fVar1 - fVar1;  // 0.0
    fVar16 = fVar2 - fVar2;  // 0.0
    fVar17 = fVar3 - fVar3;  // 0.0

    // Transpose the 3x3 rotation/scale part into output matrix
    outMatrix[0] = fVar5;    // out[0][0] = m[0][0]
    outMatrix[1] = fVar11;   // out[0][1] = m[1][0]
    outMatrix[2] = fVar8;    // out[0][2] = m[2][0]
    outMatrix[3] = fVar15;   // out[0][3] = 0.0

    outMatrix[4] = fVar6;    // out[1][0] = m[0][1]
    outMatrix[5] = fVar12;   // out[1][1] = m[1][1]
    outMatrix[6] = fVar9;    // out[1][2] = m[2][1]
    outMatrix[7] = fVar16;   // out[1][3] = 0.0

    outMatrix[8] = fVar7;    // out[2][0] = m[0][2]
    outMatrix[9] = fVar13;   // out[2][1] = m[1][2]
    outMatrix[10] = fVar10;  // out[2][2] = m[2][2]
    outMatrix[0xb] = fVar17; // out[2][3] = 0.0

    // Compute new translation: -transposedRotation * originalTranslation
    outMatrix[0xc] = fVar15 - (fVar2 * fVar6 + fVar1 * fVar5 + fVar3 * fVar7);
    outMatrix[0xd] = fVar16 - (fVar2 * fVar12 + fVar1 * fVar11 + fVar3 * fVar13);
    outMatrix[0xe] = fVar17 - (fVar2 * fVar9 + fVar1 * fVar8 + fVar3 * fVar10);

    // Set homogeneous coordinate (usually 1.0, but overridden by global)
    outMatrix[0xf] = (fVar4 - fVar4) - (fVar2 * fVar16 + fVar1 * fVar15 + fVar3 * fVar17);
    outMatrix[0xf] = _DAT_00d5780c; // Global constant (likely 1.0)
}
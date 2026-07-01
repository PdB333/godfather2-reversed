// FUNC_NAME: Matrix4x4::invertAffine
void __fastcall Matrix4x4::invertAffine(float *outMatrix, float *inMatrix)
{
    float fVar1, fVar2, fVar3, fVar4, fVar5, fVar6, fVar7, fVar8, fVar9, fVar10;
    float fVar11, fVar12, fVar13, fVar14, fVar15, fVar16, fVar17;
    float *in_EAX;
    float fVar18, fVar19, fVar20;

    // Load rotation/scale columns from input matrix (row-major, 4x4)
    fVar1 = inMatrix[0xc]; // +0x30: row 3, col 0 (translation x)
    fVar2 = inMatrix[0xd]; // +0x34: row 3, col 1 (translation y)
    fVar3 = inMatrix[0xe]; // +0x38: row 3, col 2 (translation z)
    fVar4 = inMatrix[0xf]; // +0x3c: row 3, col 3 (homogeneous w, usually 1.0)

    fVar5 = inMatrix[0];  // +0x00: row 0, col 0
    fVar6 = inMatrix[1];  // +0x04: row 0, col 1
    fVar7 = inMatrix[2];  // +0x08: row 0, col 2
    fVar8 = inMatrix[8];  // +0x20: row 2, col 0
    fVar9 = inMatrix[9];  // +0x24: row 2, col 1
    fVar10 = inMatrix[10]; // +0x28: row 2, col 2
    fVar11 = inMatrix[4]; // +0x10: row 1, col 0
    fVar12 = inMatrix[5]; // +0x14: row 1, col 1
    fVar13 = inMatrix[6]; // +0x18: row 1, col 2

    // Compute zero vectors for translation negation
    fVar15 = fVar1 - fVar1; // 0.0
    fVar16 = fVar2 - fVar2; // 0.0
    fVar17 = fVar3 - fVar3; // 0.0

    // Transpose the upper-left 3x3 rotation/scale matrix into output
    outMatrix[0] = fVar5;   // row 0, col 0 = original (0,0)
    outMatrix[1] = fVar11;  // row 0, col 1 = original (1,0)
    outMatrix[2] = fVar8;   // row 0, col 2 = original (2,0)
    outMatrix[3] = fVar15;  // row 0, col 3 = 0.0

    outMatrix[4] = fVar6;   // row 1, col 0 = original (0,1)
    outMatrix[5] = fVar12;  // row 1, col 1 = original (1,1)
    outMatrix[6] = fVar9;   // row 1, col 2 = original (2,1)
    outMatrix[7] = fVar16;  // row 1, col 3 = 0.0

    outMatrix[8] = fVar7;   // row 2, col 0 = original (0,2)
    outMatrix[9] = fVar13;  // row 2, col 1 = original (1,2)
    outMatrix[10] = fVar10; // row 2, col 2 = original (2,2)
    outMatrix[0xb] = fVar17; // row 2, col 3 = 0.0

    // Compute negated translation: -translation * transposed rotation
    outMatrix[0xc] = fVar15 - (fVar2 * fVar6 + fVar1 * fVar5 + fVar3 * fVar7);
    outMatrix[0xd] = fVar16 - (fVar2 * fVar12 + fVar1 * fVar11 + fVar3 * fVar13);
    outMatrix[0xe] = fVar17 - (fVar2 * fVar9 + fVar1 * fVar8 + fVar3 * fVar10);
    outMatrix[0xf] = (fVar4 - fVar4) - (fVar2 * fVar16 + fVar1 * fVar15 + fVar3 * fVar17);

    // Overwrite last element with global value (likely identity w = 1.0)
    outMatrix[0xf] = _DAT_00d5780c; // +0x3c: homogeneous w component
    return;
}
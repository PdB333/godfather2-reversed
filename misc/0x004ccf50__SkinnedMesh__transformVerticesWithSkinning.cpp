// FUNC_NAME: SkinnedMesh::transformVerticesWithSkinning
void __thiscall SkinnedMesh::transformVerticesWithSkinning(
    int vertexData,          // +0x00: pointer to vertex data (stride 0x20)
    int vertexCount,         // number of vertices to process
    int boneMatrixArray,     // array of 4x4 bone matrices (each 0x40 bytes)
    int unusedLoop,          // unused loop counter (debug?)
    int outputBuffer,        // output vertex buffer (stride 0x14)
    float* outMin,           // output minimum bounding box (4 floats)
    float* outMax)           // output maximum bounding box (4 floats)
{
    float* pfVar1;
    float* pfVar2;
    ulonglong uVar3;
    float fVar7, fVar8, fVar9, fVar10;
    float fVar17, fVar19, fVar21, fVar22;
    float fVar23, fVar27, fVar28, fVar29, fVar30, fVar31, fVar32;
    float fVar35, fVar36, fVar37, fVar38, fVar39, fVar40;
    float fVar43, fVar44, fVar45, fVar46, fVar47, fVar48, fVar49, fVar50, fVar51;
    uint uVar11;
    float* pfVar12;
    int iVar13;
    float* pfVar14;
    int iVar15;
    undefined8 in_MM0, in_MM1;
    ushort uVar20;
    undefined1 auVar4[12], auVar5[14], auVar6[14];
    undefined1 auVar18[16], auVar24[16], auVar25[16], auVar26[16];
    undefined1 auVar33[16], auVar34[16], auVar41[16], auVar42[16];
    undefined1 auVar52[16], auVar53[16];
    undefined8* outputPtr;
    int remainingVertices;
    undefined1 local_90[16], local_70[16]; // min/max accumulators

    remainingVertices = vertexCount;

    // Unused loop (likely debug or alignment)
    if (unusedLoop != 0) {
        do {
            unusedLoop = unusedLoop - 1;
        } while (unusedLoop != 0);
    }

    // Initialize min/max from global constants (likely +inf / -inf)
    // These globals are at 0x00e36910-0x00e3691c and 0x00e36920-0x00e3692c
    local_70._4_4_ = _UNK_00e36914;
    local_70._0_4_ = _DAT_00e36910;
    local_70._8_4_ = _UNK_00e36918;
    local_70._12_4_ = _UNK_00e3691c;
    local_90._4_4_ = _UNK_00e36924;
    local_90._0_4_ = _DAT_00e36920;
    local_90._8_4_ = _UNK_00e36928;
    local_90._12_4_ = _UNK_00e3692c;

    // Alignment loop (does nothing)
    uVar11 = 0;
    do {
        uVar11 = uVar11 + 0x40;
    } while (uVar11 < 0x200);

    // Output pointer starts at outputBuffer + 0xc
    outputPtr = (undefined8*)(outputBuffer + 0xc);

    // Advance vertex data pointer by 0x200 (512 bytes) – likely to skip header?
    vertexData = vertexData + 0x200;

    do {
        // Read vertex data from current position (relative to vertexData)
        // Position (3 floats) at offsets -0x200, -0x1fc, -0x1f8
        fVar32 = *(float*)(vertexData + -0x200);   // x
        fVar37 = *(float*)(vertexData + -0x1fc);   // y
        fVar51 = *(float*)(vertexData + -0x1f8);   // z

        // Read packed bone weights (64-bit at offset -0x1e8 = +0x18 from base)
        uVar3 = *(ulonglong*)(vertexData + -0x1e8);
        uVar20 = (ushort)(uVar3 >> 0x30);          // weight4 (high 16 bits)

        // Decompose weights into 4 half-floats (16-bit unsigned)
        auVar5._8_4_ = 0;
        auVar5._0_8_ = uVar3;
        auVar5._12_2_ = uVar20;
        auVar6._8_2_ = (short)(uVar3 >> 0x20);
        auVar6._0_8_ = uVar3;
        auVar6._10_4_ = auVar5._10_4_;
        auVar4._2_10_ = (unkuint10)auVar6._8_6_ << 0x10;
        auVar4._0_2_ = (short)(uVar3 >> 0x10);

        // Convert weights to floats using global scale factors
        fVar17 = (float)(ushort)uVar3 * _DAT_00e368e0;          // weight1
        fVar19 = (float)auVar4._0_4_ * _UNK_00e368e4;          // weight2
        fVar21 = (float)auVar6._8_4_ * _UNK_00e368e8;          // weight3
        fVar22 = (float)uVar20 * _UNK_00e368ec;                // weight4

        // Read packed normal/tangent (64-bit at offset -500 = +0x0c from base)
        uVar11 = (uint)((ulonglong)*(undefined8*)(vertexData + -500) >> 0x20);
        fVar43 = (float)(uVar11 & _UNK_00e36934 | _UNK_00e368d4); // normal component?
        iVar15 = (int)*(undefined8*)(vertexData + -500);

        // Extract normal components from packed data (bit shifts)
        fVar30 = (float)((iVar15 << 2) >> 0x16) * _DAT_00e368f0;
        fVar35 = (float)((int)(uVar11 << 2) >> 0x16) * _UNK_00e368f4;
        fVar23 = (float)((iVar15 << 0x16) >> 0x16) * _DAT_00e368f0;
        fVar27 = (float)((int)(uVar11 << 0x16) >> 0x16) * _UNK_00e368f4;
        fVar28 = (float)((iVar15 << 0xc) >> 0x16) * _UNK_00e368f8;
        fVar29 = (float)((int)(uVar11 << 0xc) >> 0x16) * _UNK_00e368fc;

        // Read bone indices (4 bytes at offsets -0x1eb, -0x1ec, -0x1ea, -0x1e9)
        // Each index is multiplied by 0x40 (64 bytes) to get bone matrix offset
        pfVar12 = (float*)((uint)*(byte*)(vertexData + -0x1eb) * 0x40 + boneMatrixArray);
        iVar13 = (uint)*(byte*)(vertexData + -0x1ec) * 0x40;
        pfVar1 = (float*)(iVar13 + boneMatrixArray);
        iVar13 = iVar13 + boneMatrixArray;
        pfVar14 = (float*)((uint)*(byte*)(vertexData + -0x1ea) * 0x40 + boneMatrixArray);
        iVar15 = (uint)*(byte*)(vertexData + -0x1e9) * 0x40;
        pfVar2 = (float*)(iVar15 + boneMatrixArray);
        iVar15 = iVar15 + boneMatrixArray;

        // Compute weighted sum of bone matrix columns for position
        // Each bone matrix is 16 floats (4x4), accessed as columns
        fVar31 = *pfVar1 * fVar17 + *pfVar12 * fVar19 + *pfVar14 * fVar21 + *pfVar2 * fVar22;
        fVar36 = pfVar1[1] * fVar17 + pfVar12[1] * fVar19 + pfVar14[1] * fVar21 + pfVar2[1] * fVar22;
        fVar38 = pfVar1[2] * fVar17 + pfVar12[2] * fVar19 + pfVar14[2] * fVar21 + pfVar2[2] * fVar22;
        fVar39 = pfVar1[3] * fVar17 + pfVar12[3] * fVar19 + pfVar14[3] * fVar21 + pfVar2[3] * fVar22;

        fVar40 = pfVar12[4] * fVar19 + *(float*)(iVar13 + 0x10) * fVar17 + pfVar14[4] * fVar21 + *(float*)(iVar15 + 0x10) * fVar22;
        fVar44 = pfVar12[5] * fVar19 + *(float*)(iVar13 + 0x14) * fVar17 + pfVar14[5] * fVar21 + *(float*)(iVar15 + 0x14) * fVar22;
        fVar45 = pfVar12[6] * fVar19 + *(float*)(iVar13 + 0x18) * fVar17 + pfVar14[6] * fVar21 + *(float*)(iVar15 + 0x18) * fVar22;
        fVar46 = pfVar12[7] * fVar19 + *(float*)(iVar13 + 0x1c) * fVar17 + pfVar14[7] * fVar21 + *(float*)(iVar15 + 0x1c) * fVar22;

        fVar47 = pfVar12[8] * fVar19 + *(float*)(iVar13 + 0x20) * fVar17 + pfVar14[8] * fVar21 + *(float*)(iVar15 + 0x20) * fVar22;
        fVar48 = pfVar12[9] * fVar19 + *(float*)(iVar13 + 0x24) * fVar17 + pfVar14[9] * fVar21 + *(float*)(iVar15 + 0x24) * fVar22;
        fVar49 = pfVar12[10] * fVar19 + *(float*)(iVar13 + 0x28) * fVar17 + pfVar14[10] * fVar21 + *(float*)(iVar15 + 0x28) * fVar22;
        fVar50 = pfVar12[0xb] * fVar19 + *(float*)(iVar13 + 0x2c) * fVar17 + pfVar14[0xb] * fVar21 + *(float*)(iVar15 + 0x2c) * fVar22;

        // Combine weighted bone matrix columns with original position to get transformed position
        auVar18._0_8_ = CONCAT44(
            pfVar12[0xd] * fVar19 + *(float*)(iVar13 + 0x34) * fVar17 + pfVar14[0xd] * fVar21 + *(float*)(iVar15 + 0x34) * fVar22 +
            fVar37 * fVar44 + fVar32 * fVar36 + fVar51 * fVar48,
            pfVar12[0xc] * fVar19 + *(float*)(iVar13 + 0x30) * fVar17 + pfVar14[0xc] * fVar21 + *(float*)(iVar15 + 0x30) * fVar22 +
            fVar37 * fVar40 + fVar32 * fVar31 + fVar51 * fVar47);
        auVar18._8_4_ = pfVar12[0xe] * fVar19 + *(float*)(iVar13 + 0x38) * fVar17 + pfVar14[0xe] * fVar21 + *(float*)(iVar15 + 0x38) * fVar22 +
                        fVar37 * fVar45 + fVar32 * fVar38 + fVar51 * fVar49;
        auVar18._12_4_ = pfVar12[0xf] * fVar19 + *(float*)(iVar13 + 0x3c) * fVar17 + pfVar14[0xf] * fVar21 + *(float*)(iVar15 + 0x3c) * fVar22 +
                         fVar37 * fVar46 + fVar32 * fVar39 + fVar51 * fVar50;

        // Update min/max using SSE minps/maxps
        auVar52._8_4_ = auVar18._8_4_;
        auVar52._0_8_ = auVar18._0_8_;
        auVar52._12_4_ = auVar18._12_4_;
        local_70 = minps(auVar52, local_70);
        auVar53._8_4_ = auVar18._8_4_;
        auVar53._0_8_ = auVar18._0_8_;
        auVar53._12_4_ = auVar18._12_4_;
        local_90 = maxps(auVar53, local_90);

        // Compute transformed normal using same bone matrices but with normal components
        fVar51 = fVar28 * fVar40 + fVar23 * fVar31 + fVar30 * fVar47;
        fVar17 = fVar28 * fVar44 + fVar23 * fVar36 + fVar30 * fVar48;
        fVar19 = fVar28 * fVar45 + fVar23 * fVar38 + fVar30 * fVar49;
        fVar21 = fVar29 * fVar40 + fVar27 * fVar31 + fVar35 * fVar47;
        fVar22 = fVar29 * fVar44 + fVar27 * fVar36 + fVar35 * fVar48;
        fVar27 = fVar29 * fVar45 + fVar27 * fVar38 + fVar35 * fVar49;

        // Normalize normal (using rsqrtps)
        fVar32 = fVar21 * fVar21;
        fVar37 = fVar22 * fVar22;
        auVar33._8_4_ = fVar27 * fVar27;
        auVar33._4_4_ = auVar33._8_4_;
        auVar33._0_4_ = auVar33._8_4_;
        auVar33._12_4_ = auVar33._8_4_;
        auVar41._0_4_ = fVar37 + fVar32 + auVar33._8_4_;
        auVar41._4_4_ = fVar37 + fVar32 + auVar33._8_4_;
        auVar41._8_4_ = fVar37 + fVar32 + auVar33._8_4_;
        auVar41._12_4_ = fVar37 + fVar32 + auVar33._8_4_;
        auVar33 = rsqrtps(auVar33, auVar41);

        fVar32 = fVar51 * fVar51;
        fVar37 = fVar17 * fVar17;
        auVar24._8_4_ = fVar19 * fVar19;
        auVar24._4_4_ = auVar24._8_4_;
        auVar24._0_4_ = auVar24._8_4_;
        auVar24._12_4_ = auVar24._8_4_;
        auVar42._0_4_ = fVar37 + fVar32 + auVar24._8_4_;
        auVar42._4_4_ = fVar37 + fVar32 + auVar24._8_4_;
        auVar42._8_4_ = fVar37 + fVar32 + auVar24._8_4_;
        auVar42._12_4_ = fVar37 + fVar32 + auVar24._8_4_;
        auVar25 = rsqrtps(auVar24, auVar42);

        // Pack transformed position and normal into 16-bit integers (for GPU)
        auVar26._0_4_ = (int)(auVar25._0_4_ * fVar51 * _DAT_00e36900 + _DAT_00e36900);
        auVar26._4_4_ = (int)(auVar25._4_4_ * fVar17 * _UNK_00e36904 + _UNK_00e36904);
        auVar26._8_4_ = (int)(auVar25._8_4_ * fVar19 * _UNK_00e36908 + _UNK_00e36908);
        auVar26._12_4_ = (int)(auVar25._12_4_ * (fVar28 * fVar46 + fVar23 * fVar39 + fVar30 * fVar50) * _UNK_00e3690c + _UNK_00e3690c);

        // Store transformed position (first 8 bytes) to output
        uVar16 = movdq2q(in_MM0, auVar18);
        *(undefined8*)((int)outputPtr + -0xc) = uVar16;

        // Pack normal components
        auVar34._0_4_ = (int)(auVar33._0_4_ * fVar21 * fVar7 + fVar7);
        auVar34._4_4_ = (int)(auVar33._4_4_ * fVar22 * fVar8 + fVar8);
        auVar34._8_4_ = (int)(auVar33._8_4_ * fVar27 * fVar9 + fVar9);
        auVar34._12_4_ = (int)(fVar43 * fVar10 + fVar10);

        // Pack both into 16-bit shorts using packssdw
        auVar25._8_8_ = auVar18._8_8_;
        auVar25._0_8_ = auVar25._8_8_;
        in_MM0 = movdq2q(uVar16, auVar25);
        packssdw(auVar26, auVar34);

        // Store remaining output (4 bytes at offset 8, 8 bytes at offset 0xc)
        *(int*)((int)outputPtr + -4) = (int)in_MM0;
        in_MM1 = movdq2q(in_MM1, auVar25);
        *outputPtr = in_MM0;

        // Advance pointers
        outputPtr = (undefined8*)((int)outputPtr + 0x14);
        vertexData = vertexData + 0x20;
        remainingVertices = remainingVertices - 1;
    } while (remainingVertices != 0);

    // Output bounding box min/max
    *outMin = local_70._0_4_;
    outMin[1] = local_70._4_4_;
    outMin[2] = local_70._8_4_;
    outMin[3] = local_70._12_4_;
    *outMax = local_90._0_4_;
    outMax[1] = local_90._4_4_;
    outMax[2] = local_90._8_4_;
    outMax[3] = local_90._12_4_;
}
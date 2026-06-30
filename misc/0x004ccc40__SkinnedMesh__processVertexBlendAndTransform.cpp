// FUNC_NAME: SkinnedMesh::processVertexBlendAndTransform
void SkinnedMesh::processVertexBlendAndTransform(int vertexCount, int vertexStride, float* boneMatrices, int blendIndices, float* blendWeights, float* outMinBounds, float* outMaxBounds)
{
    float* pfVar1;
    float* pfVar2;
    ulonglong uVar3;
    float fVar7, fVar8, fVar9, fVar10;
    float fVar18, fVar20, fVar21, fVar22, fVar26, fVar27, fVar28, fVar30, fVar31, fVar32, fVar36, fVar37, fVar38, fVar39, fVar40, fVar41;
    float fVar45, fVar46, fVar47, fVar48, fVar49, fVar50, fVar51, fVar52, fVar53;
    uint uVar11;
    int iVar12, iVar13, iVar29;
    float* pfVar14, * pfVar15;
    undefined8* puVar16;
    undefined8 in_MM0, in_MM1, uVar17;
    
    // Constants loaded from global data
    // +0x00e368a0: min bounds accumulator (initialized to large positive)
    // +0x00e368b0: max bounds accumulator (initialized to large negative)
    float minBounds[4] = { _DAT_00e368a0, _UNK_00e368a4, _UNK_00e368a8, _UNK_00e368ac };
    float maxBounds[4] = { _DAT_00e368b0, _UNK_00e368b4, _UNK_00e368b8, _UNK_00e368bc };
    
    // Alignment padding loop (likely for cache line alignment)
    uVar11 = 0;
    do {
        uVar11 = uVar11 + 0x40;
    } while (uVar11 < 0x200);
    
    // Output pointer starts at offset 0xC in output buffer
    puVar16 = (undefined8*)(blendIndices + 0xc);
    
    // Input vertex data pointer (offset 0x200 for vertex data)
    int vertexData = vertexCount + 0x200;
    
    do {
        // Load constants for vertex processing
        fVar10 = _UNK_00e3689c;
        fVar9 = _UNK_00e36898;
        fVar8 = _UNK_00e36894;
        fVar7 = _DAT_00e36890;
        
        // Extract bone indices from packed format (likely 4 bytes per vertex)
        uVar3 = *(ulonglong*)(vertexData + -0x1e8);
        
        // Decompose bone indices (likely 4 bytes: 3 bone indices + 1 weight index)
        // auVar5, auVar6, auVar4 are used for bit manipulation
        fVar18 = (float)(ushort)uVar3 * _DAT_00e36870;  // Scale factor for bone weight 0
        fVar20 = (float)((ushort)(uVar3 >> 16)) * _UNK_00e36874;  // Scale factor for bone weight 1
        fVar21 = (float)((ushort)(uVar3 >> 32)) * _UNK_00e36878;  // Scale factor for bone weight 2
        
        // Extract blend weight index (high 16 bits)
        uVar11 = (uint)((ulonglong)*(undefined8*)(vertexData + -500) >> 0x20);
        fVar45 = (float)(uVar11 & _UNK_00e368c4 | _UNK_00e36864);  // Blend weight with bias
        
        // Load vertex position (3 floats at offset -0x200)
        fVar32 = *(float*)(vertexData + -0x200);  // X
        fVar38 = *(float*)(vertexData + -0x1fc);  // Y
        fVar41 = *(float*)(vertexData + -0x1f8);  // Z
        
        // Extract bone indices from vertex data
        iVar29 = (int)*(undefined8*)(vertexData + -500);
        
        // Calculate bone matrix indices from packed data
        fVar30 = (float)((iVar29 << 2) >> 0x16) * _DAT_00e36880;  // Bone index 0
        fVar36 = (float)((int)(uVar11 << 2) >> 0x16) * _UNK_00e36884;  // Bone index 1
        
        // Get bone matrix pointers based on blend indices
        iVar12 = (uint)*(byte*)(vertexData + -0x1eb) * 0x40;  // Bone 0 matrix offset
        pfVar1 = (float*)(iVar12 + boneMatrices);
        iVar12 = iVar12 + boneMatrices;
        
        iVar13 = (uint)*(byte*)(vertexData + -0x1ec) * 0x40;  // Bone 1 matrix offset
        pfVar2 = (float*)(iVar13 + 0x10 + boneMatrices);
        pfVar14 = (float*)(iVar13 + boneMatrices);
        
        // Extract additional bone weights and indices
        fVar22 = (float)((iVar29 << 0x16) >> 0x16) * _DAT_00e36880;  // Weight 0
        fVar26 = (float)((int)(uVar11 << 0x16) >> 0x16) * _UNK_00e36884;  // Weight 1
        fVar27 = (float)((iVar29 << 0xc) >> 0x16) * _UNK_00e36888;  // Weight 2
        fVar28 = (float)((int)(uVar11 << 0xc) >> 0x16) * _UNK_00e3688c;  // Weight 3
        
        // Get bone matrix for bone 2
        pfVar15 = (float*)((uint)*(byte*)(vertexData + -0x1ea) * 0x40 + boneMatrices);
        
        // Perform skinning: blend vertex position with bone matrices
        // First row of blended matrix
        fVar31 = *pfVar14 * fVar18 + *pfVar1 * fVar20 + *pfVar15 * fVar21;
        fVar37 = pfVar14[1] * fVar18 + pfVar1[1] * fVar20 + pfVar15[1] * fVar21;
        fVar39 = pfVar14[2] * fVar18 + pfVar1[2] * fVar20 + pfVar15[2] * fVar21;
        fVar40 = pfVar14[3] * fVar18 + pfVar1[3] * fVar20 + pfVar15[3] * fVar21;
        
        // Second row of blended matrix
        fVar46 = *(float*)(iVar12 + 0x10) * fVar20 + *pfVar2 * fVar18 + pfVar15[4] * fVar21;
        fVar47 = *(float*)(iVar12 + 0x14) * fVar20 + pfVar2[1] * fVar18 + pfVar15[5] * fVar21;
        fVar48 = *(float*)(iVar12 + 0x18) * fVar20 + pfVar2[2] * fVar18 + pfVar15[6] * fVar21;
        fVar49 = *(float*)(iVar12 + 0x1c) * fVar20 + pfVar2[3] * fVar18 + pfVar15[7] * fVar21;
        
        // Third row of blended matrix
        fVar50 = *(float*)(iVar12 + 0x20) * fVar20 + pfVar14[8] * fVar18 + pfVar15[8] * fVar21;
        fVar51 = *(float*)(iVar12 + 0x24) * fVar20 + pfVar14[9] * fVar18 + pfVar15[9] * fVar21;
        fVar52 = *(float*)(iVar12 + 0x28) * fVar20 + pfVar14[10] * fVar18 + pfVar15[10] * fVar21;
        fVar53 = *(float*)(iVar12 + 0x2c) * fVar20 + pfVar14[0xb] * fVar18 + pfVar15[0xb] * fVar21;
        
        // Transform vertex position by blended matrix
        // auVar19 contains the transformed vertex (4 components)
        auVar19._0_8_ = CONCAT44(
            fVar38 * fVar47 + fVar32 * fVar37 + fVar41 * fVar51 +
            *(float*)(iVar12 + 0x34) * fVar20 + pfVar14[0xd] * fVar18 + pfVar15[0xd] * fVar21,
            fVar38 * fVar46 + fVar32 * fVar31 + fVar41 * fVar50 +
            *(float*)(iVar12 + 0x30) * fVar20 + pfVar14[0xc] * fVar18 + pfVar15[0xc] * fVar21
        );
        auVar19._8_4_ = fVar38 * fVar48 + fVar32 * fVar39 + fVar41 * fVar52 +
                        *(float*)(iVar12 + 0x38) * fVar20 + pfVar14[0xe] * fVar18 + pfVar15[0xe] * fVar21;
        auVar19._12_4_ = fVar38 * fVar49 + fVar32 * fVar40 + fVar41 * fVar53 +
                         *(float*)(iVar12 + 0x3c) * fVar20 + pfVar14[0xf] * fVar18 + pfVar15[0xf] * fVar21;
        
        // Update min/max bounds using SSE minps/maxps
        auVar42._8_4_ = auVar19._8_4_;
        auVar42._0_8_ = auVar19._0_8_;
        auVar42._12_4_ = auVar19._12_4_;
        minBounds = minps(auVar42, minBounds);
        
        auVar43._8_4_ = auVar19._8_4_;
        auVar43._0_8_ = auVar19._0_8_;
        auVar43._12_4_ = auVar19._12_4_;
        maxBounds = maxps(auVar43, maxBounds);
        
        // Calculate normal transformation (using inverse transpose)
        fVar41 = fVar27 * fVar46 + fVar22 * fVar31 + fVar30 * fVar50;
        fVar18 = fVar27 * fVar47 + fVar22 * fVar37 + fVar30 * fVar51;
        fVar20 = fVar27 * fVar48 + fVar22 * fVar39 + fVar30 * fVar52;
        fVar21 = fVar28 * fVar46 + fVar26 * fVar31 + fVar36 * fVar50;
        fVar31 = fVar28 * fVar47 + fVar26 * fVar37 + fVar36 * fVar51;
        fVar26 = fVar28 * fVar48 + fVar26 * fVar39 + fVar36 * fVar52;
        
        // Normalize the transformed normal
        fVar32 = fVar21 * fVar21;
        fVar38 = fVar31 * fVar31;
        auVar33._8_4_ = fVar26 * fVar26;
        auVar33._4_4_ = auVar33._8_4_;
        auVar33._0_4_ = auVar33._8_4_;
        auVar33._12_4_ = auVar33._8_4_;
        
        auVar24._4_4_ = fVar38 + fVar32 + auVar33._8_4_;
        auVar24._0_4_ = fVar38 + fVar32 + auVar33._8_4_;
        auVar24._8_4_ = fVar38 + fVar32 + auVar33._8_4_;
        auVar24._12_4_ = fVar38 + fVar32 + auVar33._8_4_;
        auVar34 = rsqrtps(auVar33, auVar24);  // Reciprocal square root
        
        fVar32 = fVar41 * fVar41;
        fVar38 = fVar18 * fVar18;
        auVar23._8_4_ = fVar20 * fVar20;
        auVar23._4_4_ = auVar23._8_4_;
        auVar23._0_4_ = auVar23._8_4_;
        auVar23._12_4_ = auVar23._8_4_;
        
        auVar44._0_4_ = fVar38 + fVar32 + auVar23._8_4_;
        auVar44._4_4_ = fVar38 + fVar32 + auVar23._8_4_;
        auVar44._8_4_ = fVar38 + fVar32 + auVar23._8_4_;
        auVar44._12_4_ = fVar38 + fVar32 + auVar23._8_4_;
        auVar24 = rsqrtps(auVar23, auVar44);
        
        // Apply normalization and scale to output
        fVar32 = auVar24._0_4_ * fVar41 * _DAT_00e36890 + _DAT_00e36890;
        fVar38 = auVar24._4_4_ * fVar18 * _UNK_00e36894 + _UNK_00e36894;
        fVar41 = auVar24._8_4_ * fVar20 * _UNK_00e36898 + _UNK_00e36898;
        fVar18 = auVar24._12_4_ * (fVar27 * fVar49 + fVar22 * fVar40 + fVar30 * fVar53) * _UNK_00e3689c + _UNK_00e3689c;
        
        // Store transformed vertex to output buffer
        uVar17 = movdq2q(in_MM0, auVar19);
        *(undefined8*)((int)puVar16 + -0xc) = uVar17;
        
        // Pack and store normal data
        auVar25._0_4_ = (int)fVar32;
        auVar25._4_4_ = (int)fVar38;
        auVar25._8_4_ = (int)fVar41;
        auVar25._12_4_ = (int)fVar18;
        
        auVar35._0_4_ = (int)(auVar34._0_4_ * fVar21 * fVar7 + fVar7);
        auVar35._4_4_ = (int)(auVar34._4_4_ * fVar31 * fVar8 + fVar8);
        auVar35._8_4_ = (int)(auVar34._8_4_ * fVar26 * fVar9 + fVar9);
        auVar35._12_4_ = (int)(fVar45 * fVar10 + fVar10);
        
        auVar34._8_8_ = auVar19._8_8_;
        auVar34._0_8_ = auVar34._8_8_;
        in_MM0 = movdq2q(uVar17, auVar34);
        
        packssdw(auVar25, auVar35);
        *(int*)((int)puVar16 + -4) = (int)in_MM0;
        in_MM1 = movdq2q(in_MM1, auVar34);
        *puVar16 = in_MM0;
        
        // Advance to next vertex (0x14 bytes per vertex output, 0x20 bytes input stride)
        puVar16 = (undefined8*)((int)puVar16 + 0x14);
        vertexData = vertexData + 0x20;
        vertexCount = vertexCount - 1;
        
    } while (vertexCount != 0);
    
    // Output min/max bounds
    *outMinBounds = minBounds[0];
    outMinBounds[1] = minBounds[1];
    outMinBounds[2] = minBounds[2];
    outMinBounds[3] = minBounds[3];
    
    *outMaxBounds = maxBounds[0];
    outMaxBounds[1] = maxBounds[1];
    outMaxBounds[2] = maxBounds[2];
    outMaxBounds[3] = maxBounds[3];
    
    return;
}
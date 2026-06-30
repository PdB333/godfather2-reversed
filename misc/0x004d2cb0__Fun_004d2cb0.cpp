// FUNC_NAME: Fun_004d2cb0
// +0x00: this pointer (in_EAX), param_1: output vertices, param_2: output indices
// Uses SSE movmskps, no __thiscall: C-style or static function
void FUN_004d2cb0(float* this, int outVertices, int outIndices) {
    float dVar1, dVar2, dVar3, dVar4;
    float dVar8, dVar9, dVar10, dVar11, dVar12, dVar13, dVar14, dVar15;
    float dVar16, dVar17, dVar18, dVar19, dVar20, dVar21, dVar22, dVar23;
    float dVar24, dVar25, dVar26, dVar27, dVar28, dVar29, dVar30, dVar31;
    float* pfVar34;
    int iVar35 = 0, iVar36;
    int uVar33, uVar37;
    // Global constant at 0x00e2b1a4 (assumed like 1.0f or a delta)
    float fConst = *(float*)0x00e2b1a4;
    // +0x18: some byte flag (enumerator / mask)
    byte bFlag = *(byte*)(this + 0x18);
    int unaff_EDI; // number of tests passed via caller

    if (0 < unaff_EDI) {
        // Save state from 'this' pointer array of 24 floats (address +0x00 .. +0x5C)
        dVar8 = this[0];  dVar9 = this[1];  dVar10 = this[2];  dVar11 = this[3];
        dVar12 = this[4];  dVar13 = this[5];  dVar14 = this[6];  dVar15 = this[7];
        dVar16 = this[8];  dVar17 = this[9];  dVar18 = this[10]; dVar19 = this[11];
        dVar20 = this[12]; dVar21 = this[13]; dVar22 = this[14]; dVar23 = this[15];
        dVar24 = this[16]; dVar25 = this[17]; dVar26 = this[18]; dVar27 = this[19];
        dVar28 = this[20]; dVar29 = this[21]; dVar30 = this[22]; dVar31 = this[23];
        // Point to source vertices/edges: outVertices+8
        pfVar34 = (float*)(outVertices + 8);
        do {
            dVar1 = pfVar34[-2]; // dx0
            dVar2 = pfVar34[1];  // dz?
            dVar3 = pfVar34[-1]; // dy0
            dVar4 = *pfVar34;    // dw?
            // Plane distance calculations with interpolation
            dVar38 = dVar27 * fConst + dVar26 * dVar4;
            dVar39 = dVar25 * dVar3 + dVar24 * dVar1;
            dVar40 = dVar31 * fConst + dVar30 * dVar4;
            dVar41 = dVar29 * dVar3 + dVar28 * dVar1;
            // Compare dVar2 (input coordinate) against two combinations -> 4x int mask
            auVar6._4_4_ = (unsigned int)(-(dVar2 < dVar39 + dVar38));
            auVar6._0_4_ = (unsigned int)(-(dVar2 < dVar41 + dVar40));
            auVar6._8_4_ = auVar6._0_4_;  // redundant
            auVar6._12_4_ = auVar6._4_4_; // redundant
            uVar33 = _mm_movemask_ps(*(__m128*)&auVar6);
            // Second set of plane equations (more complex)
            auVar7._4_4_ = (unsigned int)(-(dVar2 < dVar9 * dVar3 + dVar8 * dVar1 +
                                                   dVar11 * fConst + dVar10 * dVar4));
            auVar7._0_4_ = (unsigned int)(-(dVar2 < dVar13 * dVar3 + dVar12 * dVar1 +
                                                   dVar15 * fConst + dVar14 * dVar4));
            auVar7._8_4_ = (unsigned int)(-(dVar2 < dVar21 * dVar3 + dVar20 * dVar1 +
                                                   dVar23 * fConst + dVar22 * dVar4));
            auVar7._12_4_ = (unsigned int)(-(dVar2 < dVar17 * dVar3 + dVar16 * dVar1 +
                                                    dVar19 * fConst + dVar18 * dVar4));
            uVar37 = _mm_movemask_ps(*(__m128*)&auVar7);
            // Combine masks: if any plane test failed, result is 0; otherwise output 'bFlag' value
            int combined = (int)((uVar33 | uVar37) > 0 ? -1 : 0) & (int)bFlag;
            *(char*)(iVar35 + outIndices) = (char)combined;
            iVar36 = iVar35 + 1;
            pfVar34 += 4; // step 4 floats (16 bytes)
            iVar35 = iVar36;
        } while (iVar36 < unaff_EDI);
    }
    return;
}
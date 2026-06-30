// FUNC_NAME: BroadPhase::linearCast
LPVOID __thiscall BroadPhase::linearCast(int thisPtr, float* startPos, float* endPos, int param4, int param5)
{
    uint* puVar1;
    undefined4* puVar2;
    int* piVar3;
    int iVar4;
    undefined8 uVar5;
    LPVOID pvVar6;
    LPVOID pvVar7;
    int iVar8;
    int iVar9;
    float10 fVar10;
    float fVar11;
    float fVar12;
    float fVar13;
    float fVar14;
    float fVar15;
    float fVar16;
    float fVar17;
    float fStack_dc;
    float fStack_d8;
    float fStack_d4;
    float fStack_d0;
    float fStack_cc;
    float fStack_c8;
    float fStack_c4;
    float fStack_c0;
    float fStack_bc;
    float fStack_b8;
    float fStack_b4;
    float fStack_b0;
    float fStack_98;
    undefined4* puStack_94;
    undefined1 auStack_8c[80];
    float fStack_3c;
    float fStack_38;
    float fStack_34;
    float fStack_30;
    float fStack_2c;
    float fStack_28;
    undefined4 uStack_24;

    // Setup transform from this+0x160 to this+0xa0
    FUN_004b59d0(*(int*)(thisPtr + 0x160) + 0xd0, thisPtr + 0xa0);

    // TLS profiling: start "LtlinearCast"
    pvVar6 = TlsGetValue(DAT_01139830);
    puVar2 = *(undefined4**)((int)pvVar6 + 4);
    if (puVar2 < *(undefined4**)((int)pvVar6 + 0xc)) {
        *puVar2 = "LtlinearCast";
        puVar2[3] = "Stsetup";
        uVar5 = rdtsc();
        fStack_d4 = (float)uVar5;
        puVar2[1] = fStack_d4;
        *(undefined4**)((int)pvVar6 + 4) = puVar2 + 4;
    }

    // Store start position (4 floats) at this+0xd0
    *(float*)(thisPtr + 0xd0) = *startPos;
    *(float*)(thisPtr + 0xd4) = startPos[1];
    *(float*)(thisPtr + 0xd8) = startPos[2];
    *(float*)(thisPtr + 0xdc) = startPos[3];

    fStack_d8 = endPos[5]; // Note: endPos[5] is used, likely a radius or something

    // TLS profiling: start "StupdateBroadphase"
    pvVar6 = TlsGetValue(DAT_01139830);
    puStack_94 = *(undefined4**)((int)pvVar6 + 4);
    if (puStack_94 < *(undefined4**)((int)pvVar6 + 0xc)) {
        *puStack_94 = "StupdateBroadphase";
        uVar5 = rdtsc();
        fStack_d4 = (float)uVar5;
        puStack_94[1] = fStack_d4;
        *(undefined4**)((int)pvVar6 + 4) = puStack_94 + 3;
    }

    // Call broadphase update via vtable at this+0x10
    (**(code**)(**(int**)(thisPtr + 0x10) + 0x1c))
        (thisPtr + 0xa0,
         *(float*)(*(int*)(*(int*)(thisPtr + 8) + 0x6c) + 4) + fStack_d8,
         &fStack_d0);

    // Compute direction vector (end - start)
    fStack_bc = *endPos - *startPos;
    fStack_b8 = endPos[1] - startPos[1];
    fStack_b4 = endPos[2] - startPos[2];
    fStack_b0 = endPos[3] - startPos[3];

    // Clamp negative components to 0 (for min bound?)
    fVar12 = fStack_bc;
    if (0.0 < fStack_bc) {
        fVar12 = 0.0;
    }
    fStack_98 = fStack_b8;
    if (0.0 < fStack_b8) {
        fStack_98 = 0.0;
    }
    fVar17 = fStack_b4;
    if (0.0 < fStack_b4) {
        fVar17 = 0.0;
    }
    fVar16 = fStack_b0;
    if (0.0 < fStack_b0) {
        fVar16 = 0.0;
    }

    // Clamp positive components to 0 (for max bound?)
    fVar13 = fStack_bc;
    if (fStack_bc < 0.0) {
        fVar13 = 0.0;
    }
    fVar15 = fStack_b8;
    if (fStack_b8 < 0.0) {
        fVar15 = 0.0;
    }
    fVar14 = fStack_b4;
    if (fStack_b4 < 0.0) {
        fVar14 = 0.0;
    }
    fVar11 = 0.0;
    if (0.0 <= fStack_b0) {
        fVar11 = fStack_b0;
    }

    // Accumulate into local variables (likely AABB min/max)
    fStack_dc = fVar12 + fStack_dc;
    fStack_d8 = fStack_d8 + fStack_98;
    fStack_d4 = fStack_d4 + fVar17;
    fStack_d0 = fStack_d0 + fVar16;
    fStack_cc = fStack_cc + fVar13;
    fStack_c8 = fStack_c8 + fVar15;
    fStack_c4 = fStack_c4 + fVar14;
    fStack_c0 = fStack_c0 + fVar11;

    FUN_00a0e1e0(&fStack_dc); // Likely normalize or clamp AABB

    fStack_2c = (float)DAT_00e44598; // Some constant
    iVar8 = *(int*)(*(int*)(thisPtr + 8) + 0x6c);
    FUN_0054bfb0(iVar8); // Update broadphase internal state
    uStack_24 = *(undefined4*)(iVar8 + 0x6c);

    // Store direction vector for later use
    fStack_30 = fStack_b0;
    fStack_34 = fStack_b4;
    fStack_38 = fStack_b8;
    fStack_3c = fStack_bc;

    // Compute length of direction vector
    fVar10 = (float10)FUN_00414a80(fStack_b4 * fStack_b4 + fStack_b8 * fStack_b8 +
                                   fStack_bc * fStack_bc);
    fStack_28 = (float)fVar10;
    fStack_2c = endPos[4]; // endPos[4] is likely max distance

    // TLS profiling: start "StlinearCast"
    pvVar6 = TlsGetValue(DAT_01139830);
    puVar2 = *(undefined4**)((int)pvVar6 + 4);
    if (puVar2 < *(undefined4**)((int)pvVar6 + 0xc)) {
        *puVar2 = "StlinearCast";
        uVar5 = rdtsc();
        puVar2[1] = (int)uVar5;
        *(undefined4**)((int)pvVar6 + 4) = puVar2 + 3;
    }

    // Iterate over a list of objects (likely broadphase proxies)
    iVar8 = *(int*)(thisPtr + 0x154); // count
    iVar9 = *(int*)(*(int*)(thisPtr + 8) + 0x74); // vtable offset
    while (iVar8 = iVar8 + -1, -1 < iVar8) {
        if (iVar8 < *(int*)(thisPtr + 0x154)) {
            piVar3 = *(int**)(*(int*)(thisPtr + 0x150) + iVar8 * 4); // pointer to proxy
            (**(code**)(iVar9 + 0x9ac +
                        (uint)*(byte*)((*(int*)(*(int*)(thisPtr + 0x10) + 0xc) + 0xd) * 0x20 +
                                        *(int*)(*piVar3 + 0xc) + iVar9) * 0x14))
                (thisPtr + 0x10, piVar3, auStack_8c, param4, param5);
        }
    }

    // TLS profiling: end (string at DAT_00e391e4 likely "EndLinearCast")
    pvVar7 = TlsGetValue(DAT_01139830);
    puVar2 = *(undefined4**)((int)pvVar7 + 4);
    pvVar6 = pvVar7;
    if (puVar2 < *(undefined4**)((int)pvVar7 + 0xc)) {
        *puVar2 = &DAT_00e391e4;
        uVar5 = rdtsc();
        pvVar6 = (LPVOID)uVar5;
        puVar2[1] = pvVar6;
        *(undefined4**)((int)pvVar7 + 4) = puVar2 + 3;
    }

    // Check if there is a collision result and process it
    if ((*(int*)(thisPtr + 0x164) != 0) &&
        (pvVar6 = (LPVOID)(*(uint*)(*(int*)(thisPtr + 0x164) + 0xe4) >> 10), ((uint)pvVar6 & 1) != 0)) {
        if (param5 != 0) {
            FUN_0054cb00(param5); // Likely clear or reset collision info
        }
        pvVar6 = (LPVOID)FUN_0054cb00(param4);
        if (param5 != 0) {
            pvVar6 = (LPVOID)FUN_0054cdb0(); // Likely finalize collision
        }
        iVar8 = 0;
        if (0 < *(int*)(param4 + 0x14)) {
            iVar9 = 0;
            do {
                iVar4 = *(int*)(param4 + 0x10);
                puVar1 = (uint*)(iVar9 + 0x2c + iVar4);
                *puVar1 = *puVar1 & 0x3fffffff; // Clear some flags
                pvVar6 = (LPVOID)(iVar9 + 0x2c + iVar4);
                iVar8 = iVar8 + 1;
                iVar9 = iVar9 + 0x30;
            } while (iVar8 < *(int*)(param4 + 0x14));
        }
    }

    return pvVar6;
}
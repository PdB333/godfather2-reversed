// FUNC_NAME: WorldPhysics::sweepTestLinear
LPVOID __thiscall WorldPhysics::sweepTestLinear(WorldPhysics* this, float* start, float* end, int hitList, int filter)
{
    uint *puVar1;
    undefined4 *puVar2;
    int *piVar3;
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
    undefined4 *puStack_94;
    undefined1 auStack_8c [80];
    float fStack_3c;
    float fStack_38;
    float fStack_34;
    float fStack_30;
    float fStack_2c;
    float fStack_28;
    undefined4 uStack_24;
    
    // Prepare sweep state
    FUN_004b59d0(*(int *)(this + 0x160) + 0xd0, this + 0xa0);
    pvVar6 = TlsGetValue(DAT_01139830);
    puVar2 = *(undefined4 **)((int)pvVar6 + 4);
    if (puVar2 < *(undefined4 **)((int)pvVar6 + 0xc)) {
        *puVar2 = "LtlinearCast";
        puVar2[3] = "Stsetup";
        uVar5 = rdtsc();
        fStack_d4 = (float)uVar5;
        puVar2[1] = fStack_d4;
        *(undefined4 **)((int)pvVar6 + 4) = puVar2 + 4;
    }
    // Store start position
    *(float *)(this + 0xd0) = *start;
    *(float *)(this + 0xd4) = start[1];
    *(float *)(this + 0xd8) = start[2];
    *(float *)(this + 0xdc) = start[3];
    fStack_d8 = end[5];
    pvVar6 = TlsGetValue(DAT_01139830);
    puStack_94 = *(undefined4 **)((int)pvVar6 + 4);
    if (puStack_94 < *(undefined4 **)((int)pvVar6 + 0xc)) {
        *puStack_94 = "StupdateBroadphase";
        uVar5 = rdtsc();
        fStack_d4 = (float)uVar5;
        puStack_94[1] = fStack_d4;
        *(undefined4 **)((int)pvVar6 + 4) = puStack_94 + 3;
    }
    // Update broadphase with sweep distance
    (**(code **)(**(int **)(this + 0x10) + 0x1c))
              (this + 0xa0, *(float *)(*(int *)(*(int *)(this + 8) + 0x6c) + 4) + fStack_d8,
               &fStack_d0);
    // Compute delta = end - start
    fStack_bc = *end - *start;
    fStack_b8 = end[1] - start[1];
    fStack_b4 = end[2] - start[2];
    fStack_b0 = end[3] - start[3];
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
    // Accumulate into AABB min/max from sweep
    fStack_dc = fVar12 + fStack_dc;
    fStack_d8 = fStack_d8 + fStack_98;
    fStack_d4 = fStack_d4 + fVar17;
    fStack_d0 = fStack_d0 + fVar16;
    fStack_cc = fStack_cc + fVar13;
    fStack_c8 = fStack_c8 + fVar15;
    fStack_c4 = fStack_c4 + fVar14;
    fStack_c0 = fStack_c0 + fVar11;
    // Compute final AABB from accumulated min/max
    FUN_00a0e1e0(&fStack_dc);
    fStack_2c = (float)DAT_00e44598;
    iVar8 = *(int *)(*(int *)(this + 8) + 0x6c);
    FUN_0054bfb0(iVar8);
    uStack_24 = *(undefined4 *)(iVar8 + 0x6c);
    fStack_30 = fStack_b0;
    fStack_34 = fStack_b4;
    fStack_38 = fStack_b8;
    fStack_3c = fStack_bc;
    fVar10 = (float10)FUN_00414a80(fStack_b4 * fStack_b4 + fStack_b8 * fStack_b8 +
                                   fStack_bc * fStack_bc);
    fStack_28 = (float)fVar10;
    fStack_2c = end[4]; // sweep speed from user
    pvVar6 = TlsGetValue(DAT_01139830);
    puVar2 = *(undefined4 **)((int)pvVar6 + 4);
    if (puVar2 < *(undefined4 **)((int)pvVar6 + 0xc)) {
        *puVar2 = "StlinearCast";
        uVar5 = rdtsc();
        puVar2[1] = (int)uVar5;
        *(undefined4 **)((int)pvVar6 + 4) = puVar2 + 3;
    }
    iVar8 = *(int *)(this + 0x154); // number of collision objects
    iVar9 = *(int *)(*(int *)(this + 8) + 0x74); // collision dispatcher table
    while (iVar8 = iVar8 + -1, -1 < iVar8) {
        if (iVar8 < *(int *)(this + 0x154)) {
            piVar3 = *(int **)(*(int *)(this + 0x150) + iVar8 * 4); // object pointer
            (**(code **)(iVar9 + 0x9ac +
                        (uint)*(byte *)((*(int *)(*(int *)(this + 0x10) + 0xc) + 0xd) * 0x20 +
                                        *(int *)(*piVar3 + 0xc) + iVar9) * 0x14))
                      (this + 0x10, piVar3, auStack_8c, hitList, filter);
        }
    }
    pvVar7 = TlsGetValue(DAT_01139830);
    puVar2 = *(undefined4 **)((int)pvVar7 + 4);
    pvVar6 = pvVar7;
    if (puVar2 < *(undefined4 **)((int)pvVar7 + 0xc)) {
        *puVar2 = "StlinearCastEnd";
        uVar5 = rdtsc();
        pvVar6 = (LPVOID)uVar5;
        puVar2[1] = pvVar6;
        *(undefined4 **)((int)pvVar7 + 4) = puVar2 + 3;
    }
    if ((*(int *)(this + 0x164) != 0) &&
       (pvVar6 = (LPVOID)(*(uint *)(*(int *)(this + 0x164) + 0xe4) >> 10), ((uint)pvVar6 & 1) != 0)) {
        // Process results if flag is set
        if (filter != 0) {
            FUN_0054cb00(filter);
        }
        pvVar6 = (LPVOID)FUN_0054cb00(hitList);
        if (filter != 0) {
            pvVar6 = (LPVOID)FUN_0054cdb0();
        }
        iVar8 = 0;
        if (0 < *(int *)(hitList + 0x14)) {
            iVar9 = 0;
            do {
                iVar4 = *(int *)(hitList + 0x10);
                puVar1 = (uint *)(iVar9 + 0x2c + iVar4);
                *puVar1 = *puVar1 & 0x3fffffff; // Clear high bits (mark as processed?)
                pvVar6 = (LPVOID)(iVar9 + 0x2c + iVar4);
                iVar8 = iVar8 + 1;
                iVar9 = iVar9 + 0x30;
            } while (iVar8 < *(int *)(hitList + 0x14));
        }
    }
    return pvVar6;
}
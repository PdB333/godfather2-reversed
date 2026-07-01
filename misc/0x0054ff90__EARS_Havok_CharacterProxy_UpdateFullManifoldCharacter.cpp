// Xbox PDB: EARS::Havok::CharacterProxy::UpdateFullManifoldCharacter
// FUNC_NAME: CharacterProxy::update
void CharacterProxy::update(float deltaTime)
{
    int *piVar1;
    int iVar2;
    undefined8 uVar3;
    float fVar4;
    char cVar5;
    LPVOID pvVar6;
    undefined4 *puVar7;
    float fVar8;
    float fVar9;
    float fVar10;
    undefined4 uVar11;
    undefined4 uStack_454;
    float fStack_450;
    float fStack_44c;
    float fStack_448;
    float fStack_444;
    float fStack_440;
    float fStack_43c;
    float fStack_438;
    float fStack_434;
    float fStack_430;
    float fStack_42c;
    float fStack_428;
    float fStack_424;
    undefined4 uStack_420;
    undefined4 uStack_41c;
    undefined1 auStack_410 [16];
    float fStack_400;
    undefined4 uStack_3fc;
    undefined4 uStack_3f0;
    undefined4 uStack_3d0;
    int iStack_3c0;
    undefined **appuStack_3b0 [104];
    undefined4 *puStack_210;
    undefined4 uStack_208;
    undefined4 uStack_204;
    undefined4 uStack_1f0;
    undefined **appuStack_1e0 [104];
    undefined4 *puStack_40;
    undefined4 uStack_38;
    undefined4 uStack_34;
    undefined ***pppuStack_20;

    // Check the proxy update type (enum stored at +0xe8)
    // 0 = proxy with two check supports
    // 1 = terrain disabled
    // other = just raycast
    if (*(int *)(param_1 + 0xe8) == 0) {
        // Proxy update with two check supports (ground check)
        pvVar6 = TlsGetValue(DAT_01139830);
        puVar7 = *(undefined4 **)((int)pvVar6 + 4);
        if (puVar7 < *(undefined4 **)((int)pvVar6 + 0xc)) {
            *puVar7 = "LtCharacter Proxy Update with two check supports?";
            puVar7[3] = "StFirst check support";
            uVar3 = rdtsc();
            uStack_454 = (undefined4)uVar3;
            puVar7[1] = uStack_454;
            *(undefined4 **)((int)pvVar6 + 4) = puVar7 + 4;
        }
        // Compute ground check raycast start position (offset from character position)
        // +0x90, +0x94, +0x98, +0x9c are the ground check offsets
        fStack_430 = DAT_00e44564 - *(float *)(param_1 + 0x90);
        fStack_42c = DAT_00e44564 - *(float *)(param_1 + 0x94);
        fStack_428 = DAT_00e44564 - *(float *)(param_1 + 0x98);
        fStack_424 = DAT_00e44564 - *(float *)(param_1 + 0x9c);
        *(uint *)(param_1 + 0xe4) = *(uint *)(param_1 + 0xe4) | 4;  // set ground check busy flag
        FUN_00553750(&fStack_430);
        *(uint *)(param_1 + 0xe4) = *(uint *)(param_1 + 0xe4) & 0xfffffffb;  // clear ground check busy flag
        
        // Get character position and velocity
        fVar8 = *(float *)(param_1 + 100);  // +0x64 = position.x
        fVar9 = *(float *)(param_1 + 0x68); // +0x68 = position.y
        fVar10 = *(float *)(param_1 + 0x6c); // +0x6c = position.z
        uVar11 = 0;
        fStack_440 = fVar8;
        fStack_43c = fVar9;
        fStack_438 = fVar10;
        
        if ((*(byte *)(param_1 + 0xe4) & 1) == 0) {
            // Not flying, apply velocity
            FUN_0054efb0(param_2);
            fVar8 = *(float *)(param_1 + 0x70) + fStack_440;  // +0x70 = velocity.x
            fVar9 = *(float *)(param_1 + 0x74) + fStack_43c;  // +0x74 = velocity.y
            fVar10 = *(float *)(param_1 + 0x78) + fStack_438; // +0x78 = velocity.z
            uVar11 = *(undefined4 *)(param_1 + 0x7c); // +0x7c = ?
        }
        fStack_444 = 0.0;
        iVar2 = *(int *)(param_1 + 0x14);  // +0x14 = collision object pointer?
        *(float *)(iVar2 + 0x10) = fVar8;
        *(float *)(iVar2 + 0x14) = fVar9;
        *(float *)(iVar2 + 0x18) = fVar10;
        *(undefined4 *)(iVar2 + 0x1c) = uVar11;
        fStack_448 = param_2;
        if (0.0 < param_2) {
            fStack_444 = DAT_00e2b1a4 / param_2;  // 1.0/deltaTime = invDeltaTime
        }
        
        pvVar6 = TlsGetValue(DAT_01139830);
        puVar7 = *(undefined4 **)((int)pvVar6 + 4);
        if (puVar7 < *(undefined4 **)((int)pvVar6 + 0xc)) {
            *puVar7 = "StIntegrate the character";
            uVar3 = rdtsc();
            uStack_454 = (undefined4)uVar3;
            puVar7[1] = uStack_454;
            *(undefined4 **)((int)pvVar6 + 4) = puVar7 + 3;
        }
        
        // Check if some flag is set at bit 10 of +0xe4
        if ((*(uint *)(param_1 + 0xe4) >> 10 & 1) == 0) {
            // Normal path
            FUN_0054bae0();
            FUN_0054bae0();
            FUN_00552930(&fStack_450,appuStack_1e0);
            if (puStack_40 == (undefined4 *)0x0) {
                piVar1 = (int *)(param_1 + 0xd8);
                *(undefined4 *)(param_1 + 0xcc) = 0;
                *(undefined4 *)(param_1 + 0xd0) = 0;
                *(undefined4 *)(param_1 + 0x60) = 0xfe16702f;  // default surface??
                if (*piVar1 != 0) {
                    FUN_004daf90(piVar1);
                    *piVar1 = 0;
                }
            }
            else {
                *(undefined4 *)(param_1 + 0xcc) = *puStack_40;
                *(undefined4 *)(param_1 + 0xd0) = puStack_40[1];
                *(undefined4 *)(param_1 + 0x60) = uStack_38;
                FUN_0044b210(uStack_34);
            }
            FUN_0054bc00();
            FUN_0054bc00();
        }
        else {
            // Alternative path with pppuStack
            FUN_0054bae0();
            appuStack_3b0[0] = &PTR_LAB_00e39f08;
            uStack_1f0 = 0;
            FUN_0054bae0();
            pppuStack_20 = appuStack_3b0;
            appuStack_1e0[0] = &PTR_LAB_00e39f08;
            FUN_00552930(&fStack_450,pppuStack_20);
            if (puStack_210 == (undefined4 *)0x0) {
                piVar1 = (int *)(param_1 + 0xd8);
                *(undefined4 *)(param_1 + 0xcc) = 0;
                *(undefined4 *)(param_1 + 0xd0) = 0;
                if (*piVar1 != 0) {
                    FUN_004daf90(piVar1);
                    *piVar1 = 0;
                }
                *(undefined4 *)(param_1 + 0x60) = 0xfe16702f;
            }
            else {
                *(undefined4 *)(param_1 + 0xcc) = *puStack_210;
                *(undefined4 *)(param_1 + 0xd0) = puStack_210[1];
                *(undefined4 *)(param_1 + 0x60) = uStack_208;
                FUN_0044b210(uStack_204);
            }
            FUN_0054bcf0();
            FUN_0054bcf0();
        }
        
        // Second ground check support
        *(uint *)(param_1 + 0xe4) = *(uint *)(param_1 + 0xe4) | 4;  // set busy flag
        pvVar6 = TlsGetValue(DAT_01139830);
        puVar7 = *(undefined4 **)((int)pvVar6 + 4);
        if (puVar7 < *(undefined4 **)((int)pvVar6 + 0xc)) {
            *puVar7 = "StDo another check support";
            uVar3 = rdtsc();
            uStack_454 = (undefined4)uVar3;
            puVar7[1] = uStack_454;
            *(undefined4 **)((int)pvVar6 + 4) = puVar7 + 3;
        }
        FUN_00553750(&fStack_430);
        *(uint *)(param_1 + 0xe4) = *(uint *)(param_1 + 0xe4) & 0xfffffffb;  // clear busy flag
        
        // Check if the character is on the ground
        cVar5 = FUN_0054f240();
        if (cVar5 == '\0') {
            // Not on ground - reset ground timer
            *(undefined4 *)(param_1 + 0xa4) = 0;
        }
        else if (*(int *)(param_1 + 0xa4) == 0) {
            // Just landed - set ground timer
            *(undefined4 *)(param_1 + 0xa4) = DAT_01205224;
        }
        
        // Handle frozen state (e.g., ragdoll transition)
        if (*(char *)(param_1 + 0x30) == '\0') {
            // Not frozen
            if (*(int *)(param_1 + 0xb0) == 0) {
                *(undefined4 *)(param_1 + 0xb0) = DAT_01205224;
            }
        }
        else {
            // Frozen - reset something
            *(undefined4 *)(param_1 + 0xb0) = 0;
        }
        
        pvVar6 = TlsGetValue(DAT_01139830);
        puVar7 = *(undefined4 **)((int)pvVar6 + 4);
        if (*(undefined4 **)((int)pvVar6 + 0xc) <= puVar7) {
            return;
        }
        *puVar7 = &DAT_00e391e4;
        uVar3 = rdtsc();
        uStack_454 = (undefined4)uVar3;
        goto LAB_00550a5a;
    }
    
    if (*(int *)(param_1 + 0xe8) != 1) {
        // Proxy update just raycast (no ground check, no terrain disabled)
        pvVar6 = TlsGetValue(DAT_01139830);
        puVar7 = *(undefined4 **)((int)pvVar6 + 4);
        if (puVar7 < *(undefined4 **)((int)pvVar6 + 0xc)) {
            *puVar7 = "TtCharacter Proxy Update just raycast";
            uVar3 = rdtsc();
            uStack_454 = (undefined4)uVar3;
            puVar7[1] = uStack_454;
            *(undefined4 **)((int)pvVar6 + 4) = puVar7 + 3;
        }
        fVar4 = DAT_00e2b1a4;
        iVar2 = *(int *)(param_1 + 0x14);
        fVar8 = *(float *)(param_1 + 100);
        fVar9 = *(float *)(param_1 + 0x68);
        fVar10 = *(float *)(param_1 + 0x6c);
        *(float *)(iVar2 + 0x10) = fVar8;
        *(float *)(iVar2 + 0x14) = fVar9;
        *(float *)(iVar2 + 0x18) = fVar10;
        *(float *)(iVar2 + 0x1c) = fVar4;
        iVar2 = *(int *)(*(int *)(*(int *)(param_1 + 0x14) + 0x30) + 0x18);
        fStack_450 = fVar8 * param_2 + *(float *)(iVar2 + 0x30);
        fStack_44c = fVar9 * param_2 + *(float *)(iVar2 + 0x34);
        fStack_448 = fVar10 * param_2 + *(float *)(iVar2 + 0x38);
        fStack_444 = *(float *)(iVar2 + 0x3c) + param_2;
        FUN_009f1820(&fStack_450,0);
        
        if ((*(uint *)(param_1 + 0xe4) >> 3 & 1) == 0) {
            uStack_3fc = 0xffffffff;
            uStack_3f0 = 0xffffffff;
            fStack_400 = DAT_00e2b1a4;
            uStack_3d0 = 0;
            iStack_3c0 = 0;
            FUN_00550c50(auStack_410);
            if (iStack_3c0 == 0) {
                puVar7 = (undefined4 *)0x0;
LAB_00550960:
                uVar11 = 0;
            }
            else {
                puVar7 = (undefined4 *)FUN_00542700(auStack_410);
                if (puVar7 == (undefined4 *)0x0) goto LAB_00550960;
                uVar11 = *puVar7;
            }
            *(undefined4 *)(param_1 + 0xcc) = uVar11;
            if (puVar7 == (undefined4 *)0x0) {
                uVar11 = 0;
            }
            else {
                uVar11 = puVar7[1];
            }
            *(undefined4 *)(param_1 + 0xd0) = uVar11;
            if (iStack_3c0 == 0) goto LAB_00550841;
            uVar11 = FUN_004afca0(iStack_3c0);
            FUN_0044b210(uVar11);
            if ((*(int *)(param_1 + 0xd8) == 0) || (*(int *)(param_1 + 0xd8) == 0x48)) {
                puVar7 = (undefined4 *)FUN_0054c0e0(&uStack_454,iStack_3c0);
                *(undefined4 *)(param_1 + 0x60) = *puVar7;
            }
            else {
                puVar7 = (undefined4 *)FUN_00421430();
                *(undefined4 *)(param_1 + 0x60) = *puVar7;
            }
        }
        else {
            *(undefined4 *)(param_1 + 0xcc) = 0;
            *(undefined4 *)(param_1 + 0xd0) = 0;
            *(undefined4 *)(param_1 + 0x60) = 0xfe16702f;
LAB_00550841:
            if (*(int *)(param_1 + 0xd8) != 0) {
                FUN_004daf90((undefined4 *)(param_1 + 0xd8));
                *(undefined4 *)(param_1 + 0xd8) = 0;
            }
        }
        fStack_434 = 0.0;
        fStack_438 = param_2;
        if (0.0 < param_2) {
            fStack_434 = DAT_00e2b1a4 / param_2;
        }
        if ((*(uint *)(param_1 + 0xe4) >> 10 & 1) == 0) {
            FUN_0054bae0();
            FUN_0054bae0();
            FUN_00552930(&fStack_440,appuStack_1e0);
            FUN_0054bc00();
            FUN_0054bc00();
        }
        else {
            FUN_0054bae0();
            appuStack_3b0[0] = &PTR_LAB_00e39f08;
            uStack_1f0 = 0;
            FUN_0054bae0();
            pppuStack_20 = appuStack_3b0;
            appuStack_1e0[0] = &PTR_LAB_00e39f08;
            FUN_00552930(&fStack_440,pppuStack_20);
            FUN_0054bcf0();
            FUN_0054bcf0();
        }
        pvVar6 = TlsGetValue(DAT_01139830);
        puVar7 = *(undefined4 **)((int)pvVar6 + 4);
        if (*(undefined4 **)((int)pvVar6 + 0xc) <= puVar7) {
            return;
        }
        *puVar7 = &DAT_00e39c6c;
        uVar3 = rdtsc();
        uStack_454 = (undefined4)uVar3;
        goto LAB_00550a5a;
    }
    
    // Proxy update with terrain disabled (e.g. flying/dead characters)
    pvVar6 = TlsGetValue(DAT_01139830);
    puVar7 = *(undefined4 **)((int)pvVar6 + 4);
    if (puVar7 < *(undefined4 **)((int)pvVar6 + 0xc)) {
        *puVar7 = "LtCharacter Proxy Update with terrain disabled";
        puVar7[3] = "StSetup";
        uVar3 = rdtsc();
        uStack_454 = (undefined4)uVar3;
        puVar7[1] = uStack_454;
        *(undefined4 **)((int)pvVar6 + 4) = puVar7 + 4;
    }
    fVar4 = DAT_00e2b1a4;
    iVar2 = *(int *)(param_1 + 0x14);
    fVar8 = *(float *)(param_1 + 100);
    fVar9 = *(float *)(param_1 + 0x68);
    fVar10 = *(float *)(param_1 + 0x6c);
    *(float *)(iVar2 + 0x10) = fVar8;
    *(float *)(iVar2 + 0x14) = fVar9;
    *(float *)(iVar2 + 0x18) = fVar10;
    *(float *)(iVar2 + 0x1c) = fVar4;
    iVar2 = *(int *)(*(int *)(*(int *)(param_1 + 0x14) + 0x30) + 0x18);
    fStack_450 = fVar8 * param_2 + *(float *)(iVar2 + 0x30);
    fStack_44c = fVar9 * param_2 + *(float *)(iVar2 + 0x34);
    fStack_448 = fVar10 * param_2 + *(float *)(iVar2 + 0x38);
    fStack_444 = *(float *)(iVar2 + 0x3c) + param_2;
    uStack_41c = DAT_00e44834;
    uStack_420 = DAT_00e2e780;
    iVar2 = *(int *)(*(int *)(*(int *)(param_1 + 0x14) + 0x30) + 0x18);
    fStack_430 = *(float *)(iVar2 + 0x30);
    fStack_42c = *(float *)(iVar2 + 0x34);
    fStack_428 = *(float *)(iVar2 + 0x38);
    fStack_424 = *(float *)(iVar2 + 0x3c);
    
    pvVar6 = TlsGetValue(DAT_01139830);
    puVar7 = *(undefined4 **)((int)pvVar6 + 4);
    if (puVar7 < *(undefined4 **)((int)pvVar6 + 0xc)) {
        *puVar7 = "StLinear Cast";
        uVar3 = rdtsc();
        uStack_454 = (undefined4)uVar3;
        puVar7[1] = uStack_454;
        *(undefined4 **)((int)pvVar6 + 4) = puVar7 + 3;
    }
    
    if ((*(uint *)(param_1 + 0xe4) >> 10 & 1) == 0) {
        FUN_0054bae0();
        FUN_0054bae0();
        (**(code **)(**(int **)(*(int *)(param_1 + 0x14) + 0x30) + 0x34))
                  (&fStack_450,&fStack_430,appuStack_3b0,appuStack_1e0);
        FUN_0054bc00();
        FUN_0054bc00();
    }
    else {
        FUN_0054bae0();
        appuStack_3b0[0] = &PTR_LAB_00e39f08;
        uStack_1f0 = 0;
        FUN_0054bae0();
        pppuStack_20 = appuStack_3b0;
        appuStack_1e0[0] = &PTR_LAB_00e39f08;
        (**(code **)(**(int **)(*(int *)(param_1 + 0x14) + 0x30) + 0x34))
                  (&fStack_450,&fStack_430,appuStack_1e0,appuStack_3b0);
        FUN_0054bcf0();
        FUN_0054bcf0();
    }
    
    pvVar6 = TlsGetValue(DAT_01139830);
    puVar7 = *(undefined4 **)((int)pvVar6 + 4);
    if (puVar7 < *(undefined4 **)((int)pvVar6 + 0xc)) {
        *puVar7 = "StAfter Linear Cast";
        uVar3 = rdtsc();
        uStack_454 = (undefined4)uVar3;
        puVar7[1] = uStack_454;
        *(undefined4 **)((int)pvVar6 + 4) = puVar7 + 3;
    }
    
    if ((*(uint *)(param_1 + 0xe4) >> 3 & 1) == 0) {
        pvVar6 = TlsGetValue(DAT_01139830);
        puVar7 = *(undefined4 **)((int)pvVar6 + 4);
        if (puVar7 < *(undefined4 **)((int)pvVar6 + 0xc)) {
            *puVar7 = "StSometimes raycast";
            uVar3 = rdtsc();
            uStack_454 = (undefined4)uVar3;
            puVar7[1] = uStack_454;
            *(undefined4 **)((int)pvVar6 + 4) = puVar7 + 3;
        }
        uStack_3fc = 0xffffffff;
        uStack_3f0 = 0xffffffff;
        fStack_400 = DAT_00e2b1a4;
        uStack_3d0 = 0;
        iStack_3c0 = 0;
        FUN_00550c50(auStack_410);
        if (iStack_3c0 == 0) {
            puVar7 = (undefined4 *)0x0;
LAB_005506d6:
            uVar11 = 0;
        }
        else {
            puVar7 = (undefined4 *)FUN_00542700(auStack_410);
            if (puVar7 == (undefined4 *)0x0) goto LAB_005506d6;
            uVar11 = *puVar7;
        }
        *(undefined4 *)(param_1 + 0xcc) = uVar11;
        if (puVar7 == (undefined4 *)0x0) {
            uVar11 = 0;
        }
        else {
            uVar11 = puVar7[1];
        }
        *(undefined4 *)(param_1 + 0xd0) = uVar11;
        if (iStack_3c0 == 0) goto LAB_00550610;
        uVar11 = FUN_004afca0(iStack_3c0);
        FUN_0044b210(uVar11);
        if ((*(int *)(param_1 + 0xd8) == 0) || (*(int *)(param_1 + 0xd8) == 0x48)) {
            puVar7 = (undefined4 *)FUN_0054c0e0(&uStack_454,iStack_3c0);
            *(undefined4 *)(param_1 + 0x60) = *puVar7;
        }
        else {
            puVar7 = (undefined4 *)FUN_00421430();
            *(undefined4 *)(param_1 + 0x60) = *puVar7;
        }
    }
    else {
        *(undefined4 *)(param_1 + 0xcc) = 0;
        *(undefined4 *)(param_1 + 0xd0) = 0;
        *(undefined4 *)(param_1 + 0x60) = 0xfe16702f;
LAB_00550610:
        if (*(int *)(param_1 + 0xd8) != 0) {
            FUN_004daf90((undefined4 *)(param_1 + 0xd8));
            *(undefined4 *)(param_1 + 0xd8) = 0;
        }
    }
    
    pvVar6 = TlsGetValue(DAT_01139830);
    puVar7 = *(undefined4 **)((int)pvVar6 + 4);
    if (*(undefined4 **)((int)pvVar6 + 0xc) <= puVar7) {
        return;
    }
    *puVar7 = &DAT_00e391e4;
    uVar3 = rdtsc();
    uStack_454 = (undefined4)uVar3;
LAB_00550a5a:
    puVar7[1] = uStack_454;
    *(undefined4 **)((int)pvVar6 + 4) = puVar7 + 3;
    return;
}
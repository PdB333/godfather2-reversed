// FUNC_NAME: PlayerSM::processWeaponSlots
void __fastcall PlayerSM::processWeaponSlots(int *thisPtr)
{
    bool bVar1;
    char cVar2;
    uint uVar3;
    int iVar4;
    int iVar5;
    uint *puVar6;
    int iVar7;
    undefined4 uVar8;
    int *piVar9;
    byte bVar10;
    int *piVar11;
    undefined4 *puVar12;
    char *pcVar13;
    float fVar14;
    float fVar15;
    float fVar16;
    float fVar17;
    undefined4 uVar18;
    int iStack_22c;
    char *pcStack_228;
    int *piStack_224;
    int iStack_220;
    int *piStack_21c;
    int iStack_218;
    int iStack_214;
    uint uStack_20c;
    uint uStack_208;
    undefined4 uStack_204;
    undefined4 local_200;
    undefined4 uStack_1fc;
    float fStack_1f8;
    float fStack_1f4;
    float fStack_1f0;
    float fStack_1ec;
    int iStack_1e0;
    int *piStack_1dc;
    float fStack_1d8;
    float fStack_1d4;
    float fStack_1d0;
    float fStack_1cc;
    int *apiStack_1c0 [2];
    undefined **ppuStack_1b8;
    undefined4 uStack_1b4;
    undefined1 *puStack_1a8;
    int iStack_1a4;
    uint uStack_1a0;
    undefined1 auStack_198 [404];
    
    local_200 = 0;
    cVar2 = (**(code **)(*thisPtr + 0x10))(0x383225a1, &local_200);
    iStack_218 = 0;
    uStack_20c = -(uint)(cVar2 != '\0') & uStack_208;
    do {
        iVar7 = iStack_218;
        piVar11 = thisPtr + iStack_218 * 0x48 + 0x410; // +0x410: weapon slot array (10 slots, 0x48 each)
        bVar10 = (byte)iStack_218;
        uVar3 = 1 << (bVar10 & 0x1f);
        piStack_1dc = piVar11;
        if ((thisPtr[0x182] & uVar3) == 0) { // +0x608: activeWeaponFlags
            if ((((thisPtr[0x181] & uVar3) != 0) && (bVar10 < 10)) &&
               (thisPtr[(char)bVar10 * 0x48 + 0x440] != 0)) { // +0x440: weaponEntityPtrs
                iVar4 = *(int *)(thisPtr[(char)bVar10 * 0x48 + 0x440] + 0xc); // entity type
                if (iVar4 == 2) {
                    FUN_00549da0(); // playEquipSound
                }
                else if (iVar4 == 6) {
                    FUN_00549e00(); // playUnequipSound
                }
            }
        }
        else {
            fStack_1f8 = (float)piVar11[0x10]; // +0x40: weapon position x
            fStack_1f4 = (float)piVar11[0x11]; // +0x44: weapon position y
            fStack_1f0 = (float)piVar11[0x12]; // +0x48: weapon position z
            fStack_1ec = (float)piVar11[0x13]; // +0x4c: weapon rotation
            if ((bVar10 < 10) && (thisPtr[(char)bVar10 * 0x48 + 0x440] != 0)) {
                iVar4 = *(int *)(thisPtr[(char)bVar10 * 0x48 + 0x440] + 0xc);
                if (iVar4 == 2) {
                    FUN_00549da0();
                }
                else if (iVar4 == 6) {
                    FUN_00549e00();
                }
            }
            puStack_1a8 = auStack_198;
            uStack_1a0 = 0x80000008;
            iStack_1a4 = 0;
            uStack_1b4 = DAT_00e445dc;
            ppuStack_1b8 = &PTR_LAB_00d723d4;
            FUN_007fbd10(piVar11, &fStack_1f8, &ppuStack_1b8); // getWeaponCollisionResults
            iStack_1e0 = iStack_1a4;
            iStack_214 = 0;
            if (0 < iStack_1a4) {
                do {
                    puVar12 = (undefined4 *)(puStack_1a8 + iStack_214 * 0x30);
                    iVar4 = puVar12[10]; // collision entity
                    if ((iVar4 != 0) && (*(char *)(iVar4 + 0x10) + iVar4 != 0)) {
                        piStack_224 = (int *)0x0;
                        FUN_004af8c0(apiStack_1c0, 0x2001); // getPlayerFromEntity
                        piVar11 = (int *)0x0;
                        if (apiStack_1c0[0] != (int *)0x0) {
                            piStack_224 = apiStack_1c0[0];
                            piVar11 = apiStack_1c0[0];
                        }
                        iVar7 = iStack_218;
                        if ((piVar11 != (int *)0x0) && (piVar11 != thisPtr)) {
                            bVar1 = false;
                            iStack_220 = 0;
                            piStack_21c = (int *)0x0;
                            if (((*(byte *)(thisPtr + 0x183) & 1) != 0) && // +0x60c: weaponFlags
                               ((thisPtr[0x3ff] != 0 && (thisPtr[0x3ff] != 0x48)))) { // +0xffc: currentWeaponIndex
                                if (thisPtr[0x3ff] == 0) {
                                    pcStack_228 = (char *)0x0;
                                }
                                else {
                                    pcStack_228 = (char *)(thisPtr[0x3ff] + -0x48);
                                }
                                iVar4 = FUN_0043b490(); // getCurrentTime
                                iVar5 = FUN_0043b490();
                                piVar11 = piStack_224;
                                iVar7 = iStack_218;
                                if (iVar5 == iVar4) goto LAB_0080b4b2;
                            }
                            uStack_204 = *puVar12; // collision point x
                            local_200 = puVar12[1]; // collision point y
                            uStack_1fc = puVar12[2]; // collision point z
                            pcStack_228 = (char *)0x0;
                            cVar2 = (**(code **)(*piVar11 + 0x10))(0x55859efa, &pcStack_228); // isPlayerAlive
                            if (((cVar2 == '\0') || (pcStack_228 == (char *)0x0)) ||
                               (((uint)thisPtr[0x183] >> 1 & 1) != 0)) { // +0x60c: weaponFlags bit 1
                                iStack_22c = 0;
                                cVar2 = (**(code **)(*piVar11 + 0x10))(0xa7039c8, &iStack_22c); // isPlayerInVehicle
                                if (((cVar2 == '\0') || (iStack_22c == 0)) || (((uint)thisPtr[0x183] >> 2 & 1) != 0)) {
                                    iStack_22c = 0;
                                    cVar2 = (**(code **)(*piVar11 + 0x10))(0xa5975eb2, &iStack_22c); // isPlayerInCover
                                    if (((cVar2 == '\0') || (iStack_22c == 0)) ||
                                       (((uint)thisPtr[0x183] >> 3 & 1) != 0)) goto LAB_0080b29e;
                                    if ((*(byte *)(piVar11 + 0x286) & 1) == 0) { // +0xa18: playerFlags bit 0
                                        uVar8 = FUN_00691810(0); // getWeaponDamage
                                        piVar11 = piStack_224;
                                        (**(code **)(*thisPtr + 0x1e8))
                                                  (piStack_224, thisPtr[0x6e4], 0xffffffff, &uStack_204, 0, uVar8); // applyDamage
                                    }
                                    uVar18 = puVar12[10];
                                    uVar8 = 0xffffffff;
                                }
                                else {
                                    cVar2 = FUN_00481620(); // isPlayerInVehicle
                                    if (cVar2 != '\0') {
                                        uVar8 = FUN_00691810(0);
                                        piVar11 = piStack_224;
                                        (**(code **)(*thisPtr + 0x1e8))
                                                  (piStack_224, thisPtr[0x6e4], 0xffffffff, &uStack_204, 0, uVar8);
                                    }
                                    uVar8 = puVar12[0xb];
                                    uVar18 = puVar12[10];
                                }
                                bVar1 = true;
                                piStack_21c = (int *)FUN_005566a0(uVar18, uVar8); // getWeaponData
                            }
                            else {
                                piStack_224 = (int *)FUN_007faa70(puVar12[10]); // getHitEntity
                                if (piStack_224 == (int *)0x0) {
                                    piVar9 = (int *)FUN_005566a0(puVar12[10], puVar12[0xb]);
                                    if ((piVar9 != (int *)0x0) && (*piVar9 == 0x69)) { // weapon type check
                                        fVar17 = (float)piStack_1dc[0x10] - fStack_1f8;
                                        fVar15 = (float)piStack_1dc[0x12] - fStack_1f0;
                                        fVar14 = (float)piStack_1dc[0x11] - fStack_1f4;
                                        fVar16 = fVar17 * fVar17 + fVar15 * fVar15 + fVar14 * fVar14;
                                        bVar1 = true;
                                        piStack_21c = piVar9;
                                        if (fVar16 != _DAT_00d577a0) {
                                            fVar16 = _DAT_00d5780c / SQRT(fVar16);
                                            fStack_1d8 = fVar16 * fVar17 * DAT_00d92298;
                                            fStack_1d4 = fVar14 * fVar16 * DAT_00d92298;
                                            fStack_1d0 = fVar15 * fVar16 * DAT_00d92298;
                                            fStack_1cc = ((float)piStack_1dc[0x13] - fStack_1ec) * fVar16 * DAT_00d92298;
                                            FUN_005417d0(DAT_00d5f374, &fStack_1d8, puVar12); // applyKnockback
                                        }
                                    }
                                }
                                else {
                                    bVar1 = true;
                                    pcStack_228 = (char *)0x0;
                                    iVar4 = FUN_00558d40(puVar12[10], puVar12[0xb]); // getWeaponIndex
                                    iVar7 = iStack_220;
                                    if (iVar4 != -1) {
                                        puVar6 = (uint *)FUN_00558b00(iVar4); // getWeaponConfig
                                        pcStack_228 = (char *)(*puVar6 >> 2);
                                        iVar7 = FUN_00558a10(iVar4); // getWeaponAmmo
                                    }
                                    piStack_21c = (int *)0x0;
                                    if ((iVar7 != 0) && (*(int **)(iVar7 + 8) != (int *)0x0)) {
                                        piStack_21c = *(int **)(iVar7 + 8);
                                    }
                                    if (((uint)piVar11[0x208] >> 3 & 1) != 0) { // +0x820: playerFlags bit 3
                                        piStack_21c = (int *)&DAT_00e53b3c;
                                    }
                                    cVar2 = FUN_00481620(); // isPlayerInVehicle
                                    pcVar13 = pcStack_228;
                                    if (cVar2 != '\0') {
                                        uVar8 = FUN_00691810(0);
                                        pcVar13 = pcStack_228;
                                        (**(code **)(*thisPtr + 0x1e8))
                                                  (piVar11, thisPtr[0x6e4], pcStack_228, &uStack_204, 0, uVar8);
                                    }
                                    if ((pcVar13 == (char *)((uint)piVar11[0x19e] >> 2)) ||
                                       (pcVar13 == (char *)((uint)piVar11[0x1a8] >> 2))) { // check weapon type
                                        FUN_007f63e0(0x54); // playHitSound
                                    }
                                }
                            }
LAB_0080b29e:
                            if (uStack_20c == 0) {
LAB_0080b34f:
                                if (piStack_21c != (int *)0x0) {
                                    if ((iStack_218 == 9) && (iVar7 = FUN_00691810(), iVar7 != 0)) {
                                        FUN_00691810();
                                        pcStack_228 = (char *)FUN_00707510(); // getFistWeaponName
                                    }
                                    else if (((uint)thisPtr[0x23b] >> 4 & 1) == 0) { // +0x8ec: playerFlags bit 4
                                        pcStack_228 = (&PTR_DAT_00e53d7c)[iStack_218]; // weapon name table
                                    }
                                    else {
                                        pcStack_228 = "fist_brass_knuckles";
                                    }
                                    piStack_224 = (int *)*piStack_21c;
                                    iStack_22c = 0;
                                    cVar2 = (**(code **)(*piVar11 + 0x10))(0x55859efa, &iStack_22c); // isPlayerAlive
                                    iVar7 = iStack_22c;
                                    if (cVar2 == '\0') {
                                        iVar7 = 0;
                                    }
                                    else if (((iStack_22c != 0) && ((*(uint *)(iStack_22c + 0x8e0) >> 0xb & 1) != 0)) // playerFlags bit 11
                                            && (cVar2 = FUN_00690150(0xf), cVar2 == '\0')) { // isGodMode
                                        piStack_224 = (int *)&DAT_00000068; // damage type
                                    }
                                    FUN_00805a10(pcStack_228, piStack_224, &uStack_204, 0xffffffff); // spawnBulletImpact
                                    if ((iVar7 != 0) &&
                                       ((piStack_224 == (int *)&DAT_00000064 ||
                                        (cVar2 = FUN_00690150(0x54), cVar2 != '\0')))) { // isBulletImpact
                                        FUN_007f6420(0x54); // playImpactSound
                                        iStack_220 = FUN_0043b870(DAT_01131018); // getCurrentTime
                                        cVar2 = FUN_0043c6c0(thisPtr, *(undefined4 *)(iVar7 + 0x1e48)); // checkHitCooldown
                                        if ((cVar2 == '\0') && (iStack_220 != 0)) {
                                            FUN_009af6f0(thisPtr); // triggerHitReaction
                                        }
                                    }
                                }
                            }
                            else {
                                iStack_22c = 0;
                                cVar2 = (**(code **)(*piVar11 + 0x10))(0x369ac561, &iStack_22c); // isPlayerInCover
                                if ((((cVar2 == '\0') || (iStack_22c == 0)) ||
                                    ((*(uint *)(iStack_22c + 0x8e4) >> 0xd & 1) == 0)) && // coverFlags bit 13
                                   ((*(char *)(uStack_20c + 0x1ec4) != '\x1c' &&
                                    (*(char *)(uStack_20c + 0x1ec4) != '\x1d')))) { // not in cover state
                                    if ((bVar1) && (cVar2 = (**(code **)(*piVar11 + 0x78))(), cVar2 != '\0')) { // isPlayerAlive
                                        iVar7 = FUN_006bea40(piVar11); // getPlayerHealth
                                        if ((iVar7 != 0) && (cVar2 = FUN_009ae8a0(1), cVar2 == '\0')) goto LAB_0080b46a; // isPlayerDead
                                        FUN_0079d2f0(iStack_218, piVar11, thisPtr[0x6e4]); // applyWeaponDamage
                                        FUN_0079db60(thisPtr[0x6e4]); // updateHealthBar
                                    }
                                    goto LAB_0080b34f;
                                }
                            }
LAB_0080b46a:
                            iVar7 = thisPtr[0x236]; // +0x8d8: hitReactionIndex
                            if (iVar7 == 5) {
                                iVar4 = 3;
                                do {
                                    iVar7 = iVar4;
                                    iVar4 = iVar7 + -1;
                                } while (iVar4 != 0);
                                iVar7 = iVar7 + 3;
                            }
                            iVar4 = FUN_0043b490(); // getCurrentTime
                            thisPtr[iVar7 + 0x22d] = iVar4; // +0x8b4: hitReactionTimers
                            thisPtr[0x235] = (int)(thisPtr + 0x22d); // +0x8d4: currentHitReactionTimer
                            thisPtr[0x236] = iVar7 + 1; // +0x8d8: hitReactionIndex
                            iVar7 = iStack_218;
                        }
                    }
LAB_0080b4b2:
                    iStack_214 = iStack_214 + 1;
                } while (iStack_214 < iStack_1e0);
            }
            ppuStack_1b8 = &PTR_LAB_00e397fc;
            if (-1 < (int)uStack_1a0) {
                uVar3 = uStack_1a0 & 0x3fffffff;
                TlsGetValue(DAT_01139810);
                FUN_00aa26e0(puStack_1a8, uVar3 * 0x30, 0x17); // freeCollisionResults
            }
        }
        iStack_218 = iVar7 + 1;
        if (9 < iStack_218) {
            thisPtr[0x182] = thisPtr[0x181]; // +0x608: updateActiveWeaponFlags
            return;
        }
    } while( true );
}
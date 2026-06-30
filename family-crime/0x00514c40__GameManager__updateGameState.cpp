// FUNC_NAME: GameManager::updateGameState
int __thiscall GameManager::updateGameState(uint flags, char param_3)
{
    int iVar1;
    float fVar2;
    undefined4 uVar3;
    undefined4 uVar4;
    int iVar5;
    uint uVar6;
    undefined4 *puVar7;
    uint uVar8;
    undefined4 local_28;
    uint local_24;
    float local_20;
    float fStack_1c;
    float fStack_18;
    undefined4 uStack_14;

    // g_fDefaultValue is a global float (DAT_00e2b1a4)
    fVar2 = g_fDefaultValue;

    // Check if the object's bounding box or position is outside a threshold (g_fZeroThreshold)
    // Offsets: +0x40, +0x20, +0x24, +0x28, +0x4c, +0x30, +0x34, +0x38
    // If all conditions fail, return 0 (early exit)
    if (((*(float *)(this + 0x40) <= g_fZeroThreshold && g_fZeroThreshold != *(float *)(this + 0x40)) ||
        (((*(float *)(this + 0x20) <= g_fZeroThreshold && g_fZeroThreshold != *(float *)(this + 0x20) &&
          (*(float *)(this + 0x24) <= g_fZeroThreshold && g_fZeroThreshold != *(float *)(this + 0x24)))
         && (*(float *)(this + 0x28) <= g_fZeroThreshold && g_fZeroThreshold != *(float *)(this + 0x28))
         ))) && ((*(float *)(this + 0x4c) <= g_fZeroThreshold &&
                  g_fZeroThreshold != *(float *)(this + 0x4c) ||
                 (((*(float *)(this + 0x30) <= g_fZeroThreshold &&
                    g_fZeroThreshold != *(float *)(this + 0x30) &&
                   (*(float *)(this + 0x34) <= g_fZeroThreshold &&
                    g_fZeroThreshold != *(float *)(this + 0x34))) &&
                  (*(float *)(this + 0x38) <= g_fZeroThreshold &&
                   g_fZeroThreshold != *(float *)(this + 0x38))))))) {
        return 0;
    }

    local_28 = 0;
    if ((flags & 0x10) != 0) {
        if (g_bSomeFlag == '\0') {
            puVar7 = (undefined4 *)0x0;
        } else {
            puVar7 = &local_28;
        }
        iVar5 = FUN_00507150(puVar7); // Some initialization or check
        if ((iVar5 != 0) && (iVar5 == -1)) {
            return 0;
        }
    }

    // Get current ID from global or from a pointer (g_pPlayer + 0x16c)
    if (g_pPlayer == 0) {
        local_24 = g_uCurrentID;
    } else {
        local_24 = *(uint *)(g_pPlayer + 0x16c);
    }

    // Increment state counter
    g_iStateCounter = g_iStateCounter + 1;

    if (param_3 == '\0') {
        FUN_00609890(1); // Set some render mode
    }

    // Clamp screen dimensions (g_iScreenWidth, g_iScreenHeight)
    if (g_iScreenWidth < 0x16) {
        g_iScreenWidth = 0x16;
    }
    if (0x16 < g_iScreenHeight) {
        g_iScreenHeight = 0x16;
    }
    g_bRenderFlag1 = 1;

    if (g_iScreenWidth < 7) {
        g_iScreenWidth = 7;
    }
    if (7 < g_iScreenHeight) {
        g_iScreenHeight = 7;
    }
    g_bRenderFlag2 = 0;

    if (g_iScreenWidth < 0xe) {
        g_iScreenWidth = 0xe;
    }
    if (0xe < g_iScreenHeight) {
        g_iScreenHeight = 0xe;
    }
    g_bRenderFlag3 = 0;

    if (g_iScreenWidth < 0x19) {
        g_iScreenWidth = 0x19;
    }
    if (0x19 < g_iScreenHeight) {
        g_iScreenHeight = 0x19;
    }
    g_bRenderFlag4 = 5;

    if (g_iScreenWidth < 0x18) {
        g_iScreenWidth = 0x18;
    }
    if (0x18 < g_iScreenHeight) {
        g_iScreenHeight = 0x18;
    }
    g_bRenderFlag5 = 0;

    if (g_iScreenWidth < 0xf) {
        g_iScreenWidth = 0xf;
    }
    if (0xf < g_iScreenHeight) {
        g_iScreenHeight = 0xf;
    }
    g_bRenderFlag6 = 0;

    if (g_iScreenWidth < 0x1b) {
        g_iScreenWidth = 0x1b;
    }
    if (0x1a < g_iScreenHeight) {
        g_iScreenHeight = 0x1b;
    }
    g_bRenderFlag7 = 0;

    FUN_00417cf0(1, 2, 1); // Set some global state

    uVar8 = g_uSomeID;
    uVar6 = 0;
    do {
        if (g_aIDArray[uVar6 * 2] == g_uSomeID) {
            if (uVar6 < 0x14) {
                g_aFlagArray[uVar6 * 2] = g_aFlagArray[uVar6 * 2] & 0xfffffffc;
            }
            break;
        }
        uVar6 = uVar6 + 1;
    } while (uVar6 < 0x14);

    uVar4 = g_uOldFlag2;
    uVar3 = g_uOldFlag1;
    g_uOldFlag1 = uVar8;
    g_uOldFlag2 = 0;
    FUN_00609340(0, uVar3, uVar4); // Set viewport
    FUN_0060db60(0, 0, 0, 0x3f800000, 0x3f800000); // Set clear color (RGBA: 0,0,0,1,1)
    FUN_00609810(1); // Enable something
    FUN_005392b0(); // Update camera
    FUN_005388a0(); // Update something else

    uVar6 = g_uCurrentID;
    if (g_pPlayer != 0) {
        uVar6 = *(uint *)(g_pPlayer + 0x16c);
    }
    if ((uVar6 != 0xffffffff) && (uVar6 < 0x1000)) {
        iVar5 = uVar6 * 0x38;
        if ((g_pSomeArray + iVar5 != (byte *)0x0) && ((byte)(g_pSomeArray)[iVar5] < 4)) {
            if (*(int *)(g_pSomeArray + 0x1c + iVar5) != 0) {
                FUN_00606e60(*(int *)(g_pSomeArray + 0x1c + iVar5), 0x200000); // Set flags
            }
            *(uint *)(g_pSomeArray + 0xc + iVar5) = *(uint *)(g_pSomeArray + 0xc + iVar5) & 0xfcac8fff | 0x200000;
            FUN_006189c0(); // Update something
        }
    }

    g_fSomeGlobal = fVar2; // Store default value

    if (((g_pSomePtr == &g_someStruct) && (g_someStruct.field1 == g_someOtherField)) && (g_someFlag != 0)) {
        FUN_0060add0(g_someStruct.field1, g_someFlag, &g_fSomeGlobal); // Some operation
    }

    FUN_005394e0(); // Update something

    // Second set of bounds checks (similar to first but with different offsets)
    if ((*(float *)(this + 0x40) <= g_fZeroThreshold && g_fZeroThreshold != *(float *)(this + 0x40)) ||
       (((local_20 = *(float *)(this + 0x20), local_20 < g_fZeroThreshold &&
         (*(float *)(this + 0x24) <= g_fZeroThreshold && g_fZeroThreshold != *(float *)(this + 0x24)))
        && (*(float *)(this + 0x28) <= g_fZeroThreshold && g_fZeroThreshold != *(float *)(this + 0x28)))
       )) {
        local_20 = g_fDefaultValue;
        fStack_1c = g_fDefaultValue;
        fStack_18 = g_fDefaultValue;
    } else {
        fStack_1c = *(float *)(this + 0x24);
        fStack_18 = *(float *)(this + 0x28);
    }
    uStack_14 = 0;
    FUN_005398d0(); // Update something

    if ((*(float *)(this + 0x4c) <= g_fZeroThreshold && g_fZeroThreshold != *(float *)(this + 0x4c)) ||
       (((local_20 = *(float *)(this + 0x30), local_20 < g_fZeroThreshold &&
         (*(float *)(this + 0x34) <= g_fZeroThreshold && g_fZeroThreshold != *(float *)(this + 0x34)))
        && (*(float *)(this + 0x38) <= g_fZeroThreshold && g_fZeroThreshold != *(float *)(this + 0x38)))
       )) {
        local_20 = 0.0;
        fStack_1c = 0.0;
        fStack_18 = 0.0;
    } else {
        fStack_1c = *(float *)(this + 0x34);
        fStack_18 = *(float *)(this + 0x38);
    }
    uStack_14 = 0;
    FUN_005399a0(); // Update something

    // Compute some values based on global floats
    g_fSomeX = g_fGlobalA * g_fGlobalB;
    g_fSomeY = g_fGlobalC * g_fGlobalD;
    fStack_18 = 0.0;
    uStack_14 = local_28;
    g_fSomeZ = 0;
    g_fSomeW = local_28;
    local_20 = g_fSomeX;
    fStack_1c = g_fSomeY;

    if (((g_pSomePtr == &g_someStruct) && (g_someStruct.field1 == g_someOtherField2)) {
        FUN_0060add0(g_someOtherField2, g_someFlag2, &g_fSomeX); // Some operation
    }

    puVar7 = (undefined4 *)FUN_0060cd00(0xd, 4, 0, 1, 0); // Allocate memory
    uVar3 = g_fSomeGlobal2;
    fVar2 = g_fDefaultValue;
    if (puVar7 != (undefined4 *)0x0) {
        *puVar7 = g_fSomeGlobal2;
        puVar7[1] = uVar3;
        puVar7[2] = fVar2;
        puVar7[3] = uVar3;
        puVar7[4] = fVar2;
        puVar7[5] = fVar2;
        puVar7[6] = uVar3;
        puVar7[7] = fVar2;
        FUN_0060cde0(); // Free or commit
    }

    FUN_00539250(); // Update something
    FUN_00609890(1); // Set render mode
    FUN_0052c420(uVar8, 0); // Some operation with ID

    uVar8 = g_uCurrentID;
    if (g_pPlayer != 0) {
        uVar8 = *(uint *)(g_pPlayer + 0x16c);
    }
    uVar6 = 0;
    do {
        if (g_aIDArray[uVar6 * 2] == uVar8) {
            if (uVar6 < 0x14) {
                g_aFlagArray[uVar6 * 2] = g_aFlagArray[uVar6 * 2] & 0xfffffffc;
            }
            break;
        }
        uVar6 = uVar6 + 1;
    } while (uVar6 < 0x14);

    uVar3 = g_uOldFlag2;
    uVar6 = g_uOldFlag1;
    g_uOldFlag2 = 0;
    g_uOldFlag1 = uVar8;
    FUN_00609340(0, uVar6, uVar3); // Set viewport
    FUN_0060db60(0, 0, 0, 0x3f800000, 0x3f800000); // Set clear color

    uVar8 = g_uSomeID;
    iVar5 = g_pPlayer;
    uVar6 = g_uCurrentID;
    if (g_pPlayer != 0) {
        uVar6 = *(uint *)(g_pPlayer + 0x16c);
    }
    if ((uVar6 != 0xffffffff) && (uVar6 < 0x1000)) {
        iVar1 = uVar6 * 0x38;
        if ((g_pSomeArray + iVar1 != (byte *)0x0) && ((byte)(g_pSomeArray)[iVar1] < 4)) {
            if (*(int *)(g_pSomeArray + 0x1c + iVar1) != 0) {
                FUN_00606e60(*(int *)(g_pSomeArray + 0x1c + iVar1), 0x210000); // Set flags
            }
            *(uint *)(g_pSomeArray + 0xc + iVar1) = *(uint *)(g_pSomeArray + 0xc + iVar1) & 0xfcad8fff | 0x210000;
            FUN_006189c0(); // Update something
        }
    }
    if ((uVar8 != 0xffffffff) && (uVar8 < 0x1000)) {
        iVar1 = uVar8 * 0x38;
        if ((g_pSomeArray + iVar1 != (byte *)0x0) && ((byte)(g_pSomeArray)[iVar1] < 4)) {
            if (*(int *)(g_pSomeArray + 0x1c + iVar1) != 0) {
                FUN_00606e60(*(int *)(g_pSomeArray + 0x1c + iVar1), 0x200000); // Set flags
            }
            *(uint *)(g_pSomeArray + 0xc + iVar1) = *(uint *)(g_pSomeArray + 0xc + iVar1) & 0xfcac8fff | 0x200000;
            FUN_006189c0(); // Update something
        }
    }

    // Clamp screen dimensions again (similar to earlier)
    if (g_iScreenWidth < 0x16) {
        g_iScreenWidth = 0x16;
    }
    if (0x16 < g_iScreenHeight) {
        g_iScreenHeight = 0x16;
    }
    g_bRenderFlag1 = 1;

    if (g_iScreenWidth < 7) {
        g_iScreenWidth = 7;
    }
    if (7 < g_iScreenHeight) {
        g_iScreenHeight = 7;
    }
    g_bRenderFlag2 = 1;

    if (g_iScreenWidth < 0xe) {
        g_iScreenWidth = 0xe;
    }
    if (0xe < g_iScreenHeight) {
        g_iScreenHeight = 0xe;
    }
    g_bRenderFlag3 = 1;

    if (g_iScreenWidth < 0x19) {
        g_iScreenWidth = 0x19;
    }
    if (0x19 < g_iScreenHeight) {
        g_iScreenHeight = 0x19;
    }
    g_bRenderFlag4 = 7;

    if (g_iScreenWidth < 0x18) {
        g_iScreenWidth = 0x18;
    }
    if (0x18 < g_iScreenHeight) {
        g_iScreenHeight = 0x18;
    }
    g_bRenderFlag5 = 0;

    if (g_iScreenWidth < 0xf) {
        g_iScreenWidth = 0xf;
    }
    if (0xf < g_iScreenHeight) {
        g_iScreenHeight = 0xf;
    }
    g_bRenderFlag6 = 0;

    if (g_iScreenWidth < 0x1b) {
        g_iScreenWidth = 0x1b;
    }
    if (0x1a < g_iScreenHeight) {
        g_iScreenHeight = 0x1b;
    }
    g_bRenderFlag7 = 0;

    FUN_00417cf0(1, 5, 6); // Set some global state

    uVar8 = g_uCurrentID;
    if (iVar5 != 0) {
        uVar8 = *(uint *)(iVar5 + 0x16c);
    }
    if (local_24 == uVar8) {
        g_iStateCounter = g_iStateCounter - 1; // Decrement counter if IDs match
    }

    return 1;
}
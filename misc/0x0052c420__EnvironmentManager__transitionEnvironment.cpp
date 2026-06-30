// FUNC_NAME: EnvironmentManager::transitionEnvironment

/* 0x0052c420 - Transition between two environmental zones (e.g., interior/exterior, day/night)
   Handles fog color, depth texture, render states, and zone state flags.
   param1: bool bForward (true = forward transition, false = backward)
   param2: uint sourceZoneId
   param3: uint destZoneId (0 = auto-detect from global arrays)
*/

void __thiscall EnvironmentManager::transitionEnvironment(bool bForward, uint sourceZoneId, uint destZoneId)
{
    uint uVar1;
    bool bVar2;
    int iVar3;
    bool bCrossTransition; // bVar4
    undefined4 uVar5;
    int iVar6;
    uint uVar7;
    uint uVar8;
    float in_XMM0_Da;
    float fVar9;
    float fVar10;
    float in_XMM1_Da;
    undefined4 uVar11;
    float local_1c;
    uint local_10;

    // Determine destZoneId if not provided
    if (destZoneId == 0) {
        // Select zone ID from global array based on direction
        // Array: gAltTransitionZones[2] (DAT_01218eb8)
        // Offset: if bForward? -2? Actually: (-(uint)(bForward) & 0xfffffffd) * 2 gives 0 or -2 index
        destZoneId = gAltTransitionZoneC[bForward ? -3 : 0];
    }

    // Use default blending factor if XMM0 equals a sentinel (DAT_00e2eff4)
    if (in_XMM0_Da == gSentinelFloat) {
        in_XMM0_Da = in_XMM1_Da;
    }

    local_1c = gTransitionBlendDefault; // DAT_00e2d99c
    if (bForward) {
        local_1c = gTransitionBlendForward; // DAT_00e2b04c
    }
    local_1c = in_XMM1_Da - local_1c; // Difference between new and old blend values

    fVar9 = gTransitionBlendDefault;
    if (bForward) {
        fVar9 = gTransitionBlendForward;
    }
    fVar9 = in_XMM0_Da - fVar9;

    fVar10 = fVar9;
    if (fVar9 < local_1c) {
        fVar10 = local_1c;
    }

    if (fVar10 <= 0.0f) return;

    local_10 = sourceZoneId;

    // Retrieve two zone IDs from global arrays based on direction
    uVar1 = gAltTransitionZoneA[bForward ? -1 : 0]; // DAT_01218ea8
    iVar6 = (bForward ? -2 : 0) + 0xd; // -> index 0xb or 0xd? Actually: (-(uint)bForward & 0xfffffffd)+0xd
    uVar8 = gTransitionZoneIds[iVar6 * 2]; // DAT_01218e50[iVar6*2]

    // Determine if this is a cross-fade transition
    bool bCrossTransition = false;
    bool bVar2 = fVar9 < local_1c;
    if ((local_1c != fVar9) && (fVar9 > 0.0f) && (local_1c > 0.0f)) {
        bCrossTransition = true;
    }

    // Check if the blend factor exceeds a threshold
    if (gTransitionBlendForward <= (float)((uint)(fVar9 - local_1c) & gFloatMask)) {
        if (bCrossTransition) {
            uVar8 = *(uint *)(&gTransitionZoneAlt + (bForward ? -2 : 0) * 8); // DAT_01218e78
            if (bVar2) {
                local_1c = fVar9;
            }
            goto LAB_0x0052c531;
        }
    } else {
        bCrossTransition = false;
    }
    local_1c = 0.0f;
LAB_0x0052c531:

    // Update zone resource state for sourceZoneId, uVar1, uVar8, destZoneId
    // Each zone has a state entry of size 0x38 in gZoneResourceArray (DAT_011a0f28)
    if ((sourceZoneId != 0xFFFFFFFF) && (sourceZoneId < 0x1000)) {
        iVar3 = sourceZoneId * 0x38;
        if ((&gZoneResourceArray[iVar3] != NULL) && (gZoneResourceArray[iVar3].state < 4)) {
            if (gZoneResourceArray[iVar3].resource != 0) {
                FUN_00606e60(gZoneResourceArray[iVar3].resource, 0x100000); // load/lock resource
            }
            gZoneResourceArray[iVar3].flags = (gZoneResourceArray[iVar3].flags & 0xfc9c8fff) | 0x100000;
            FUN_006189c0(); // update resource system
        }
    }

    if ((uVar1 != 0xFFFFFFFF) && (uVar1 < 0x1000)) {
        iVar3 = uVar1 * 0x38;
        if ((&gZoneResourceArray[iVar3] != NULL) && (gZoneResourceArray[iVar3].state < 4)) {
            if (gZoneResourceArray[iVar3].resource != 0) {
                FUN_00606e60(gZoneResourceArray[iVar3].resource, 0x100000);
            }
            gZoneResourceArray[iVar3].flags = (gZoneResourceArray[iVar3].flags & 0xfc9c8fff) | 0x100000;
            FUN_006189c0();
        }
    }

    if ((uVar8 != 0xFFFFFFFF) && (uVar8 < 0x1000)) {
        iVar3 = uVar8 * 0x38;
        if ((&gZoneResourceArray[iVar3] != NULL) && (gZoneResourceArray[iVar3].state < 4)) {
            if (gZoneResourceArray[iVar3].resource != 0) {
                FUN_00606e60(gZoneResourceArray[iVar3].resource, 0x100000);
            }
            gZoneResourceArray[iVar3].flags = (gZoneResourceArray[iVar3].flags & 0xfc9c8fff) | 0x100000;
            FUN_006189c0();
        }
    }

    if ((destZoneId != 0xFFFFFFFF) && (destZoneId < 0x1000)) {
        iVar3 = destZoneId * 0x38;
        if ((&gZoneResourceArray[iVar3] != NULL) && (gZoneResourceArray[iVar3].state < 4)) {
            if (gZoneResourceArray[iVar3].resource != 0) {
                FUN_00606e60(gZoneResourceArray[iVar3].resource, 0x100000);
            }
            gZoneResourceArray[iVar3].flags = (gZoneResourceArray[iVar3].flags & 0xfc9c8fff) | 0x100000;
            FUN_006189c0();
        }
    }

    // Update global state
    FUN_0053d590(); // maybe clear render queue?
    FUN_00417cf0(1, 2, 1); // set some rendering mode (1=?, 2=?, 1=?)

    if (gRenderStateVar1 < 27) gRenderStateVar1 = 27;
    if (27 < gRenderStateVar2) gRenderStateVar2 = 27;
    gGlobalFlag1 = 0;

    // Remove uVar1 from zone list
    uVar7 = 0;
    do {
        if (gTransitionZoneIds[uVar7 * 2] == uVar1) {
            if (uVar7 < 20) {
                gTransitionZoneFlags[uVar7 * 2] &= 0xfffffffc; // clear lower 2 bits
            }
            break;
        }
        uVar7++;
    } while (uVar7 < 20);

    uVar5 = gCurrentTransitionTo; // DAT_011f38f4
    uVar11 = gCurrentTransitionFrom; // DAT_011f38f0
    gCurrentTransitionTo = 0;
    gCurrentTransitionFrom = uVar1;
    FUN_00609340(0, uVar11, uVar5); // set transition source/dest?

    // Remove uVar8 from zone list
    uVar7 = 0;
    do {
        if (gTransitionZoneIds[uVar7 * 2] == uVar8) {
            if (uVar7 < 20) {
                gTransitionZoneFlags[uVar7 * 2] &= 0xfffffffc;
            }
            break;
        }
        uVar7++;
    } while (uVar7 < 20);

    uVar11 = gCurrentTransitionTo;
    uVar7 = gCurrentTransitionFrom;
    gCurrentTransitionTo = 0;
    gCurrentTransitionFrom = uVar8;
    FUN_00609340(0, uVar7, uVar11);

    if (bCrossTransition) {
        // Handle cross-fade: re-add uVar1 and set blend
        uVar8 = 0;
        do {
            if (gTransitionZoneIds[uVar8 * 2] == uVar1) {
                if (uVar8 < 20) {
                    gTransitionZoneFlags[uVar8 * 2] &= 0xfffffffc;
                }
                break;
            }
            uVar8++;
        } while (uVar8 < 20);

        uVar11 = gCurrentTransitionTo;
        uVar8 = gCurrentTransitionFrom;
        gCurrentTransitionTo = 0;
        gCurrentTransitionFrom = uVar1;
        FUN_00609340(0, uVar8, uVar11);

        FUN_00609810(1); // push render state

        // Set fog and shader parameters for transition
        gFogShader = gDefaultFogShader; // DAT_0121b750
        gFogEnabled = 0; // DAT_0121b874
        gCurrentShader = gTransitionShaderA; // DAT_0121b754

        if ((gTransitionShaderA == gShaderFogColor) || 
            (gTransitionShaderA == gShaderFogParams) ||
            (gTransitionShaderA == gShaderDepthTexture)) {
            gFogColorParam = FUN_0060a580(gTransitionShaderA, "fog_color");
            gFogParamsParam = FUN_0060a580(gCurrentShader, "fog_params");
            gDepthTextureParam = FUN_0060a580(gCurrentShader, "depth_texture");
        }

        if (gCurrentShaderSet == &gShaderState1) { // DAT_012058e8, &DAT_0121b740
            FUN_0060a460(gCurrentShader);
            FUN_0060a460(gFogShader);
        }

        FUN_005388a0(); // update shader constants? 
        FUN_0053a7f0(3 - (uint)bVar2); // set blend mode (0,1,2,3?)
        FUN_00528010(); // render something
        FUN_00539250(); // post-process?
        FUN_00609890(1); // pop render state

        fVar10 = fVar10 - gTransitionBlendForward;
        uVar8 = uVar1;
        local_10 = uVar1;
    }

    // Call recursive helper to continue transition
    FUN_0052c380(local_10, uVar8, fVar10 - local_1c, !bCrossTransition);

    if (bCrossTransition) {
        // Second phase of cross-fade: reset state and apply reverse transition
        if (gRenderStateVar1 < 27) gRenderStateVar1 = 27;
        if (27 < gRenderStateVar2) gRenderStateVar2 = 27;
        gGlobalFlag1 = 1;

        uint uTemp = bVar2 ? 3 : 1;
        FUN_00417cf0(uTemp, 2, 2); // set rendering mode (different parameters)

        gFogShader = gDefaultFogShader;
        gFogEnabled = 0;
        gCurrentShader = gTransitionShaderB; // DAT_0121bba8

        if ((gTransitionShaderB == gShaderFogColor) || 
            (gTransitionShaderB == gShaderFogParams) ||
            (gTransitionShaderB == gShaderDepthTexture)) {
            gFogColorParam = FUN_0060a580(gTransitionShaderB, "fog_color");
            gFogParamsParam = FUN_0060a580(gCurrentShader, "fog_params");
            gDepthTextureParam = FUN_0060a580(gCurrentShader, "depth_texture");
        }

        if (gCurrentShaderSet == &gShaderState1) {
            FUN_0060a460(gCurrentShader);
            FUN_0060a460(gFogShader);
        }

        FUN_005388a0();
        FUN_0053a7f0(bVar2); // blend mode based on bVar2 (0/1)
        FUN_00528010();
        FUN_00539250();
        FUN_00417cf0(1,2,1);
        FUN_00609890(1);

        uVar1 = gTransitionZoneIds[iVar6 * 2]; // the second stored zone
        uVar7 = 0;
        do {
            if (gTransitionZoneIds[uVar7 * 2] == uVar1) {
                if (uVar7 < 20) {
                    gTransitionZoneFlags[uVar7 * 2] &= 0xfffffffc;
                }
                break;
            }
            uVar7++;
        } while (uVar7 < 20);

        uVar11 = gCurrentTransitionTo;
        uVar7 = gCurrentTransitionFrom;
        gCurrentTransitionTo = 0;
        gCurrentTransitionFrom = uVar1;
        FUN_00609340(0, uVar7, uVar11);

        if (gRenderStateVar1 < 27) gRenderStateVar1 = 27;
        if (27 < gRenderStateVar2) gRenderStateVar2 = 27;
        gGlobalFlag1 = 0;

        FUN_0052c380(uVar8, uVar1, local_1c, 1); // final transition step
    }

    // Final step: switch to destination zone if not already active
    uVar1 = gCurrentTransitionFrom;
    if (gCurrentTransitionFrom != destZoneId) {
        uVar8 = 0;
        do {
            if (gTransitionZoneIds[uVar8 * 2] == destZoneId) {
                if (uVar8 < 20) {
                    gTransitionZoneFlags[uVar8 * 2] &= 0xfffffffc;
                }
                break;
            }
            uVar8++;
        } while (uVar8 < 20);

        uVar11 = gCurrentTransitionTo;
        gCurrentTransitionFrom = destZoneId;
        gCurrentTransitionTo = 0;
        FUN_00609340(0, uVar1, uVar11);

        FUN_00609810(1);
        gFinalShader1 = gFinalShaderDefault; // DAT_012198fc & DAT_01219900?
        gFinalShader2 = gFinalShaderDefault2;
        gFinalState = 4; // _DAT_01219a6c

        if (gCurrentShaderSet == &gShaderState2) { // &DAT_01219940
            FUN_0060a460(gFinalShader1);
            FUN_0060a460(gFinalShader2);
        }

        FUN_00530a60();
        FUN_00530df0();
        FUN_00528070();
        FUN_00612e00();

        gFinalShader1 = 0;
        gFinalShader2 = 0;
        gFinalVar1 = 0;
        gFinalVar2 = 0;
        FUN_00609890(1);
    }
    return;
}
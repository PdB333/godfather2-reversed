// FUNC_NAME: setupScreenEffect
void setupScreenEffect(float* effectParams)
{
    float fVar1;
    int iVar2;
    uint32_t uVar3;
    uint32_t* puVar4;
    uint8_t* puVar5;
    uint32_t uVar6;
    uint32_t uVar7;
    uint32_t uVar8;
    bool bVar9;
    float fVar10;
    float fStack_20;
    float fStack_1c;
    float fStack_18;
    float fStack_14;

    // Clamp top bar height to minimum 168 (0xa8)
    if (gScreenTopBarHeight < 0xa8) {
        gScreenTopBarHeight = 0xa8;
    }
    // Also clamp bottom bar height; gScreenBottomBarHeight <= 0xa7? Actually: if (0xa7 < gScreenBottomBarHeight) set to 0xa8
    if (0xa7 < gScreenBottomBarHeight) {
        gScreenBottomBarHeight = 0xa8;
    }
    gScreenTopBarFlag = 0xf;                    // +0x117f3c78: flag for top bar
    
    // Update top bar to >= 0xbe (190)
    if (gScreenTopBarHeight < 0xbe) {
        gScreenTopBarHeight = 0xbe;
    }
    if (0xbd < gScreenBottomBarHeight) {
        gScreenBottomBarHeight = 0xbe;
    }
    gScreenBottomBarFlag = 0xf;                  // +0x117f3cd0: flag for bottom bar

    // Main effect block: only if effectParams[3] (duration?) is greater than threshold (DAT_00e2e780)
    if (gEffectThreshold <= effectParams[3]) {
        // Set horizontal bars
        if (gScreenLeftBarHeight < 0x16) {
            gScreenLeftBarHeight = 0x16;
        }
        if (0x16 < gScreenRightBarHeight) {
            gScreenRightBarHeight = 0x16;
        }
        gScreenLeftBarFlag = 1;                  // +0x117f3a30: left bar flag

        if (gScreenLeftBarHeight < 7) {
            gScreenLeftBarHeight = 7;
        }
        if (7 < gScreenRightBarHeight) {
            gScreenRightBarHeight = 7;
        }
        gScreenRightBarFlag = 0;                 // +0x117f39f4: right bar flag

        if (gScreenLeftBarHeight < 0x19) {
            gScreenLeftBarHeight = 0x19;
        }
        if (0x19 < gScreenRightBarHeight) {
            gScreenRightBarHeight = 0x19;
        }
        gScreenLeftBarMode = 5;                  // +0x117f3a3c

        if (gScreenLeftBarHeight < 0x18) {
            gScreenLeftBarHeight = 0x18;
        }
        if (0x18 < gScreenRightBarHeight) {
            gScreenRightBarHeight = 0x18;
        }
        gScreenRightBarMode = 0;                 // +0x117f3a38

        if (gScreenLeftBarHeight < 0xf) {
            gScreenLeftBarHeight = 0xf;
        }
        if (0xf < gScreenRightBarHeight) {
            gScreenRightBarHeight = 0xf;
        }
        gScreenLeftBarOffset = 0;                // +0x117f3a14

        if (gScreenLeftBarHeight < 0x1b) {
            gScreenLeftBarHeight = 0x1b;
        }
        if (0x1a < gScreenRightBarHeight) {
            gScreenRightBarHeight = 0x1b;
        }
        gScreenRightBarOffset = 1;               // +0x117f3a44

        // Enable some state (probably fade/overlay)
        setEffectState(1, 2, 1);                  // FUN_00417cf0(1,2,1)
        setRenderMode(1);                          // FUN_00609890(1)

        iVar2 = gCurrentModeIndex;                 // DAT_01218e60
        uVar6 = 0;
        do {
            if (gModeIndexMap[uVar6 * 2] == gCurrentModeIndex) {
                if (uVar6 < 20) {
                    gModeIndexMap[uVar6 * 2 + 1] &= 0xfffffffc; // clear bit0, 1
                }
                break;
            }
            uVar6 = uVar6 + 1;
        } while (uVar6 < 20);

        uVar3 = gRenderTargetWidth;                 // DAT_011f38f4
        uVar6 = gRenderTargetHeight;                // DAT_011f38f0
        gRenderTargetHeight = iVar2;
        gRenderTargetWidth = 0;
        updateRenderTarget(0, uVar6, uVar3);         // FUN_00609340(0, oldHeight, oldWidth)

        iVar2 = gSomeRenderFlag;                     // DAT_011f3914
        bVar9 = gSomeRenderFlag2 != 0;               // DAT_011f3910
        gSomeRenderFlag2 = 0;
        gSomeRenderFlag = 0;
        if (bVar9 || (iVar2 != 0)) {
            (*(code**)(*gDevicePtr + 0x9c))(gDevicePtr, 0); // reset device or something
        }

        setClearColor(0, 0, 0, 1.0f, 1.0f);          // FUN_0060db60(0,0,0,1.0,1.0)
        uVar6 = gNewModeIndex;                       // DAT_01218ea8

        // Again clamp and set bars for new mode
        if (gScreenTopBarHeight < 0xa8) {
            gScreenTopBarHeight = 0xa8;
        }
        if (0xa7 < gScreenBottomBarHeight) {
            gScreenBottomBarHeight = 0xa8;
        }
        gScreenTopBarFlag = 1;

        if (gScreenTopBarHeight < 0xbe) {
            gScreenTopBarHeight = 0xbe;
        }
        if (0xbd < gScreenBottomBarHeight) {
            gScreenBottomBarHeight = 0xbe;
        }
        gScreenBottomBarFlag = 1;

        uVar7 = 0;
        do {
            if (gModeIndexMap[uVar7 * 2] == gNewModeIndex) {
                if (uVar7 < 20) {
                    gModeIndexMap[uVar7 * 2 + 1] &= 0xfffffffc;
                }
                break;
            }
            uVar7 = uVar7 + 1;
        } while (uVar7 < 20);

        uVar3 = gRenderTargetWidth;
        iVar2 = gRenderTargetHeight;
        gRenderTargetHeight = uVar6;
        gRenderTargetWidth = 0;
        updateRenderTarget(0, iVar2, uVar3);

        setClearColor(0, 0, 0, 1.0f, 1.0f);

        // Set some screen coordinates for overlay
        gOverlayLeft = gOverlayHorizontalCenter;       // DAT_01219954 = DAT_012198f8
        gOverlayRight = gOverlayVerticalCenter;        // DAT_01219950 = DAT_01219908
        gOverlayMode = 6;                              // _DAT_01219a6c = 6

        if (gOverlayStatePtr == &gOverlayDefaultState) { // DAT_012058e8 == &DAT_01219940
            releaseOverlay(gOverlayHorizontalCenter);   // FUN_0060a460
            releaseOverlay(gOverlayVerticalCenter);
        }

        initializeOverlayCoords();                     // FUN_00530a60()
        updateOverlayVertices();                       // FUN_00530df0()

        // Build a 2D quad (for overlay?)
        fStack_20 = gDefaultFloat;                     // DAT_00e2b1a4
        fStack_1c = gDefaultFloat;
        fStack_18 = gDefaultFloat;
        fStack_14 = gDefaultFloat;

        initOverlayBuffer();                           // FUN_005311d0()

        puVar4 = (uint32_t*)allocateMemory(0xd, 4, 0, 1, 0); // FUN_0060cd00(size?, align?, etc)
        uVar3 = gSomeColorFloat;                       // DAT_00e2eff4
        fVar1 = gDefaultFloat;
        if (puVar4 != 0) {
            puVar4[0] = uVar3;
            puVar4[1] = uVar3;
            puVar4[2] = fVar1;
            puVar4[3] = uVar3;
            puVar4[4] = fVar1;
            puVar4[5] = fVar1;
            puVar4[6] = uVar3;
            puVar4[7] = fVar1;
            pushAllocation();                          // FUN_0060cde0()
        }

        finalizeRendering();                           // FUN_00612e00()

        gOverlayRight = 0;
        gOverlayLeft = 0;
        gOverlayTop = 0;                               // _DAT_012199e4
        gOverlayBottom = 0;                            // _DAT_012199e8

        setRenderMode(1);                              // FUN_00609890(1)

        uVar7 = gLastModeIndex;                        // DAT_01218ed8
        uVar6 = gRenderTargetHeight;

        if ((effectParams[5] & 1) == 0) {
            uVar8 = 0;
            do {
                if (gModeIndexMap[uVar8 * 2] == gLastModeIndex) {
                    if (uVar8 < 20) {
                        gModeIndexMap[uVar8 * 2 + 1] &= 0xfffffffc;
                    }
                    break;
                }
                uVar8 = uVar8 + 1;
            } while (uVar8 < 20);

            uVar3 = gRenderTargetWidth;
            gRenderTargetHeight = uVar7;
            gRenderTargetWidth = 0;
            updateRenderTarget(0, uVar6, uVar3);

            resetOverlayData();                        // FUN_0053c6f0()
            resetOverlayTextures();                    // FUN_0053c670()

            if (*gSomeTexturePtr != 0) {
                releaseTexture();                      // FUN_006063b0()
            }

            // Calculate aspect ratio correction using the previous render target height
            float aspectX, aspectY;
            if (uVar6 < 0x1000) {
                puVar5 = &gTextureInfoArray + uVar6 * 0x38;
            } else {
                puVar5 = 0;
            }
            fStack_20 = gBaseAspectRatio / (float)*(uint16_t*)(puVar5 + 2); // DAT_00e2b198 / width

            if (uVar6 < 0x1000) {
                puVar5 = &gTextureInfoArray + uVar6 * 0x38;
            } else {
                puVar5 = 0;
            }
            fStack_1c = gBaseAspectRatio / (float)*(uint16_t*)(puVar5 + 4); // height

            fStack_14 = gScreenHeight - fStack_1c;     // DAT_00e44564 - fStack_1c
            fStack_18 = fStack_20;

            if (gSomePostEffectParam != 0) {            // DAT_0121be7c[7]
                applyPostEffect(gRenderTargetPtr, gSomePostEffectParam, &fStack_20); // FUN_0060add0
            }

            renderOverlayQuad();                        // FUN_00528070()
            finalizeRendering();                        // FUN_00612e00()

            gRenderTargetPtr = 0;                       // DAT_0121bc20
            gRenderTargetPtr2 = 0;                      // DAT_0121bc24

            if ((effectParams[5] & 2) != 0) {
                setEffectState(3, 2, 2);                // FUN_00417cf0(3,2,2)

                gOverlayLeft = gOverlayHorizontalCenter2; // DAT_012198fc
                gOverlayRight = gOverlayVerticalCenter2;  // DAT_01219900
                gOverlayMode = 4;

                if (gOverlayStatePtr == &gOverlayDefaultState) {
                    releaseOverlay(gOverlayHorizontalCenter2);
                    releaseOverlay(gOverlayVerticalCenter2);
                }

                initializeOverlayCoords();
                setRenderTexture(uVar6, 0x110000);       // FUN_00606e60(uVar6, 0x110000)
                updateOverlayVertices();
                renderOverlayQuad();
                finalizeRendering();

                gOverlayRight = 0;
                gOverlayLeft = 0;
                gOverlayTop = 0;
                gOverlayBottom = 0;
            }

            setRenderMode(1);
        }

        // Second main block (outside the flag check but inside effect duration block)
        uVar6 = gRenderTargetHeight;

        if (gScreenTopBarHeight < 0xa8) {
            gScreenTopBarHeight = 0xa8;
        }
        if (0xa7 < gScreenBottomBarHeight) {
            gScreenBottomBarHeight = 0xa8;
        }
        gScreenTopBarFlag = 0xf;

        if (gScreenTopBarHeight < 0xbe) {
            gScreenTopBarHeight = 0xbe;
        }
        if (0xbd < gScreenBottomBarHeight) {
            gScreenBottomBarHeight = 0xbe;
        }
        gScreenBottomBarFlag = 0xf;

        setPostEffectMode();                            // FUN_004e3a70()
        setEffectState(1, 2, 6);                        // FUN_00417cf0(1,2,6)

        gSomeFloat1 = gOverlayVerticalCenter;            // DAT_01125ba0 = DAT_01219908
        gSomeIndex = 0;                                  // DAT_01125d78 = 0
        gSomeFloat2 = gSomeGlobalTexture;                // DAT_01125ba4 = DAT_01125c34

        if (gOverlayStatePtr == &ptrOverlayDefaultState) { // DAT_012058e8 == &PTR_PTR_01125b90
            releaseOverlay(gSomeGlobalTexture);
            releaseOverlay(gSomeFloat1);
        }

        startOverlayAnimation();                         // FUN_0053cc10()

        // Scale the effect parameters
        fVar10 = effectParams[3] * gScaleFactor;         // DAT_00e35654
        fVar1 = effectParams[3];
        effectParams[0] = fVar10 * effectParams[0];
        effectParams[1] = fVar10 * effectParams[1];
        effectParams[2] = fVar10 * effectParams[2];
        effectParams[3] = fVar10 * effectParams[3];
        effectParams[3] = fVar1;                         // restore original duration? Seems odd

        if (effectParams[6] == 0.0f) {
            effectParams[3] = 0.0f;
        } else {
            effectParams[3] = fVar10;
        }

        if (gSomeAnimationFlag != 0) {                   // &DAT_01125c38[ index*11 ]
            applyAnimation(gSomeFloat2, gSomeAnimationFlag, effectParams); // FUN_0060add0
        }

        // Compute aspect ratio for a second overlay
        if (uVar6 < 0x1000) {
            puVar5 = &gTextureInfoArray + uVar6 * 0x38;
        } else {
            puVar5 = 0;
        }
        fStack_20 = (effectParams[4] * gAspectFactor) / (float)*(uint16_t*)(puVar5 + 2); // DAT_00e2cd54

        if (uVar6 < 0x1000) {
            puVar5 = &gTextureInfoArray + uVar6 * 0x38;
        } else {
            puVar5 = 0;
        }
        fStack_1c = (effectParams[4] * gAspectFactor) / (float)*(uint16_t*)(puVar5 + 4);

        fStack_14 = gScreenHeight - fStack_1c;
        fStack_18 = fStack_20;

        if (gSecondAnimationFlag != 0) {                 // &DAT_01125c48[ index*11 ]
            applyAnimation(gSomeFloat2, gSecondAnimationFlag, &fStack_20);
        }

        if ((uVar6 != 0xffffffff) && (uVar6 < 0x1000)) {
            iVar2 = uVar6 * 0x38;
            if ((&gTextureInfoArray + iVar2 != 0) && ((byte)gTextureInfoArray[iVar2] < 4)) {
                if (*(int*)(&gTextureInfoArray + iVar2 + 0x14) != 0) { // offset 0x14 in texture info
                    setRenderTexture(*(int*)(&gTextureInfoArray + iVar2 + 0x14), 0x100000);
                }
                *(uint32_t*)(&gTextureInfoArray + iVar2 + 0x04) = 
                    *(uint32_t*)(&gTextureInfoArray + iVar2 + 0x04) & 0xfc9c8fff | 0x100000;
                recomputeHwSettings();                  // FUN_006189c0()
            }
        }

        finalizeOverlay();                              // FUN_0053cdc0()

        // Allocate another quad (same pattern)
        puVar4 = (uint32_t*)allocateMemory(0xd, 4, 0, 1, 0);
        uVar3 = gSomeColorFloat;
        fVar1 = gDefaultFloat;
        if (puVar4 != 0) {
            puVar4[0] = uVar3;
            puVar4[1] = uVar3;
            puVar4[2] = fVar1;
            puVar4[3] = uVar3;
            puVar4[4] = fVar1;
            puVar4[5] = fVar1;
            puVar4[6] = uVar3;
            puVar4[7] = fVar1;
            pushAllocation();
        }

        finalizeRendering();

        gSomeFloat1 = 0;
        gSomeFloat2 = 0;
    }

    // Final clamp and set (always executed)
    if (gScreenLeftBarHeight < 0x16) {
        gScreenLeftBarHeight = 0x16;
    }
    if (0x16 < gScreenRightBarHeight) {
        gScreenRightBarHeight = 0x16;
    }
    gScreenLeftBarFlag = 1;

    if (gScreenLeftBarHeight < 7) {
        gScreenLeftBarHeight = 7;
    }
    if (7 < gScreenRightBarHeight) {
        gScreenRightBarHeight = 7;
    }
    gScreenRightBarFlag = 1;

    if (gScreenLeftBarHeight < 0xe) {
        gScreenLeftBarHeight = 0xe;
    }
    if (0xe < gScreenRightBarHeight) {
        gScreenRightBarHeight = 0xe;
    }
    gScreenLeftBarFlag2 = 1;                          // _DAT_011f3a10

    if (gScreenLeftBarHeight < 0x19) {
        gScreenLeftBarHeight = 0x19;
    }
    if (0x19 < gScreenRightBarHeight) {
        gScreenRightBarHeight = 0x19;
    }
    gScreenLeftBarMode = 7;

    if (gScreenLeftBarHeight < 0x18) {
        gScreenLeftBarHeight = 0x18;
    }
    if (0x18 < gScreenRightBarHeight) {
        gScreenRightBarHeight = 0x18;
    }
    gScreenRightBarMode = 0;

    if (gScreenLeftBarHeight < 0xf) {
        gScreenLeftBarHeight = 0xf;
    }
    if (0xf < gScreenRightBarHeight) {
        gScreenRightBarHeight = 0xf;
    }
    gScreenLeftBarOffset = 0;

    if (gScreenLeftBarHeight < 0x1b) {
        gScreenLeftBarHeight = 0x1b;
    }
    if (0x1a < gScreenRightBarHeight) {
        gScreenRightBarHeight = 0x1b;
    }
    gScreenRightBarOffset = 0;

    setEffectState(1, 5, 6);                          // FUN_00417cf0(1,5,6)
    return;
}
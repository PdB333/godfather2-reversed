// FUNC_NAME: PresentationManager::updateScreenEffect
void PresentationManager::updateScreenEffect(float *viewportParams)
{
    float fVar1;
    int iVar2;
    unsigned int uVar3;
    unsigned int *puVar4;
    unsigned char *puVar5;
    unsigned int uVar6;
    unsigned int uVar7;
    unsigned int uVar8;
    bool bVar9;
    float fVar10;
    float fStack_20;
    float fStack_1c;
    float fStack_18;
    float fStack_14;

    // Clamp screen width (0xa8=168, 0xbe=190)
    if (gScreenWidth < 0xa8) {
        gScreenWidth = 0xa8;
    }
    if (0xa7 < gScreenWidthAlt) {
        gScreenWidthAlt = 0xa8;
    }
    gScreenWidthFlag = 0xf;
    if (gScreenWidth < 0xbe) {
        gScreenWidth = 0xbe;
    }
    if (0xbd < gScreenWidthAlt) {
        gScreenWidthAlt = 0xbe;
    }
    gScreenWidthFlagAlt = 0xf;

    if (gSomeScale <= viewportParams[3]) {
        // Clamp screen height (0x16=22, 0x1b=27, etc.)
        if (gScreenHeight < 0x16) {
            gScreenHeight = 0x16;
        }
        if (0x16 < gScreenHeightAlt) {
            gScreenHeightAlt = 0x16;
        }
        gScreenHeightFlag = 1;
        if (gScreenHeight < 7) {
            gScreenHeight = 7;
        }
        if (7 < gScreenHeightAlt) {
            gScreenHeightAlt = 7;
        }
        gScreenHeightFlag2 = 0;
        if (gScreenHeight < 0x19) {
            gScreenHeight = 0x19;
        }
        if (0x19 < gScreenHeightAlt) {
            gScreenHeightAlt = 0x19;
        }
        gScreenHeightFlag3 = 5;
        if (gScreenHeight < 0x18) {
            gScreenHeight = 0x18;
        }
        if (0x18 < gScreenHeightAlt) {
            gScreenHeightAlt = 0x18;
        }
        gScreenHeightFlag4 = 0;
        if (gScreenHeight < 0xf) {
            gScreenHeight = 0xf;
        }
        if (0xf < gScreenHeightAlt) {
            gScreenHeightAlt = 0xf;
        }
        gScreenHeightFlag5 = 0;
        if (gScreenHeight < 0x1b) {
            gScreenHeight = 0x1b;
        }
        if (0x1a < gScreenHeightAlt) {
            gScreenHeightAlt = 0x1b;
        }
        gScreenHeightFlag6 = 1;

        // Set video mode
        FUN_00417cf0(1, 2, 1);
        FUN_00609890(1);

        iVar2 = gCurrentRenderTarget;
        uVar6 = 0;
        do {
            if (gRenderTargetArray[uVar6 * 2] == gCurrentRenderTarget) {
                if (uVar6 < 0x14) {
                    gRenderTargetArray[uVar6 * 2 + 1] &= 0xfffffffc;
                }
                break;
            }
            uVar6++;
        } while (uVar6 < 0x14);

        uVar3 = gRenderTargetFlag;
        uVar6 = gRenderTargetCurrent;
        gRenderTargetCurrent = iVar2;
        gRenderTargetFlag = 0;
        FUN_00609340(0, uVar6, uVar3);

        iVar2 = gSomeOtherTarget;
        bVar9 = gSomeOtherFlag != 0;
        gSomeOtherFlag = 0;
        gSomeOtherTarget = 0;
        if ((bVar9) || (iVar2 != 0)) {
            (*(code **)(*gSomeObject + 0x9c))(gSomeObject, 0);
        }

        FUN_0060db60(0, 0, 0, 0x3f800000, 0x3f800000);

        uVar6 = gAnotherRenderTarget;
        if (gScreenWidth < 0xa8) {
            gScreenWidth = 0xa8;
        }
        if (0xa7 < gScreenWidthAlt) {
            gScreenWidthAlt = 0xa8;
        }
        gScreenWidthFlag = 1;
        if (gScreenWidth < 0xbe) {
            gScreenWidth = 0xbe;
        }
        if (0xbd < gScreenWidthAlt) {
            gScreenWidthAlt = 0xbe;
        }
        gScreenWidthFlagAlt = 1;

        uVar7 = 0;
        do {
            if (gRenderTargetArray[uVar7 * 2] == gAnotherRenderTarget) {
                if (uVar7 < 0x14) {
                    gRenderTargetArray[uVar7 * 2 + 1] &= 0xfffffffc;
                }
                break;
            }
            uVar7++;
        } while (uVar7 < 0x14);

        uVar3 = gRenderTargetFlag;
        iVar2 = gRenderTargetCurrent;
        gRenderTargetCurrent = uVar6;
        gRenderTargetFlag = 0;
        FUN_00609340(0, iVar2, uVar3);

        FUN_0060db60(0, 0, 0, 0x3f800000, 0x3f800000);

        gSomeWidth = gSourceWidth;
        gSomeHeight = gSourceHeight;
        gSomeCount = 6;

        if (gSomeObject2 == (undefined **)&gSomeStruct) {
            FUN_0060a460(gSourceWidth);
            FUN_0060a460(gSomeHeight);
        }

        FUN_00530a60();
        FUN_00530df0();

        fStack_20 = gDefaultFloat;
        fStack_1c = gDefaultFloat;
        fStack_18 = gDefaultFloat;
        fStack_14 = gDefaultFloat;
        FUN_005311d0();

        puVar4 = (unsigned int *)FUN_0060cd00(0xd, 4, 0, 1, 0);
        uVar3 = gSomeColor;
        fVar1 = gDefaultFloat;
        if (puVar4 != (unsigned int *)0x0) {
            *puVar4 = gSomeColor;
            puVar4[1] = uVar3;
            puVar4[2] = fVar1;
            puVar4[3] = uVar3;
            puVar4[4] = fVar1;
            puVar4[5] = fVar1;
            puVar4[6] = uVar3;
            puVar4[7] = fVar1;
            FUN_0060cde0();
        }

        FUN_00612e00();

        gSomeHeight = 0;
        gSomeWidth = 0;
        gSomeFlag1 = 0;
        gSomeFlag2 = 0;

        FUN_00609890(1);

        uVar7 = gYetAnotherTarget;
        uVar6 = gRenderTargetCurrent;

        if ((viewportParams[5] & 1) == 0) {
            uVar8 = 0;
            do {
                if (gRenderTargetArray[uVar8 * 2] == gYetAnotherTarget) {
                    if (uVar8 < 0x14) {
                        gRenderTargetArray[uVar8 * 2 + 1] &= 0xfffffffc;
                    }
                    break;
                }
                uVar8++;
            } while (uVar8 < 0x14);

            uVar3 = gRenderTargetFlag;
            gRenderTargetCurrent = uVar7;
            gRenderTargetFlag = 0;
            FUN_00609340(0, uVar6, uVar3);

            FUN_0053c6f0();
            FUN_0053c670();

            if (*gSomeGlobalPtr != 0) {
                FUN_006063b0();
            }

            if (uVar6 < 0x1000) {
                puVar5 = &gStreamBuffer + uVar6 * 0x38;
            } else {
                puVar5 = (unsigned char *)0x0;
            }
            fStack_20 = gSomeAspect / (float)*(unsigned short *)(puVar5 + 2);

            if (uVar6 < 0x1000) {
                puVar5 = &gStreamBuffer + uVar6 * 0x38;
            } else {
                puVar5 = (unsigned char *)0x0;
            }
            fStack_1c = gSomeAspect / (float)*(unsigned short *)(puVar5 + 4);
            fStack_14 = gScreenBottom - fStack_1c;
            fStack_18 = fStack_20;

            if (gSomeCallback[7] != 0) {
                FUN_0060add0(gSomeCallbackBase, gSomeCallback[7], &fStack_20);
            }

            FUN_00528070();
            FUN_00612e00();

            gSomeCallbackBase = 0;
            gSomeCallback[0] = 0;

            if ((viewportParams[5] & 2) != 0) {
                FUN_00417cf0(3, 2, 2);

                gSomeWidth = gSourceWidth2;
                gSomeHeight = gSourceHeight2;
                gSomeCount = 4;

                if (gSomeObject2 == (undefined **)&gSomeStruct) {
                    FUN_0060a460(gSourceWidth2);
                    FUN_0060a460(gSomeHeight);
                }

                FUN_00530a60();
                FUN_00606e60(uVar6, 0x110000);
                FUN_00530df0();
                FUN_00528070();
                }

                FUN_00612e00();

                gSomeHeight = 0;
                // Note: missing assignment to gSomeWidth? original code had DAT_01219950 = DAT_012198fc and DAT_01219954 = DAT_01219900, which correspond to gSomeHeight and gSomeWidth respectively here, then later set to 0 and DAT_01219954=0, so it's fine though redundant after setting to 0 later but okay.
                gSomeWidth = 0;
                gSomeFlag1 = 0;
                gSomeFlag2 = 0;
            }

            FUN_00609890(1);
        }

        uVar6 = gRenderTargetCurrent;

        if (gScreenWidth < 0xa8) {
            gScreenWidth = 0xa8;
        }
        if (0xa7 < gScreenWidthAlt) {
            gScreenWidthAlt = 0xa8;
        }
        gScreenWidthFlag = 0xf;
        if (gScreenWidth < 0xbe) {
            gScreenWidth = 0xbe;
        }
        if (0xbd < gScreenWidthAlt) {
            gScreenWidthAlt = 0xbe;
        }
        gScreenWidthFlagAlt = 0xf;

        FUN_004e3a70();
        FUN_00417cf0(1, 2, 6);

        gSomeVar1 = gSourceHeight;
        gSomeIndex = 0;
        gSomeVar2 = gSomeBufferPtr;
        if (gSomeObject2 == &PTR_PTR_01125b90) {
            FUN_0060a460(gSomeBufferPtr);
            FUN_0060a460(gSomeVar1);
        }

        FUN_0053cc10();

        fVar10 = viewportParams[3] * gSomeMultiplier;
        fVar1 = viewportParams[3];

        viewportParams[0] = fVar10 * viewportParams[0];
        viewportParams[1] = fVar10 * viewportParams[1];
        viewportParams[2] = fVar10 * viewportParams[2];
        viewportParams[3] = fVar10 * viewportParams[3];
        viewportParams[3] = fVar1;

        if (viewportParams[6] == 0.0f) {
            viewportParams[3] = 0.0f;
        } else {
            viewportParams[3] = fVar10;
        }

        if (gCallbackArray[gSomeIndex * 0xb] != 0) {
            FUN_0060add0(gSomeVar2, gCallbackArray[gSomeIndex * 0xb], viewportParams);
        }

        if (uVar6 < 0x1000) {
            puVar5 = &gStreamBuffer + uVar6 * 0x38;
        } else {
            puVar5 = (unsigned char *)0x0;
        }
        fStack_20 = (viewportParams[4] * gSomeScale2) / (float)*(unsigned short *)(puVar5 + 2);

        if (uVar6 < 0x1000) {
            puVar5 = &gStreamBuffer + uVar6 * 0x38;
        } else {
            puVar5 = (unsigned char *)0x0;
        }
        fStack_1c = (viewportParams[4] * gSomeScale2) / (float)*(unsigned short *)(puVar5 + 4);
        fStack_14 = gScreenBottom - fStack_1c;
        fStack_18 = fStack_20;

        if (gCallbackArray2[gSomeIndex * 0xb] != 0) {
            FUN_0060add0(gSomeVar2, gCallbackArray2[gSomeIndex * 0xb], &fStack_20);
        }

        if ((uVar6 != 0xffffffff) && (uVar6 < 0x1000)) {
            iVar2 = uVar6 * 0x38;
            if ((&gStreamBuffer + iVar2 != (byte *)0x0) && ((byte)(&gStreamBuffer)[iVar2] < 4)) {
                if (*(int *)(&gStreamBuffer + iVar2 + 0x1c) != 0) {
                    FUN_00606e60(*(int *)(&gStreamBuffer + iVar2 + 0x1c), 0x100000);
                }
                *(unsigned int *)(&gStreamBuffer + iVar2 + 0xc) &= 0xfc9c8fff | 0x100000;
                FUN_006189c0();
            }
        }

        FUN_0053cdc0();

        puVar4 = (unsigned int *)FUN_0060cd00(0xd, 4, 0, 1, 0);
        uVar3 = gSomeColor;
        fVar1 = gDefaultFloat;
        if (puVar4 != (unsigned int *)0x0) {
            *puVar4 = gSomeColor;
            puVar4[1] = uVar3;
            puVar4[2] = fVar1;
            puVar4[3] = uVar3;
            puVar4[4] = fVar1;
            puVar4[5] = fVar1;
            puVar4[6] = uVar3;
            puVar4[7] = fVar1;
            FUN_0060cde0();
        }

        FUN_00612e00();

        gSomeVar1 = 0;
        gSomeVar2 = 0;
    }

    // Final clamping and mode set (outside the if block)
    if (gScreenHeight < 0x16) {
        gScreenHeight = 0x16;
    }
    if (0x16 < gScreenHeightAlt) {
        gScreenHeightAlt = 0x16;
    }
    gScreenHeightFlag = 1;
    if (gScreenHeight < 7) {
        gScreenHeight = 7;
    }
    if (7 < gScreenHeightAlt) {
        gScreenHeightAlt = 7;
    }
    gScreenHeightFlag2 = 1;
    if (gScreenHeight < 0xe) {
        gScreenHeight = 0xe;
    }
    if (0xe < gScreenHeightAlt) {
        gScreenHeightAlt = 0xe;
    }
    gScreenHeightFlag7 = 1;
    if (gScreenHeight < 0x19) {
        gScreenHeight = 0x19;
    }
    if (0x19 < gScreenHeightAlt) {
        gScreenHeightAlt = 0x19;
    }
    gScreenHeightFlag3 = 7;
    if (gScreenHeight < 0x18) {
        gScreenHeight = 0x18;
    }
    if (0x18 < gScreenHeightAlt) {
        gScreenHeightAlt = 0x18;
    }
    gScreenHeightFlag4 = 0;
    if (gScreenHeight < 0xf) {
        gScreenHeight = 0xf;
    }
    if (0xf < gScreenHeightAlt) {
        gScreenHeightAlt = 0xf;
    }
    gScreenHeightFlag5 = 0;
    if (gScreenHeight < 0x1b) {
        gScreenHeight = 0x1b;
    }
    if (0x1a < gScreenHeightAlt) {
        gScreenHeightAlt = 0x1b;
    }
    gScreenHeightFlag6 = 0;
    FUN_00417cf0(1, 5, 6);
    return;
}
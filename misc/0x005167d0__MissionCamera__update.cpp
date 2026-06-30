// FUNC_NAME: MissionCamera::update

void MissionCamera::update() {
    // 0x005167d0 - Handles camera transition and mission state setup
    // This function is called when a camera transition timer (DAT_012066d0) is active
    // It interpolates camera values, sets up fog and depth textures, and manages input states

    float fVar12;
    uint uVar1, uVar5, uVar6, uVar7, uVar8, uVar9, uVar10;
    int iVar2, iVar4;
    undefined4 uVar13;
    bool bVar11, local_59;

    uVar13 = 0;

    // Check if camera transition is active
    if ((gCameraTransitionTimer != 0.0f) && (gCameraThreshold <= gCameraInterpTarget) && (gCameraCurrentValue != 0.0f)) {
        // Compute interpolation factor
        fVar12 = gSomeFloat / gCameraTransitionTimer;
        gCameraInterpX *= fVar12;   // +0x2c
        gCameraInterpY *= fVar12;   // +0x30
        gCameraInterpZ *= fVar12;   // +0x34
        gCameraInterpTarget *= fVar12;  // +0x38

        if ((gCameraThreshold <= gCameraInterpTarget) && ((gCameraFlags & 0x10000000) == 0)) {
            // Extract flags for direction and behavior
            uVar6 = gCameraFlags >> 0xd;
            uVar7 = gCameraFlags >> 0x11;
            uVar8 = gCameraFlags >> 0x12;
            uVar9 = gCameraFlags >> 0x13;
            uVar5 = gCameraFlags >> 0xe;
            uVar10 = gCameraFlags >> 0xf;
            uVar1 = gCameraFlags & 0x10000;

            // Determine camera speed index
            if ((gCameraFlags & 0x200000) == 0) {
                iVar4 = ((gCameraFlags & 0x100000) != 0) + 1;
            } else {
                iVar4 = 4;
            }

            local_59 = gSomeBool != 1;
            uVar13 = gBaseTarget;
            if ((uVar6 & 1) != 0) {
                // Use target from array based on speed index
                uVar13 = gTargetArray[*(int *)(gTargetIndexArray + iVar4 * 4) * 2];
            }

            if (gTransitionInProgress == '\0') {
                // First-time setup for the transition
                if ((uVar5 & 1) == 0) && local_59) {
                    someFadeFunction();
                    local_59 = (uVar5 & 1) != 0;
                }

                iVar2 = gInputState1;
                bVar11 = gInputState0 != 0;
                gInputState0 = 0;
                gInputState1 = 0;
                if (bVar11 || (iVar2 != 0)) {
                    // Call virtual function on camera object
                    (*(code **)(*gCameraObject + 0x9c))(gCameraObject, 0);
                }

                // Set viewport limits (min/max)
                if (gViewportMin < 0x16) {
                    gViewportMin = 0x16;
                }
                if (0x16 < gViewportMax) {
                    gViewportMax = 0x16;
                }
                gSomeFlag1 = 1;

                setViewport(nullptr, 0);
                setViewportOrigin(nullptr, 0);

                if (gViewportMin < 0x19) {
                    gViewportMin = 0x19;
                }
                if (0x19 < gViewportMax) {
                    gViewportMax = 0x19;
                }
                gSomeFlag2 = 5;

                if (gViewportMin < 0x18) {
                    gViewportMin = 0x18;
                }
                if (0x18 < gViewportMax) {
                    gViewportMax = 0x18;
                }
                gSomeFlag3 = 0;

                if (gViewportMin < 0xf) {
                    gViewportMin = 0xf;
                }
                if (0xf < gViewportMax) {
                    gViewportMax = 0xf;
                }
                gSomeFlag4 = 0;

                setSomeMode(1);
                setSomeOtherMode(1, 5, 6);

                // Determine camera activation flags
                if ((uVar6 & 1) == 0) {
                    gCameraActivationFlags = 1;
                } else {
                    gCameraActivationFlags = 2;
                    if ((uVar10 & 1) != 0) {
                        gCameraActivationFlags = 10;
                    }
                    if ((uVar7 & 1) == 0) {
                        if ((uVar8 & 1) != 0) {
                            gCameraActivationFlags |= 0x20;
                        }
                    } else if ((uVar8 & 1) != 0) {
                        gCameraActivationFlags |= 0x40;
                    }
                    if ((uVar9 & 1) != 0) {
                        gCameraActivationFlags |= 0x80;
                    }
                    if (uVar1 != 0) {
                        gCameraActivationFlags |= 0x10;
                    }
                    if (iVar4 == 1) {
                        gCameraActivationFlags |= 0x100;
                    } else if (iVar4 == 2) {
                        gCameraActivationFlags |= 0x200;
                    } else if (iVar4 == 4) {
                        gCameraActivationFlags |= 0x400;
                    }
                }

                gCameraCurrentMaterial = gDefaultMaterial;
                if ((gCameraActivationFlags & 1) == 0) {
                    gCameraExtraParam = (gCameraActivationFlags >> 4 & 8) + (gCameraActivationFlags >> 5 & 2) + (gCameraActivationFlags >> 3 & 2) + 2 + (gCameraActivationFlags >> 3 & 1);
                } else {
                    gCameraExtraParam = 0;
                }

                gCameraFogMaterial = gFogMaterialArray[gCameraExtraParam];

                if ((gCameraActivationFlags & 2) != 0) {
                    gCameraCurrentMaterial = gAlternativeMaterial;
                }

                // Retrieve fog shader parameters if material matches known ones
                if ((gCameraFogMaterial == gFogMaterial1) || (gCameraFogMaterial == gFogMaterial2) || (gCameraFogMaterial == gFogMaterial3)) {
                    gFogColorHandle = getShaderParameter(gCameraFogMaterial, "fog_color");
                    gFogParamsHandle = getShaderParameter(gCameraFogMaterial, "fog_params");
                    gDepthTextureHandle = getShaderParameter(gCameraFogMaterial, "depth_texture");
                }

                // Release previous materials if they match a specific pattern
                if (gPreviousMaterial == &gDefaultMaterialStruct) {
                    releaseMaterial(gCameraFogMaterial);
                    releaseMaterial(gCameraCurrentMaterial);
                }

                setShaderFlag(uVar13, 0x200000);

                // Setup rendering state
                setupRenderState1();
                setupRenderState2();
                setupRenderState3();
                setupRenderState4();
                setupRenderState5(gCameraCurrentValue);
                setupRenderState6();

                // Fade function based on camera direction
                if ((uVar6 & 1) == 0) {
                    someFadeIn();
                } else {
                    someFadeOut();
                }

                setupRenderState7();

                uVar3 = gInputState1;  // likely unused, stored for later
                uVar13 = gInputState0;
                gInputState0 = gSomeInputState;
                if (gSomeOtherPointer != 0) {
                    gInputState0 = *(int *)(gSomeOtherPointer + 0x170);
                }
                gInputState1 = 0;

                setInputState(4, uVar13, uVar3);

                // Second set of viewport limits (larger)
                if (gViewportMin < 0x16) {
                    gViewportMin = 0x16;
                }
                if (0x16 < gViewportMax) {
                    gViewportMax = 0x16;
                }
                gSomeFlag1 = 1;

                setViewport(nullptr, 1);
                setViewportOrigin(nullptr, 1);

                if (gViewportMin < 0x19) {
                    gViewportMin = 0x19;
                }
                if (0x19 < gViewportMax) {
                    gViewportMax = 0x19;
                }
                gSomeFlag2 = 7;

                if (gViewportMin < 0x18) {
                    gViewportMin = 0x18;
                }
                if (0x18 < gViewportMax) {
                    gViewportMax = 0x18;
                }
                gSomeFlag3 = 0;

                if (gViewportMin < 0xf) {
                    gViewportMin = 0xf;
                }
                if (0xf < gViewportMax) {
                    gViewportMax = 0xf;
                }
                gSomeFlag4 = 0;

                setSomeMode(0);
                setSomeOtherMode(1, 5, 6);
            } else {
                gTransitionInProgress = '\0';
            }

            if (local_59 != false) {
                someFadeFunction();
            }

            uVar13 = 0;
            setupRenderState4();  // Possibly reset
        }

        // Clear all camera state variables
        gCameraFlags = 0;
        gCameraInterpTarget = (float)uVar13;
        gCameraInterpZ = (float)uVar13;
        gCameraInterpY = (float)uVar13;
        gCameraInterpX = (float)uVar13;
        gCameraCurrentValue = (float)uVar13;
        gCameraTransitionTimer = (float)uVar13;
        return;
    }

    // If conditions not met, mark transition as not in progress
    gTransitionInProgress = 1;
}
// FUNC_NAME: UIRenderer::drawFadeTransition
void __fastcall UIRenderer::drawFadeTransition(void* thisPtr, int textureHandleIn, float param_3, float param_4, int param_5)
{
    // Global state globals
    extern uint32 g_currentContext;     // DAT_012054dc
    extern uint32 g_mainRenderTarget;   // DAT_012058a4
    extern float g_screenWidth;         // DAT_00e2b1a4
    extern float g_screenHeight;        // DAT_00e2eff4
    extern float g_uiScaleX;            // DAT_00e2cd54
    extern float g_uiScaleY;            // DAT_00e44718
    extern float g_alphaClipLow;        // DAT_00e448e8
    extern float g_alphaClipHigh;       // DAT_00e2b1a0
    extern float g_interpMax;           // DAT_00e2eb58
    extern float g_alphaMultiplier;     // DAT_00e44584

    extern uint32 g_swapTextureA;       // DAT_01218ea8
    extern uint32 g_swapTextureB;       // DAT_01218eb8
    extern uint32 g_textureSlots[5];    // DAT_011f38f0 (array of 5 uint32s)
    extern uint32 g_textureSlotFlags[5];// DAT_011f38f4 (array of 5 uint32s)

    extern int32 g_renderState1;        // DAT_012058d0
    extern int32 g_renderState2;        // DAT_00f15988
    extern uint32 g_renderFlag1;        // _DAT_011f3a30
    extern uint32 g_renderFlag2;        // _DAT_011f39f4
    extern uint32 g_renderFlag3;        // _DAT_011f3a10
    extern uint32 g_renderFlag4;        // _DAT_011f3a44
    extern uint32 g_renderFlag5;        // _DAT_011f3a3c
    extern uint32 g_renderFlag6;        // _DAT_011f3a38
    extern uint32 g_renderFlag7;        // _DAT_011f3a14

    extern uint32 g_renderState3;       // DAT_012058d4
    extern uint32 g_renderState4;       // DAT_00f1598c
    extern uint32 g_renderColor;        // _DAT_011f3cdc

    extern uint32 g_vertexBufferBase;   // DAT_011a0f28
    extern uint32 g_vertexBufferCount;  // (derived from sizeof 0x38 per slot)

    extern float g_interpTableValues[?]; // DAT_00e2d938... (four per entry)

    extern uint32 g_frameCounter;       // _DAT_01205500

    // Local variables
    uint32 currentRenderTarget;
    uint32 swappedTextures[2];
    float interpX, interpY, interpZ, interpW;
    float uvCoords[4];
    float posData[4] = {0.0f, 0.0f, 0.0f, 0.0f};
    float local_1c, local_20;
    uint32 local_38 = 0;
    int iterationCount;
    int i, j;

    // Step 1: Determine current render target
    if (g_currentContext == 0) {
        currentRenderTarget = g_mainRenderTarget;
    } else {
        currentRenderTarget = *(uint32*)(g_currentContext + 0x16c);
    }
    g_frameCounter++;

    // Step 2: Get projection/screen coordinates (call to FUN_0056b420)
    // Interpreted as: getScreenSpaceXY(textureHandle, &uvCoords)
    // But hard to reconstruct exactly.
    getScreenSpaceProjection(&g_unknownMatrix, textureHandleIn, &uvCoords);

    uvCoords[0] = (g_screenWidth / local_34) * uvCoords[0] * g_uiScaleX + g_uiScaleX;
    uvCoords[1] = (g_screenWidth / local_34) * uvCoords[1] * g_uiScaleY + g_uiScaleX; // likely a bug

    // Clamp uvCoords
    if (g_alphaClipLow < uvCoords[0]) {
        if (uvCoords[0] > g_alphaClipHigh)
            uvCoords[0] = g_alphaClipHigh;
    } else {
        uvCoords[0] = g_alphaClipLow;
    }
    if (g_alphaClipLow < uvCoords[1]) {
        if (uvCoords[1] > g_alphaClipHigh)
            uvCoords[1] = g_alphaClipHigh;
    } else {
        uvCoords[1] = g_alphaClipLow;
    }

    // Interpolation from param_3 (which is clamped to 0..g_interpMax)
    float alpha = param_3;
    if (alpha < 0.0f || g_interpMax < alpha) {
        alpha = (g_interpMax < alpha) ? g_interpMax : 0.0f;
    }

    // Look up interpolation values from table (2D lookup)
    interpZ = 0.0f;
    interpX = 0.0f;
    interpY = 0.0f;
    float interpAlpha = 0.0f;
    int tableIndex = -1;
    for (i = 0; i < 10; i++) { // 10 entries (0xe2d948 - 0xe2d938 = 0x10 bytes per entry, 4 floats)
        float* entryStart = &g_interpTableValues[4 * i];
        if (alpha <= entryStart[0]) {
            tableIndex = i;
            break;
        }
    }
    if (tableIndex != -1) {
        float t = (alpha - g_interpTableValues[4 * tableIndex]) /
                  (g_interpTableValues[4 * tableIndex] - g_interpTableValues[4 * tableIndex]);
        interpX = (g_interpTableValues[4 * tableIndex + 2] - g_interpTableValues[4 * tableIndex + 1]) * t +
                   g_interpTableValues[4 * tableIndex + 1];
        interpY = (g_interpTableValues[4 * tableIndex + 3] - g_interpTableValues[4 * tableIndex + 2]) * t +
                   g_interpTableValues[4 * tableIndex + 2];
        interpZ = (g_interpTableValues[4 * tableIndex + 4] - g_interpTableValues[4 * tableIndex + 3]) * t +
                   g_interpTableValues[4 * tableIndex + 3];
    }

    // Step 3: Set render states for the effect
    setRenderStateFlags(0x16, 0x16, &g_renderFlag1, 1);
    setRenderStateClamp(7, 7);
    setRenderStates(0xe, 0xe, &g_renderFlag3, 0);
    setRenderStates(0x1b, 0x1b, &g_renderFlag4, 0);
    setRenderStates(0x19, 0x19, &g_renderFlag5, 5);
    setRenderStates(0x18, 0x18, &g_renderFlag6, 0);
    setRenderStates(0xf, 0xf, &g_renderFlag7, 0);

    // Step 4: Clear slots (except slot 4)
    for (i = 0; i < 5; i++) {
        if (i != 4 && g_textureSlots[i] != 0) {
            if (g_textureSlots[i] < 0x1000) {
                releaseResource(g_textureSlots[i], getVertexBufferPtr(g_textureSlots[i]));
            } else {
                releaseResource(g_textureSlots[i], 0);
            }
        }
    }

    // Step 5: Set current render target with flags
    uint32 rtID = currentRenderTarget;
    if (rtID != 0xFFFFFFFF && rtID < 0x1000) {
        uint32* vb = getVertexBufferPtr(rtID);
        if (vb != 0 && ((uint8*)vb)[0] < 4) {
            setTextureFlags(vb[5], 0x100000); // +0x10 within struct? Actually offset 0x10 from base?
            vb[4] = (vb[4] & 0xFC9C8FFF) | 0x100000;
            flushCommandBuffer();
        }
    }

    // Step 6: Set render state (1,2,1) 
    setRenderState(1, 2, 1);

    // Step 7: Swap textures A and B (ping-pong)
    uint32 swapA = g_swapTextureA;
    uint32 swapB = g_swapTextureB;
    uint32 swapTmp = swapA;
    // Remove from slot list
    for (i = 0; i < 20; i++) {
        if (slotList[i].textureId == g_swapTextureA) {
            slotList[i].flags &= ~0x3; // clear bits 0-1
            break;
        }
    }
    // Set slot 0 texture to old swapA
    uint32 oldSlot0Tex = g_textureSlots[0];
    uint32 oldSlot0Flag = g_textureSlotFlags[0];
    g_textureSlots[0] = g_swapTextureA;
    g_textureSlotFlags[0] = 0;
    bindTextureToSlot(0, oldSlot0Tex, oldSlot0Flag);

    // Now do the same for swapB
    for (i = 0; i < 20; i++) {
        if (slotList[i].textureId == g_swapTextureB) {
            slotList[i].flags &= ~0x3;
            break;
        }
    }
    uint32 oldSlot1Tex = g_textureSlots[0]; // note: reuse slot 0? Actually slot 0 already set; this is a bug in decomp? Possibly slot 1.
    uint32 oldSlot1Flag = g_textureSlotFlags[0];
    g_textureSlots[0] = g_swapTextureB;
    g_textureSlotFlags[0] = 0;
    bindTextureToSlot(0, oldSlot1Tex, oldSlot1Flag);

    // Set viewport clear
    setViewport(0, 0, 0, 1.0f, 1.0f);

    // Store current textures for later
    g_currentScreenTexture = g_swapTextureB;
    g_currentBBScreenTexture = g_swapTextureA; // ?

    g_someRenderState = 5;

    if (g_previousRenderState == &g_someDummy) {
        releaseTexture(g_swapTextureB);
        releaseTexture(g_swapTextureA);
    }

    // Step 8: Push render states
    pushRenderStateA();
    pushRenderStateB();
    pushRenderStateC();

    // Step 9: Allocate and fill vertex buffer for fullscreen quad
    float* vb = (float*)allocateVertexBuffer(0xd, 4, 0, 1, 0);
    if (vb != 0) {
        vb[0] = g_screenHeight;
        vb[1] = g_screenWidth;
        vb[2] = 0.0f;
        vb[3] = 0.0f;
        vb[4] = g_screenWidth;
        vb[5] = g_screenWidth;
        vb[6] = g_screenWidth;
        vb[7] = 0.0f;
        vb[8] = g_screenWidth;
        vb[9] = g_screenHeight;
        vb[10] = g_screenWidth;
        vb[11] = g_screenWidth;
        vb[12] = g_screenHeight;
        vb[13] = g_screenHeight;
        vb[14] = 0.0f;
        vb[15] = g_screenWidth;
        finishVertexBuffer();
    }

    // Step 10: Set texture for the post-process
    if (g_currentTexture != 0) {
        uint32 texId = (g_currentTexture & 0xFF);
        if (textureOffsetTable[g_currentScreenTexture * 0x10] != 0) {
            texId += 0x10;
        }
        drawPrimitive();
        textureTargetArray[texId] = 0;
    }

    g_previousRenderState = 0;
    g_someFlag = 0;
    g_currentScreenTexture = 0;
    g_currentBBScreenTexture = 0;
    g_unknown1 = 0;
    g_unknown2 = 0;

    // Step 11: Clear slots again
    for (i = 0; i < 5; i++) {
        if (i != 4 && g_textureSlots[i] != 0) {
            if (g_textureSlots[i] < 0x1000) {
                releaseResource(g_textureSlots[i], getVertexBufferPtr(g_textureSlots[i]));
            } else {
                releaseResource(g_textureSlots[i], 0);
            }
        }
    }

    // Step 12: Compute iteration count based on interpZ
    float aspectX = g_screenWidth / (float)g_unknownWidth; // DAT_01218e40?
    float aspectY = g_screenWidth / (float)g_unknownHeight; // DAT_01218e42?
    g_currentTextureHandle1 = g_textureHandleA; // DAT_01125a84
    if (g_textureHandleA == g_mainScreenTexture) {
        textureName = "screen_texture";
    } else {
        textureName = "bb_texture_p";
    }
    g_currentTextureId = getTextureByName(g_textureHandleA, textureName);
    releaseTexture(g_currentTextureHandle1);
    g_currentTextureHandle2 = g_textureHandleB; // DAT_01219908
    doSomething();
    if (g_textureHandleC != 0) {
        drawSomething(g_currentTextureHandle2, g_textureHandleC, &g_otherQuad);
    }

    iterationCount = (int)interpZ;
    if (iterationCount < 1) iterationCount = 1;

    uint32 texA = swapA;
    uint32 texB = swapB;
    float uvPosX = uvCoords[0];
    float uvPosY = uvCoords[1];
    float uvStep = (interpZ - (float)iterationCount) / (float)iterationCount; // actually the decrement

    for (i = 0; i < iterationCount; i++) {
        // For last iteration, set special render state
        if (i > 0 && i == iterationCount - 1) {
            setRenderStateClamp(0x1b);
            g_renderFlag4 = 1;
            setRenderStateColor(0xc1);
            g_renderColor = 0x80808080;
            setRenderState(1, 0xe, 0xf);
        }

        // Compute position for quad
        local_1c = (float)i * g_positionStep + interpY;
        local_20 = local_1c * aspectX;
        local_1c = local_1c * aspectY;

        uint32 texHandle2 = g_textureHandleD;
        if (g_currentTextureHandle1 != g_textureHandleE) {
            texHandle2 = g_textureHandleF;
        }
        drawSomething(g_currentTextureHandle1, texHandle2, &local_20);

        // Swap texA with texB? Actually implement ping-pong
        // Remove from slot list again
        for (j = 0; j < 20; j++) {
            if (slotList[j].textureId == texB) {
                slotList[j].flags &= ~0x3;
                break;
            }
        }
        uint32 oldSlot0Tex2 = g_textureSlots[0];
        uint32 oldSlot0Flag2 = g_textureSlotFlags[0];
        g_textureSlots[0] = texB;
        g_textureSlotFlags[0] = 0;
        bindTextureToSlot(0, oldSlot0Tex2, oldSlot0Flag2);

        // Set texture from ID
        if (g_currentTextureId != 0) {
            uint32 texId2 = g_currentTextureId & 0xFF;
            if (textureOffsetTable[g_currentTextureHandle1 * 0x10] != 0) {
                texId2 += 0x10;
            }
            if (texA == 0xFFFFFFFF) texA = 0xFFF;
            drawPrimitive();
            textureTargetArray[texId2] = texA;
        }

        // Allocate another vertex buffer for this pass
        float* vb2 = (float*)allocateVertexBuffer(0xd, 4, 0, 1, 0);
        if (vb2 != 0) {
            vb2[0] = g_screenHeight;
            vb2[1] = g_screenHeight;
            vb2[2] = g_screenWidth;
            vb2[3] = g_screenHeight;
            vb2[4] = g_screenWidth;
            vb2[5] = g_screenWidth;
            vb2[6] = g_screenHeight;
            vb2[7] = g_screenWidth;
            finishVertexBuffer();
        }

        // Clear slots
        for (j = 0; j < 5; j++) {
            if (j != 4 && g_textureSlots[j] != 0) {
                if (g_textureSlots[j] < 0x1000) {
                    releaseResource(g_textureSlots[j], getVertexBufferPtr(g_textureSlots[j]));
                } else {
                    releaseResource(g_textureSlots[j], 0);
                }
            }
        }

        // Update texA/texB for next iteration (they are swapped)
        uint32 texATmp = texA;
        texA = texB;
        texB = texATmp;

        // Compute alpha for this iteration
        float alphaStep = uvStep;
        if (alphaStep < 0.0f) alphaStep = 0.0f;
        setRenderStateClamp(0x1b);
        g_renderColor = ((int)(alphaStep * g_alphaMultiplier) & 0xFF);
        g_renderColor = (g_renderColor << 8 | g_renderColor) << 8 | g_renderColor;
        g_renderColor = g_renderColor << 8 | g_renderColor;
        g_renderFlag4 = 1;
        setRenderStateColor(0xc1);
        setRenderState(1, 0xe, 0xf);
        setRenderState2(0xe, 0xf, 1, 2, 1);

        // Switch texture handles
        g_currentTextureHandle1 = g_textureHandleE;
        if (g_textureHandleE == g_mainScreenTexture) {
            textureName = "screen_texture";
        } else {
            textureName = "bb_texture_p";
        }
        g_currentTextureId = getTextureByName(g_textureHandleE, textureName);
        releaseTexture(g_currentTextureHandle1);

        // Draw second quad with different UV
        uvCoords[0] = interpX;
        uvCoords[1] = param_4;
        local_38 = g_unknownConstant;
        drawSomething(g_currentTextureHandle1, g_textureHandleG, &uvCoords);

        // Remove from slot list for texB
        // (similar to before)
        for (j = 0; j < 20; j++) {
            if (slotList[j].textureId == texB) {
                slotList[j].flags &= ~0x3;
                break;
            }
        }
        oldSlot0Tex2 = g_textureSlots[0];
        oldSlot0Flag2 = g_textureSlotFlags[0];
        g_textureSlots[0] = texB;
        g_textureSlotFlags[0] = 0;
        bindTextureToSlot(0, oldSlot0Tex2, oldSlot0Flag2);

        // Set texture from ID for second quad
        if (g_currentTextureId != 0) {
            uint32 texId3 = g_currentTextureId & 0xFF;
            if (textureOffsetTable[g_currentTextureHandle1 * 0x10] != 0) {
                texId3 += 0x10;
            }
            if (texA == 0xFFFFFFFF) texA = 0xFFF;
            drawPrimitive();
            textureTargetArray[texId3] = texA;
        }

        // Allocate and fill another VB
        float* vb3 = (float*)allocateVertexBuffer(0xd, 4, 0, 1, 0);
        if (vb3 != 0) {
            vb3[0] = g_screenHeight;
            vb3[1] = g_screenHeight;
            vb3[2] = g_screenWidth;
            vb3[3] = g_screenHeight;
            vb3[4] = g_screenWidth;
            vb3[5] = g_screenWidth;
            vb3[6] = g_screenHeight;
            vb3[7] = g_screenWidth;
            finishVertexBuffer();
        }

        // Clear slots again
        for (j = 0; j < 5; j++) {
            if (j != 4 && g_textureSlots[j] != 0) {
                if (g_textureSlots[j] < 0x1000) {
                    releaseResource(g_textureSlots[j], getVertexBufferPtr(g_textureSlots[j]));
                } else {
                    releaseResource(g_textureSlots[j], 0);
                }
            }
        }

        setRenderState(1, 2, 1);
    } // end iteration loop

    // Step 13: Restore current render target
    uint32 finalRT = g_mainRenderTarget;
    if (g_currentContext != 0) {
        finalRT = *(uint32*)(g_currentContext + 0x16c);
    }
    for (j = 0; j < 20; j++) {
        if (slotList[j].textureId == finalRT) {
            slotList[j].flags &= ~0x3;
            break;
        }
    }
    uint32 oldSlot0Tex3 = g_textureSlots[0];
    uint32 oldSlot0Flag3 = g_textureSlotFlags[0];
    g_textureSlotFlags[0] = 0;
    g_textureSlots[0] = finalRT;
    bindTextureToSlot(0, oldSlot0Tex3, oldSlot0Flag3);

    // Set render state 4,0? (not sure)
    bool wasActive = (g_textureSlots[2] != 0); // DAT_011f3910
    int oldSlot2State = g_textureSlotFlags[2]; // DAT_011f3914
    g_textureSlots[2] = 0;
    g_textureSlotFlags[2] = 0;
    if (wasActive || oldSlot2State != 0) {
        callVirtualMethod(g_someObject, 0); // indirect call
    }

    setViewport(0, 0, 0, 1.0f, 1.0f);

    // Restore second texture (texB) with 0x100000 flags
    if (texB != 0xFFFFFFFF && texB < 0x1000) {
        uint32* vbFinal = getVertexBufferPtr(texB);
        if (vbFinal != 0 && ((uint8*)vbFinal)[0] < 4) {
            setTextureFlags(vbFinal[5], 0x100000);
            vbFinal[4] = (vbFinal[4] & 0xFC9C8FFF) | 0x100000;
            flushCommandBuffer();
        }
    }

    // Set texture ID for the final pass
    if (g_currentTextureId != 0) {
        uint32 texIdFinal = g_currentTextureId & 0xFF;
        if (textureOffsetTable[g_currentTextureHandle1 * 0x10] != 0) {
            texIdFinal += 0x10;
        }
        if (texB == 0xFFFFFFFF) texB = 0xFFF;
        drawPrimitive();
        textureTargetArray[texIdFinal] = texB;
    }

    // Step 14: Choose final texture based on param_5
    if (param_5 == 0) {
        g_currentTextureHandle1 = g_textureHandleH; // DAT_01125a8c
        if (g_textureHandleH == g_mainScreenTexture) {
            textureName = "screen_texture";
        } else {
            textureName = "bb_texture_p";
        }
        g_currentTextureId = getTextureByName(g_textureHandleH, textureName);
        releaseTexture(g_currentTextureHandle1);
    } else {
        g_currentTextureHandle1 = g_textureHandleI; // DAT_01125a90
        if (g_textureHandleI == g_mainScreenTexture) {
            textureName = "screen_texture";
        } else {
            textureName = "bb_texture_p";
        }
        g_currentTextureId = getTextureByName(g_textureHandleI, textureName);
        releaseTexture(g_currentTextureHandle1);

        uint32 otherRT = g_mainRenderTarget2; // DAT_012058a8
        if (g_currentContext != 0) {
            otherRT = *(uint32*)(g_currentContext + 0x170);
        }
        if (otherRT != 0xFFFFFFFF && otherRT < 0x1000) {
            uint32* vbOther = getVertexBufferPtr(otherRT);
            if (vbOther != 0 && ((uint8*)vbOther)[0] < 4) {
                setTextureFlags(vbOther[5], 0x210000);
                vbOther[4] = (vbOther[4] & 0xFCAD8FFF) | 0x210000;
                flushCommandBuffer();
            }
        }
        if (g_otherTextureId != 0) {
            uint32 texIdOther = g_otherTextureId & 0xFF;
            if (textureOffsetTable[g_currentTextureHandle1 * 0x10] != 0) {
                texIdOther += 0x10;
            }
            if (otherRT == 0xFFFFFFFF) otherRT = 0xFFF;
            drawPrimitive();
            textureTargetArray[texIdOther] = otherRT;
        }
        drawSomething(g_currentTextureHandle1, g_textureHandleJ, param_5); // param_5 as pointer
    }

    // Step 15: Final render state settings
    setRenderStateClamp(0x1b);
    g_renderFlag4 = 1;
    setRenderState(1, 5, 6);

    // Allocate another VB? (duplicate of earlier)
    float* vbFinal2 = (float*)allocateVertexBuffer(0xd, 4, 0, 1, 0);
    if (vbFinal2 != 0) {
        vbFinal2[0] = g_screenHeight;
        vbFinal2[1] = g_screenHeight;
        vbFinal2[2] = g_screenWidth;
        vbFinal2[3] = g_screenHeight;
        vbFinal2[4] = g_screenWidth;
        vbFinal2[5] = g_screenWidth;
        vbFinal2[6] = g_screenHeight;
        vbFinal2[7] = g_screenWidth;
        finishVertexBuffer();
    }

    // Clear texture ID
    if (g_currentTextureId != 0) {
        uint32 texIdClear = g_currentTextureId & 0xFF;
        if (textureOffsetTable[g_currentTextureHandle1 * 0x10] != 0) {
            texIdClear += 0x10;
        }
        drawPrimitive();
        textureTargetArray[texIdClear] = 0;
    }

    // Step 16: Restore slot 2 with the other RT
    uint32 oldSlot2Tex = g_textureSlots[2];
    uint32 oldSlot2Flag = g_textureSlotFlags[2];
    g_previousRenderState = 0;
    g_someFlag = 0;
    g_currentTextureHandle2 = 0;
    g_currentTextureHandle1 = 0;
    g_textureSlots[2] = g_mainRenderTarget2; // DAT_012058a8
    if (g_currentContext != 0) {
        g_textureSlots[2] = *(uint32*)(g_currentContext + 0x170);
    }
    g_textureSlotFlags[2] = 0;
    bindTextureToSlot(4, oldSlot2Tex, oldSlot2Flag);

    // Restore render states to final values
    setRenderStateClamp(0x16);
    g_renderFlag1 = 1;
    setRenderStateClamp(7);
    g_renderFlag2 = 1;
    setRenderStateClamp(0xe);
    g_renderFlag3 = 1;
    setRenderStateClamp(0x19);
    g_renderFlag5 = 7;
    setRenderStateClamp(0x18);
    g_renderFlag6 = 0;
    setRenderStateClamp(0xf);
    g_renderFlag7 = 0;

    setRenderState(1, 5, 6);

    setRenderStateClamp(0x1b);
    g_renderFlag4 = 0;

    // Decrement frame counter if still same RT
    uint32 finalRT2 = g_mainRenderTarget;
    if (g_currentContext != 0) {
        finalRT2 = *(uint32*)(g_currentContext + 0x16c);
    }
    if (currentRenderTarget == finalRT2) {
        g_frameCounter--;
    }

    return;
}
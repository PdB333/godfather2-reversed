// FUNC_NAME: renderBurnTransition
// Address: 0x005263c0
// This function renders a "burn" overlay effect, alternating between render targets,
// using a lookup table to determine number of layers and distortion parameters.
// It is called to composite a burn/transition effect onto the screen.

void __fastcall renderBurnTransition(
    int unused,                     // __fastcall ECX - unused
    int unknownId,                  // __fastcall EDX
    float progress,                 // stack param - burn progress (0..1)
    float verticalOffset,           // stack param - vertical offset for second pass
    void* pExternalRenderData       // stack param - pointer to extra render data (used as bool)
)
{
    // Global state pointers and variables
    // DAT_012054dc is a pointer to a manager object, likely an ObjectManager
    // Offsets: +0x16C = activeTextureIndex1, +0x170 = activeTextureIndex2
    int activeTextureIndex1;
    if (g_pObjectManager == 0) {
        activeTextureIndex1 = g_defaultTextureIndex1;
    } else {
        activeTextureIndex1 = *(int*)((char*)g_pObjectManager + 0x16C);
    }

    // Increment frame counter (DAT_01205500)
    g_frameCounter++;

    // Get screen dimensions (stored in DAT_01218e00)
    float screenWidth, screenHeight;
    getScreenResolution((ScreenRes*)&g_screenResolution, unknownId, &screenWidth, &screenHeight); // FUN_0056b420

    // Calculate adjusted coordinates based on screen size and constants
    float adjustedWidth = (g_screenWidth / screenHeight) * screenWidth * g_const1 + g_const1;
    float adjustedHeight = (g_screenWidth / screenHeight) * screenHeight * g_const2 + g_const1;

    // Clamp adjustedWidth and adjustedHeight
    if (g_clampMin > adjustedWidth) {
        adjustedWidth = g_clampMin;
    } else if (adjustedWidth > g_clampMax) {
        adjustedWidth = g_clampMax;
    }
    if (g_clampMin > adjustedHeight) {
        adjustedHeight = g_clampMin;
    } else if (adjustedHeight > g_clampMax) {
        adjustedHeight = g_clampMax;
    }

    // Interpolate burn parameters from lookup table based on progress
    float layerCountFloat = 0.0f;
    float distortionX = 0.0f;
    float distortionY = 0.0f;
    float totalLayers = 0.0f;

    // Clamp progress to [0, g_progressClampMax]
    if (progress < 0.0f) {
        progress = 0.0f;
    } else if (progress > g_progressClampMax) {
        progress = g_progressClampMax;
    }

    // Lookup table interpolation (burn curve)
    // Tables: g_lutEntries (5 entries, each with 4 floats: input, out_distX, out_distY, out_layers)
    int tableIndex = 0;
    float* pTable = (float*)&g_lutTable; // start at g_lutTable (= DAT_00e2d948)
    do {
        if (progress <= *pTable) {
            float* pThisEntry = pTable - 4; // go back 4 floats to start of this entry? Actually pTable is iterating by 4, so the entry starts 4 floats before?
            // Actually the table is like: entry[i] has 4 floats: [threshold, distX, distY, layers]
            // The code uses pTable as the threshold array, and other arrays are offset from there.
            float fraction = (progress - g_lutInputs[tableIndex]) / (g_lutTable[tableIndex * 4] - g_lutInputs[tableIndex]);
            distortionX = (g_lutDistX_out[tableIndex] - g_lutDistX_in[tableIndex]) * fraction + g_lutDistX_in[tableIndex];
            distortionY = (g_lutDistY_out[tableIndex] - g_lutDistY_in[tableIndex]) * fraction + g_lutDistY_in[tableIndex];
            totalLayers = (g_lutLayers_out[tableIndex] - g_lutLayers_in[tableIndex]) * fraction + g_lutLayers_in[tableIndex];
            break;
        }
        pTable += 4;
        tableIndex++;
    } while ((int)pTable < (int)&g_lutEnd);

    // Clamp various global rendering parameters (min/max bounds)
    // These seem to be clamping render states
    if (g_renderClamp1 < 0x16) g_renderClamp1 = 0x16;
    if (0x16 < g_renderClamp2) g_renderClamp2 = 0x16;
    *g_renderStateFlag1 = 1;

    if (g_renderClamp1 < 7) g_renderClamp1 = 7;
    if (7 < g_renderClamp2) g_renderClamp2 = 7;
    *g_renderStateFlag2 = 0;

    if (g_renderClamp1 < 0xe) g_renderClamp1 = 0xe;
    if (0xe < g_renderClamp2) g_renderClamp2 = 0xe;
    *g_renderStateFlag3 = 0;

    if (g_renderClamp1 < 0x1b) g_renderClamp1 = 0x1b;
    if (0x1a < g_renderClamp2) g_renderClamp2 = 0x1b;
    *g_renderStateFlag4 = 0;

    if (g_renderClamp1 < 0x19) g_renderClamp1 = 0x19;
    if (0x19 < g_renderClamp2) g_renderClamp2 = 0x19;
    *g_renderStateFlag5 = 5;

    if (g_renderClamp1 < 0x18) g_renderClamp1 = 0x18;
    if (0x18 < g_renderClamp2) g_renderClamp2 = 0x18;
    *g_renderStateFlag6 = 0;

    if (g_renderClamp1 < 0xf) g_renderClamp1 = 0xf;
    if (0xf < g_renderClamp2) g_renderClamp2 = 0xf;
    *g_renderStateFlag7 = 0;

    // Release old render textures (skip slot 4)
    for (int i = 0; i < 5; i++) {
        if (i != 4) {
            int texId = g_renderTextureIds[i * 2]; // DAT_011f38f0[i*2]
            if (texId != 0) {
                void* texInfo = (texId < 0x1000) ? (void*)(&g_textureInfoArray + texId * 0x38) : 0;
                releaseTexture(texId, texInfo); // FUN_00606830
            }
        }
    }

    // Process the object's active texture (index from g_pObjectManager)
    int currentTexId = g_defaultTextureIndex1;
    if (g_pObjectManager != 0) {
        currentTexId = *(int*)((char*)g_pObjectManager + 0x16C);
    }
    if ((currentTexId != 0xffffffff) && (currentTexId < 0x1000)) {
        int idx = currentTexId * 0x38;
        if ((&g_textureInfoArray + idx != 0) && (g_textureInfoArray[idx] < 4)) { // check some state
            if (*(int*)(&g_textureInfoData2 + idx) != 0) {
                setTextureFlags(*(int*)(&g_textureInfoData2 + idx), 0x100000); // FUN_00606e60
            }
            *(int*)(&g_textureInfoFlags + idx) = (*(int*)(&g_textureInfoFlags + idx) & 0xfc9c8fff) | 0x100000;
            updateTextureBinding(); // FUN_006189c0
        }
    }

    // Set render states (alpha blending etc.)
    setRenderState(1, 2, 1); // FUN_00417cf0

    // Swap render targets
    unsigned int renderTargetA = g_renderTargetA; // DAT_01218eb8
    unsigned int renderTargetB = g_renderTargetB; // DAT_01218ea8
    unsigned int localRenderTargetA = renderTargetA;
    unsigned int localRenderTargetB = renderTargetB;

    // Release old render target (first pass)
    unsigned int rtIndex = 0;
    while (rtIndex < 20) {
        if (g_renderTargetList[rtIndex] == renderTargetB) {
            if (rtIndex < 20) {
                g_renderTargetList[rtIndex + 1] &= 0xfffffffc; // set flags
            }
            break;
        }
        rtIndex++;
    }
    unsigned int oldTexA = g_renderTextureIds[0]; // from slot 0? Actually pattern: DAT_011f38f0 and DAT_011f38f4
    unsigned int oldTexB = g_renderTextureIds[1];
    g_renderTextureIds[0] = renderTargetB;
    g_renderTextureIds[1] = 0;
    swapRenderTexture(0, oldTexA, oldTexB); // FUN_00609340

    // Same for second render target
    rtIndex = 0;
    while (rtIndex < 20) {
        if (g_renderTargetList[rtIndex] == renderTargetA) {
            if (rtIndex < 20) {
                g_renderTargetList[rtIndex + 1] &= 0xfffffffc;
            }
            break;
        }
        rtIndex++;
    }
    unsigned int oldTexC = g_renderTextureIds[1]; // ?
    unsigned int oldTexD = g_renderTextureIds[0];
    g_renderTextureIds[0] = renderTargetA;
    g_renderTextureIds[1] = 0;
    swapRenderTexture(0, oldTexD, oldTexC);

    // Set clear color and clear
    setClearColor(0, 0, 0, 0x3f800000, 0x3f800000); // FUN_0060db60

    // Store current texture indices for later use
    g_currentTextureStack1 = g_textureHandle2; // DAT_01219954 = DAT_01219a58
    g_currentTextureStack0 = g_textureHandle1; // DAT_01219950 = DAT_01219900
    *g_someRenderState = 5;

    // If current render texture is the sentinel, release some textures
    if (g_pCurrentRenderTexture == &g_sentinel) {
        releaseTexture(g_textureHandle2); // FUN_0060a460
        releaseTexture(g_textureHandle1);
    }

    // Call various render functions
    someRenderFunction1(); // FUN_00530a60
    someRenderFunction2(); // FUN_00530df0
    someRenderFunction3(); // FUN_00530ff0

    // Allocate vertex buffer (type 0xd, size 4, ...)
    float* pVertexBuffer = (float*)allocateVertexBuffer(0xd, 4, 0, 1, 0); // FUN_0060cd00
    if (pVertexBuffer != 0) {
        // Fill vertex buffer with UV coordinates and color?
        pVertexBuffer[0] = g_texCoordU; // DAT_00e2eff4
        pVertexBuffer[1] = g_screenWidth;
        pVertexBuffer[2] = 0.0f;
        pVertexBuffer[3] = 0.0f;
        pVertexBuffer[4] = g_screenWidth;
        pVertexBuffer[5] = g_screenWidth;
        pVertexBuffer[6] = g_screenWidth;
        pVertexBuffer[7] = 0.0f;
        pVertexBuffer[8] = g_screenWidth;
        pVertexBuffer[9] = g_texCoordU;
        pVertexBuffer[10] = g_screenWidth;
        pVertexBuffer[11] = g_screenWidth;
        pVertexBuffer[12] = g_texCoordU;
        pVertexBuffer[13] = g_texCoordU;
        pVertexBuffer[14] = 0.0f;
        pVertexBuffer[15] = g_screenWidth;
        unlockVertexBuffer(); // FUN_0060cde0
    }

    // If a custom texture handle is set, apply it
    if (g_customTextureId != 0) {
        int texSlot = g_customTextureId & 0xff;
        if (g_textureSlots[g_currentTextureStack0 * 16] != 0) {
            texSlot += 0x10;
        }
        setTextureSlot(); // FUN_00618d40
        g_textureBindings[texSlot] = 0; // clear
    }

    // Reset global pointers
    g_pCurrentRenderTexture = 0;
    g_renderFlags1 = 0;
    g_currentTextureStack0 = 0;
    g_currentTextureStack1 = 0;
    *g_renderFlag2 = 0;
    *g_renderFlag3 = 0;

    // Release old render textures again
    for (int i = 0; i < 5; i++) {
        if (i != 4) {
            int texId = g_renderTextureIds[i * 2];
            if (texId != 0) {
                void* texInfo = (texId < 0x1000) ? (void*)(&g_textureInfoArray + texId * 0x38) : 0;
                releaseTexture(texId, texInfo);
            }
        }
    }

    // Compute scaling factors for the burn layers
    float scaleX = g_scaleFactor / (float)g_screenWidthInt;   // DAT_00e35654 / DAT_01218e40
    float scaleY = g_scaleFactor / (float)g_screenHeightInt;  // DAT_00e35654 / DAT_01218e42

    // Select which texture to use for the base layer based on current context
    g_currentTexture = g_textureHandles[0]; // DAT_011259d4 = DAT_01125a84
    const char* textureType;
    if (g_textureHandles[0] == g_sentinelTexture) {
        textureType = "screen_texture";
    } else {
        textureType = "bb_texture_p";
    }
    g_textureSampler = createTextureSampler(g_textureHandles[0], textureType); // FUN_0060a580
    releaseTexture(g_currentTexture); // release old

    // Set another texture context
    g_currentTexture2 = g_textureHandles[1]; // DAT_011259d0 = DAT_01219908
    someRenderFunction4(); // FUN_00612a60

    // If there is an extra texture to apply, set it
    if (g_extraTextureId != 0) {
        setTextureWithTransform(g_currentTexture2, g_extraTextureId, &g_someTransform); // FUN_0060add0
    }

    // Determine number of layers to render (derived from lookup table)
    int numLayers = (int)totalLayers;
    if (numLayers < 1) {
        numLayers = 1;
    }

    if (numLayers > 0) {
        float startFactor = totalLayers - (float)numLayers; // used for alpha
        float currentAdjustedWidth = adjustedWidth;
        float currentAdjustedHeight = adjustedHeight;

        for (int layer = 0; layer < numLayers; layer++) {
            // For the last layer, set specific render states
            if ((layer > 0) && (layer == numLayers - 1)) {
                // Apply clamp again
                if (g_renderClamp1 < 0x1b) g_renderClamp1 = 0x1b;
                if (0x1a < g_renderClamp2) g_renderClamp2 = 0x1b;
                *g_renderStateFlag4 = 1;

                if (g_anotherClamp1 < 0xc1) g_anotherClamp1 = 0xc1;
                if (0xc0 < g_anotherClamp2) g_anotherClamp2 = 0xc1;
                *g_colorFlag = 0x80808080; // ARGB gray?

                setRenderState(1, 0xe, 0xf); // FUN_00417cf0
            }

            // Calculate screen coordinates for this layer
            float layerYPos = (float)layer * g_layerIncrement + distortionY; // g_layerIncrement = DAT_00e2d930
            float screenCoordX = layerYPos * scaleX;
            float screenCoordY = layerYPos * scaleY;
            float transformCoords[4] = { screenCoordX, screenCoordY, 0.0f, 0.0f };

            // Select texture handle based on current
            unsigned int textureToUse = g_texHandleB; // DAT_01125a78
            if (g_currentTexture != g_texHandleCompare) { // DAT_01125a88
                textureToUse = g_texHandleA; // DAT_01125a74
            }
            setTextureWithTransform(g_currentTexture, textureToUse, transformCoords);

            // Release old render target (from previous swap)
            unsigned int swapTarget = localRenderTargetB; // from earlier
            rtIndex = 0;
            while (rtIndex < 20) {
                if (g_renderTargetList[rtIndex] == swapTarget) {
                    if (rtIndex < 20) {
                        g_renderTargetList[rtIndex + 1] &= 0xfffffffc;
                    }
                    break;
                }
                rtIndex++;
            }
            unsigned int oldTex1 = g_renderTextureIds[1]; // DAT_011f38f4
            unsigned int oldTex0 = g_renderTextureIds[0];
            g_renderTextureIds[0] = swapTarget;
            g_renderTextureIds[1] = 0;
            swapRenderTexture(0, oldTex0, oldTex1);

            // If we have a sampler, bind the texture
            if (g_textureSampler != 0) {
                int texSlot = g_textureSampler & 0xff;
                if (g_textureSlots[g_currentTexture * 16] != 0) {
                    texSlot += 0x10;
                }
                if (localRenderTargetA == 0xffffffff) {
                    localRenderTargetA = 0xfff;
                }
                setTextureSlot();
                g_textureBindings[texSlot] = localRenderTargetA;
            }

            // Allocate another vertex buffer for this pass
            pVertexBuffer = (float*)allocateVertexBuffer(0xd, 4, 0, 1, 0);
            if (pVertexBuffer != 0) {
                pVertexBuffer[0] = g_texCoordU;
                pVertexBuffer[1] = g_texCoordU;
                pVertexBuffer[2] = g_screenWidth;
                pVertexBuffer[3] = g_texCoordU;
                pVertexBuffer[4] = g_screenWidth;
                pVertexBuffer[5] = g_screenWidth;
                pVertexBuffer[6] = g_texCoordU;
                pVertexBuffer[7] = g_screenWidth;
                unlockVertexBuffer();
            }

            // Release old textures after this pass
            for (int i = 0; i < 5; i++) {
                if (i != 4) {
                    int texId = g_renderTextureIds[i * 2];
                    if (texId != 0) {
                        void* texInfo = (texId < 0x1000) ? (void*)(&g_textureInfoArray + texId * 0x38) : 0;
                        releaseTexture(texId, texInfo);
                    }
                }
            }

            // Swap targets for next pass
            localRenderTargetA = localRenderTargetB;
            localRenderTargetB = swapTarget;

            // Compute alpha based on progress
            float alphaFactor = startFactor;
            if (alphaFactor < 0.0f) {
                alphaFactor = 0.0f;
            }

            // Set color/alpha state
            if (g_renderClamp1 < 0x1b) g_renderClamp1 = 0x1b;
            if (0x1a < g_renderClamp2) g_renderClamp2 = 0x1b;
            int alphaByte = (int)(alphaFactor * g_alphaScale) & 0xff; // DAT_00e44584
            *g_colorFlag = (alphaByte << 24) | (alphaByte << 16) | (alphaByte << 8) | alphaByte;
            *g_renderStateFlag4 = 1;

            if (g_anotherClamp1 < 0xc1) g_anotherClamp1 = 0xc1;
            if (0xc0 < g_anotherClamp2) g_anotherClamp2 = 0xc1;
            setRenderState(1, 0xe, 0xf);
            setRenderStateUV(0xe, 0xf, 1, 2, 1); // FUN_00417db0

            // Switch to second texture pass
            g_currentTexture = g_textureHandles[1]; // DAT_01125a88
            if (g_textureHandles[1] == g_sentinelTexture) {
                textureType = "screen_texture";
            } else {
                textureType = "bb_texture_p";
            }
            g_textureSampler = createTextureSampler(g_textureHandles[1], textureType);
            releaseTexture(g_currentTexture);

            // Update adjusted coordinates for the second pass
            currentAdjustedWidth = distortionX;
            currentAdjustedHeight = verticalOffset;
            float extraCoords[4] = { currentAdjustedWidth, currentAdjustedHeight, 0.0f, 0.0f };
            setTextureWithTransform(g_currentTexture, g_texHandleC, extraCoords); // DAT_01125a70

            // Release and swap again for second render target
            swapTarget = localRenderTargetB; // actually uVar10 from code
            rtIndex = 0;
            while (rtIndex < 20) {
                if (g_renderTargetList[rtIndex] == swapTarget) {
                    if (rtIndex < 20) {
                        g_renderTargetList[rtIndex + 1] &= 0xfffffffc;
                    }
                    break;
                }
                rtIndex++;
            }
            oldTex1 = g_renderTextureIds[1];
            oldTex0 = g_renderTextureIds[0];
            g_renderTextureIds[0] = swapTarget;
            g_renderTextureIds[1] = 0;
            swapRenderTexture(0, oldTex0, oldTex1);

            if (g_textureSampler != 0) {
                int texSlot = g_textureSampler & 0xff;
                if (g_textureSlots[g_currentTexture * 16] != 0) {
                    texSlot += 0x10;
                }
                if (localRenderTargetA == 0xffffffff) { // uVar4 from code
                    localRenderTargetA = 0xfff;
                }
                setTextureSlot();
                g_textureBindings[texSlot] = localRenderTargetA;
            }

            pVertexBuffer = (float*)allocateVertexBuffer(0xd, 4, 0, 1, 0);
            if (pVertexBuffer != 0) {
                pVertexBuffer[0] = g_texCoordU;
                pVertexBuffer[1] = g_texCoordU;
                pVertexBuffer[2] = g_screenWidth;
                pVertexBuffer[3] = g_texCoordU;
                pVertexBuffer[4] = g_screenWidth;
                pVertexBuffer[5] = g_screenWidth;
                pVertexBuffer[6] = g_texCoordU;
                pVertexBuffer[7] = g_screenWidth;
                unlockVertexBuffer();
            }

            for (int i = 0; i < 5; i++) {
                if (i != 4) {
                    int texId = g_renderTextureIds[i * 2];
                    if (texId != 0) {
                        void* texInfo = (texId < 0x1000) ? (void*)(&g_textureInfoArray + texId * 0x38) : 0;
                        releaseTexture(texId, texInfo);
                    }
                }
            }

            // Final render state for this layer
            setRenderState(1, 2, 1);
        }
    }

    // After all layers, process the active texture again
    int finalTexId = g_defaultTextureIndex1;
    if (g_pObjectManager != 0) {
        finalTexId = *(int*)((char*)g_pObjectManager + 0x16C);
    }
    rtIndex = 0;
    while (rtIndex < 20) {
        if (g_renderTargetList[rtIndex] == finalTexId) {
            if (rtIndex < 20) {
                g_renderTargetList[rtIndex + 1] &= 0xfffffffc;
            }
            break;
        }
        rtIndex++;
    }
    unsigned int oldTexE = g_renderTextureIds[1];
    unsigned int oldTexF = g_renderTextureIds[0];
    g_renderTextureIds[1] = 0;
    g_renderTextureIds[0] = finalTexId;
    swapRenderTexture(0, oldTexF, oldTexE);

    // Check and set some render flags
    bool flag = g_renderFlagA; // DAT_011f3910
    int flagVal = g_renderFlagB; // DAT_011f3914
    g_renderFlagA = 0;
    g_renderFlagB = 0;
    if (flag || flagVal != 0) {
        // Call a virtual function via pointer
        (*(void(*)(int, int))(*(int*)g_ptrToObject + 0x9c))(g_ptrToObject, 0); // likely something like clearRenderTarget
    }

    setClearColor(0, 0, 0, 0x3f800000, 0x3f800000);

    // Release last render target if valid
    if ((localRenderTargetB != 0xffffffff) && (localRenderTargetB < 0x1000)) {
        int idx = localRenderTargetB * 0x38;
        if ((&g_textureInfoArray + idx != 0) && (g_textureInfoArray[idx] < 4)) {
            if (*(int*)(&g_textureInfoData2 + idx) != 0) {
                setTextureFlags(*(int*)(&g_textureInfoData2 + idx), 0x100000);
            }
            *(int*)(&g_textureInfoFlags + idx) = (*(int*)(&g_textureInfoFlags + idx) & 0xfc9c8fff) | 0x100000;
            updateTextureBinding();
        }
    }

    // If sampler exists, bind the last texture
    if (g_textureSampler != 0) {
        int texSlot = g_textureSampler & 0xff;
        if (g_textureSlots[g_currentTexture * 16] != 0) {
            texSlot += 0x10;
        }
        if (localRenderTargetB == 0xffffffff) {
            localRenderTargetB = 0xfff;
        }
        setTextureSlot();
        g_textureBindings[texSlot] = localRenderTargetB;
    }

    // Final output based on pExternalRenderData
    if (pExternalRenderData == 0) {
        // Use texture handle set 2
        g_currentTexture = g_textureHandles[2]; // DAT_01125a8c
        if (g_textureHandles[2] == g_sentinelTexture) {
            textureType = "screen_texture";
        } else {
            textureType = "bb_texture_p";
        }
        g_textureSampler = createTextureSampler(g_textureHandles[2], textureType);
        releaseTexture(g_currentTexture);
    } else {
        // Use texture handle set 3
        g_currentTexture = g_textureHandles[3]; // DAT_01125a90
        if (g_textureHandles[3] == g_sentinelTexture) {
            textureType = "screen_texture";
        } else {
            textureType = "bb_texture_p";
        }
        g_textureSampler = createTextureSampler(g_textureHandles[3], textureType);
        releaseTexture(g_currentTexture);

        // Process active texture index 2
        int secondaryTexId = g_defaultTextureIndex2; // DAT_012058a8
        if (g_pObjectManager != 0) {
            secondaryTexId = *(int*)((char*)g_pObjectManager + 0x170);
        }
        if ((secondaryTexId != 0xffffffff) && (secondaryTexId < 0x1000)) {
            int idx = secondaryTexId * 0x38;
            if ((&g_textureInfoArray + idx != 0) && (g_textureInfoArray[idx] < 4)) {
                if (*(int*)(&g_textureInfoData2 + idx) != 0) {
                    setTextureFlags(*(int*)(&g_textureInfoData2 + idx), 0x210000);
                }
                *(int*)(&g_textureInfoFlags + idx) = (*(int*)(&g_textureInfoFlags + idx) & 0xfcad8fff) | 0x210000;
                updateTextureBinding();
            }
        }

        if (g_otherSampler != 0) { // DAT_01125a68
            int texSlot = g_otherSampler & 0xff;
            if (g_textureSlots[g_currentTexture * 16] != 0) {
                texSlot += 0x10;
            }
            if (secondaryTexId == 0xffffffff) {
                secondaryTexId = 0xfff;
            }
            setTextureSlot();
            g_textureBindings[texSlot] = secondaryTexId;
        }
        // Apply external render data as transform
        setTextureWithTransform(g_currentTexture, g_texHandleD, pExternalRenderData); // DAT_01125a6c
    }

    // Final render state
    if (g_renderClamp1 < 0x1b) g_renderClamp1 = 0x1b;
    if (0x1a < g_renderClamp2) g_renderClamp2 = 0x1b;
    *g_renderStateFlag4 = 1;
    setRenderState(1, 5, 6);

    pVertexBuffer = (float*)allocateVertexBuffer(0xd, 4, 0, 1, 0);
    if (pVertexBuffer != 0) {
        pVertexBuffer[0] = g_texCoordU;
        pVertexBuffer[1] = g_texCoordU;
        pVertexBuffer[2] = g_screenWidth;
        pVertexBuffer[3] = g_texCoordU;
        pVertexBuffer[4] = g_screenWidth;
        pVertexBuffer[5] = g_screenWidth;
        pVertexBuffer[6] = g_texCoordU;
        pVertexBuffer[7] = g_screenWidth;
        unlockVertexBuffer();
    }

    // Clear a texture slot if sampler exists
    if (g_finalSampler != 0) { // DAT_01125a60
        int texSlot = g_finalSampler & 0xff;
        if (g_textureSlots[g_currentTexture * 16] != 0) {
            texSlot += 0x10;
        }
        setTextureSlot();
        g_textureBindings[texSlot] = 0;
    }

    // Prepare next frame state
    unsigned int oldStateA = g_renderFlagB; // DAT_011f3914
    unsigned int oldStateB = g_renderFlagA; // DAT_011f3910
    g_pCurrentRenderTexture = 0;
    g_renderFlags1 = 0;
    g_currentTexture2 = 0;
    g_currentTexture = 0;
    g_renderFlagA = g_defaultTextureIndex2;
    if (g_pObjectManager != 0) {
        g_renderFlagA = *(int*)((char*)g_pObjectManager + 0x170);
    }
    g_renderFlagB = 0;
    swapRenderTexture(4, oldStateB, oldStateA); // FUN_00609340 with different slot

    // Final clamp
    if (g_renderClamp1 < 0x16) g_renderClamp1 = 0x16;
    if (0x16 < g_renderClamp2) g_renderClamp2 = 0x16;
    *g_renderStateFlag1 = 1;

    if (g_renderClamp1 < 7) g_renderClamp1 = 7;
    if (7 < g_renderClamp2) g_renderClamp2 = 7;
    *g_renderStateFlag2 = 1;

    if (g_renderClamp1 < 0xe) g_renderClamp1 = 0xe;
    if (0xe < g_renderClamp2) g_renderClamp2 = 0xe;
    *g_renderStateFlag3 = 1;

    if (g_renderClamp1 < 0x19) g_renderClamp1 = 0x19;
    if (0x19 < g_renderClamp2) g_renderClamp2 = 0x19;
    *g_renderStateFlag5 = 7;

    if (g_renderClamp1 < 0x18) g_renderClamp1 = 0x18;
    if (0x18 < g_renderClamp2) g_renderClamp2 = 0x18;
    *g_renderStateFlag6 = 0;

    if (g_renderClamp1 < 0xf) g_renderClamp1 = 0xf;
    if (0xf < g_renderClamp2) g_renderClamp2 = 0xf;
    *g_renderStateFlag7 = 0;

    setRenderState(1, 5, 6);

    if (g_renderClamp1 < 0x1b) g_renderClamp1 = 0x1b;
    if (0x1a < g_renderClamp2) g_renderClamp2 = 0x1b;
    *g_renderStateFlag4 = 0;

    // Finally, decrement frame counter if the active texture index hasn't changed
    int checkTexId = g_defaultTextureIndex1;
    if (g_pObjectManager != 0) {
        checkTexId = *(int*)((char*)g_pObjectManager + 0x16C);
    }
    if (activeTextureIndex1 == checkTexId) {
        g_frameCounter--;
    }
}
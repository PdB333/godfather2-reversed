// FUNC_NAME: RenderSystem::initDynamicCubeMaps
void __cdecl initDynamicCubeMaps(int resolution)
{
    int iVar1;
    void* puVar2;
    int iVar3;
    int* piVar4;
    byte* pbVar5;
    int uVar6;
    int unaff_FS_OFFSET;
    uint uVar7;
    int local_4; // set to 0x80 with a cast? Actually CONCAT31(local_4._1_3_,0x80) so low byte 0x80, rest unchanged. That probably means value 0x80.

    g_cubeMapResolution = resolution;

    // Determine texture format/flags based on AA flag
    uVar6 = 0x20001a; // base format
    if (g_useAAFlag != 0) {
        uVar6 = 0x20201a; // AA enabled format
    }

    // Create cube map texture (main cubemap)
    g_cubeMapTexture = createTexture(6, uVar6, resolution, resolution, 1, 0xffffffff);
    // Create cube map sky texture (same size as main? but later uses 0x100 for sky? Actually next call uses 0x100,0x100 for sky)
    g_cubeMapSkyTexture = createTexture(6, uVar6, 0x100, 0x100, 1, 0xffffffff);

    // Set debug names for textures
    uVar6 = concatenateString(0, "runtime", 7);
    uVar6 = concatenateString(uVar6, "~cubemap", 8);
    setDebugName(uVar6, g_cubeMapTexture, 1);

    uVar6 = concatenateString(0, "runtime", 7);
    uVar6 = concatenateString(uVar6, "~cubemapsky", 0xb);
    setDebugName(uVar6, g_cubeMapSkyTexture, 1);

    iVar3 = g_cubeMapResolution;

    // Check render target array for main cubemap allocation
    // g_renderTargetArray is array of structs (size 0x38) indexed by g_mainCubeTargetIndex
    // Structure at g_renderTargetBase + index*0x38: +0x02 is width?, +0x04 is height? (uint16)
    // Condition: if width*height < resolution*resolution then create a new render target (texture) with -1 handle?
    if (g_mainCubeTargetIndex < 0x1000) {
        puVar2 = (void*)(g_renderTargetBase + g_mainCubeTargetIndex * 0x38);
    } else {
        puVar2 = NULL;
    }

    if (puVar2 && ((int)(*(uint16_t*)((int)puVar2 + 4) * *(uint16_t*)((int)puVar2 + 2)) < resolution * resolution)) {
        uVar7 = 0xffffffff; // use auto mip level?
    LAB_004132a6:
        g_mainCubeRT = createTexture(3, 0x200018, iVar3, iVar3, 1, uVar7);
    } else if (g_mainCubeTargetIndex < 0x1000 && g_mainCubeTargetIndex * 0x38 != -0x11a0f28) {
        uVar7 = getRandomValue(); // or some other function returning int
        if (uVar7 < 0x1000) {
            void* ptr = (void*)(g_renderTargetBase + uVar7 * 0x38);
            if (ptr != NULL) {
                if (*(byte*)ptr < 2) goto LAB_004132a6;
                g_mainCubeRT = 0xffffffff;
            } else {
                g_mainCubeRT = 0xffffffff;
            }
        } else {
            g_mainCubeRT = 0xffffffff;
        }
    } else {
        g_mainCubeRT = 0xffffffff;
    }

    // Same logic for second render target (maybe face-specific?)
    iVar3 = g_cubeMapResolution;
    if (g_secondCubeTargetIndex < 0x1000) {
        puVar2 = (void*)(g_renderTargetBase + g_secondCubeTargetIndex * 0x38);
    } else {
        puVar2 = NULL;
    }

    if (puVar2 && ((int)(*(uint16_t*)((int)puVar2 + 4) * *(uint16_t*)((int)puVar2 + 2)) < resolution * resolution)) {
        uVar7 = 0xffffffff;
    LAB_00413357:
        g_secondCubeRT = createTexture(3, 0x200018, iVar3, iVar3, 1, uVar7);
    } else if (g_secondCubeTargetIndex < 0x1000 && g_secondCubeTargetIndex * 0x38 != -0x11a0f28) {
        uVar7 = getRandomValue();
        if (uVar7 < 0x1000) {
            void* ptr = (void*)(g_renderTargetBase + uVar7 * 0x38);
            if (ptr != NULL) {
                if (*(byte*)ptr < 2) goto LAB_00413357;
                g_secondCubeRT = 0xffffffff;
            } else {
                g_secondCubeRT = 0xffffffff;
            }
        } else {
            g_secondCubeRT = 0xffffffff;
        }
    } else {
        g_secondCubeRT = 0xffffffff;
    }

    // Allocate depth/stencil buffer for cubemap
    iVar3 = g_cubeMapResolution;
    if (g_depthStencilIndex < 0x1000) {
        puVar2 = (void*)(g_renderTargetBase + g_depthStencilIndex * 0x38);
    } else {
        puVar2 = NULL;
    }

    if (puVar2 && ((int)(*(uint16_t*)((int)puVar2 + 4) * *(uint16_t*)((int)puVar2 + 2)) < resolution * resolution)) {
        uVar7 = 0xffffffff;
    } else {
        if (g_depthStencilIndex >= 0x1000 || g_depthStencilIndex * 0x38 == -0x11a0f28) {
            g_depthRT = 0xffffffff;
            goto LAB_00413420;
        }
        uVar7 = getRandomValue();
        if (uVar7 >= 0x1000 || (void*)(g_renderTargetBase + uVar7 * 0x38) == NULL) {
            g_depthRT = 0xffffffff;
            goto LAB_00413420;
        }
        if (*(byte*)(g_renderTargetBase + uVar7 * 0x38) > 1) {
            g_depthRT = 0xffffffff;
            goto LAB_00413420;
        }
    }
    g_depthRT = createTexture(0x1a, 0x200018, iVar3, iVar3, 1, uVar7);

LAB_00413420:
    // Check if we need to create sky depth RT
    if (g_rendererMode != 1 && g_rendererMode != 2) {
        someResetFunction(); // probably reset state
    }

    if (g_depthStencilIndex < 0x1000 && g_depthStencilIndex * 0x38 != -0x11a0f28) {
        uVar7 = getRandomValue();
        if (uVar7 < 0x1000) {
            void* ptr = (void*)(g_renderTargetBase + uVar7 * 0x38);
            if (ptr != NULL) {
                if (*(byte*)ptr < 2) {
                    g_skyDepthRT = createTexture(0x1a, 0x200018, 0x100, 0x100, 1, uVar7);
                } else {
                    g_skyDepthRT = 0xffffffff;
                }
            } else {
                g_skyDepthRT = 0xffffffff;
            }
        } else {
            g_skyDepthRT = 0xffffffff;
        }
    } else {
        g_skyDepthRT = 0xffffffff;
    }

    if (g_rendererMode != 1 && g_rendererMode != 2) {
        someResetFunction();
    }

    // Find the class ID for "SM_QuadEffectClass"
    iVar3 = findClassID("SM_QuadEffectClass");

    // Search the class list for that ID
    g_foundClassEntry = g_classListHead;
    while (g_foundClassEntry != 0) {
        if (iVar3 == *(int*)(g_foundClassEntry + 8)) goto LAB_004134ee;
        g_foundClassEntry = *(int*)(g_foundClassEntry + 4);
    }
    g_foundClassEntry = 0;

LAB_004134ee:
    // Get the dynamic cube renderer instance
    iVar3 = getDynCubeRenderObject(); // returns pointer to DynCubeRender object
    g_dynCubeRenderObject = iVar3;

    // Set some engine global parameters on the renderer
    setGlobalRenderingParam(g_engineGlobal, 1.0f);
    *(uint32_t*)(iVar3 + 0x144) = g_someEngineValue; // e.g., render context
    *(uint32_t*)(iVar3 + 0x148) = g_cubeMapSize2; // maybe face size

    resetDynCubeState(); // possibly clear render lists

    // Build command list for rendering dynamic cubemap
    uVar6 = g_someEngineValue;
    if (*(int*)(**(int**)(unaff_FS_OFFSET + 0x2c) + 0x34) == 0) {
        // Push command to set render target (cubemap)
        piVar4 = (int*)(g_commandBuffer + 0x14);
        **(int**)(g_commandBuffer + 0x14) = &g_cmdSetRenderTarget;
        *piVar4 = *piVar4 + 4;
        *(int*)*piVar4 = iVar3; // object
        iVar1 = *piVar4;
        *(int*)(iVar1 + 4) = uVar6; // engine value
        *(int*)(iVar1 + 8) = g_cubeMapSize2;
        *piVar4 = iVar1 + 0xc;
    }

    // Push command for set viewport
    piVar4 = (int*)(g_commandBuffer + 0x14);
    **(int**)(g_commandBuffer + 0x14) = &g_cmdSetViewport;
    *piVar4 = *piVar4 + 4;
    *(int*)*piVar4 = iVar3;
    *piVar4 = *piVar4 + 4;

    // Push command for clear? (then another: set stencil?)
    piVar4 = (int*)(g_commandBuffer + 0x14);
    **(int**)(g_commandBuffer + 0x14) = &g_cmdClear; // actually pointer to structure with opcode
    *piVar4 = *piVar4 + 4;
    *(int*)*piVar4 = iVar3;
    *piVar4 = *piVar4 + 4;

    // Register the cubemap as a render target in the system list
    uVar7 = 0;
    g_cubeMapRenderTargetCount = 0;
    local_4 = 0x80; // flag for "immediate" or "active"?
    g_lastCubeMapRT = iVar3;

    if (g_renderTargetListCount != 0) {
        pbVar5 = g_renderTargetListEntries; // array of structs (size 0xc per entry)
        do {
            if (0x80 < *pbVar5) {
                // Error: size exceeds limit
                triggerCriticalError();
                return;
            }
            uVar7 = uVar7 + 1;
            pbVar5 = pbVar5 + 0xc;
        } while (uVar7 < g_renderTargetListCount);
    }

    if (g_renderTargetListCount < 0x20) {
        iVar3 = g_renderTargetListCount * 0xc;
        // Set entry: magic/type = 0x41309000000000? Actually 8 bytes: 0x413090 << 32 + 0? But represented as undefined8
        *(int64_t*)(g_renderTargetListBase + g_renderTargetListCount * 3) = 0x41309000000000LL;
        // Set flags: 0x80
        *(int*)(g_renderTargetListEntries + iVar3) = local_4;
        g_renderTargetListCount++;
    }

    return;
}
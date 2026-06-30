// FUNC_NAME: CameraTransition::executeFadeTransition

uint CameraTransition::executeFadeTransition(uint entityIndex, float startValue, float endValue, float duration, char enableAdditionalSetup, int frameCount, char enableCleanup)
{
    ushort width;
    ushort height;
    undefined4 uVar3;
    undefined4 uVar4;
    uint savedFlags;
    int iVar6;
    float fVar7;
    undefined4 local_uVar8;
    uint uVar9;
    uint uVar10;
    uint basePtr;
    undefined4 *allocatedBlock;
    uint savedCameraId;
    float fVar14;
    float fVar15;
    undefined4 uVar16;
    undefined4 uStack_54;
    int local_48;
    
    // Clamp system state flags to valid ranges
    if (g_systemState1 < 7) {
        g_systemState1 = 7;
    }
    if (7 < g_systemState2) {
        g_systemState2 = 7;
    }
    g_someFlag1 = 0;
    if (g_systemState1 < 0x16) {
        g_systemState1 = 0x16;
    }
    if (0x16 < g_systemState2) {
        g_systemState2 = 0x16;
    }
    g_someFlag2 = 1;
    FUN_00417cf0(1, 2, 1); // Sets up some state (1,2,1)
    
    uVar10 = g_cameraPair[0]; // store first camera index
    uVar9 = g_cameraPair[1];  // store second camera index
    local_uVar8 = g_cameraFlags2;
    uVar16 = g_cameraFlags1;
    
    if (g_systemState1 < 0x1b) {
        g_systemState1 = 0x1b;
    }
    if (0x1a < g_systemState2) {
        g_systemState2 = 0x1b;
    }
    g_someFlag3 = 1;
    
    // Retrieve object data for first camera
    if (uVar9 < 0x1000) {
        basePtr = (uint)&g_entityArray + uVar9 * 0x38;
    } else {
        basePtr = 0;
    }
    uVar3 = *(undefined4 *)(basePtr + 0xc); // object flags? +0x0C
    
    // Retrieve object data for second camera
    if (uVar10 < 0x1000) {
        basePtr = (uint)&g_entityArray + uVar10 * 0x38;
    } else {
        basePtr = 0;
    }
    uVar4 = *(undefined4 *)(basePtr + 0xc); // object flags? +0x0C
    
    g_cameraFlags1 = uVar9; // set current camera to first
    g_cameraFlags2 = 0;
    FUN_00609340(0, uVar16, local_uVar8); // set viewport/projection
    FUN_0060db60(0, 0, 0, 0x3f800000, 0x3f800000); // clear? set color?
    
    // Retrieve flags for input entity
    if (entityIndex < 0x1000) {
        basePtr = (uint)&g_entityArray + entityIndex * 0x38;
    } else {
        basePtr = 0;
    }
    savedFlags = *(uint *)(basePtr + 0xc);
    
    FUN_00606e60(entityIndex, 0); // reset flags on input entity
    g_stateEntityType = 0xf; // set state type
    g_stateData1 = g_stateData4; // copy state data
    g_stateData2 = g_stateData5;
    
    if (g_singletonPtr == &g_globalState) {
        FUN_0060a460(g_stateData4); // apply state data
    }
    FUN_00611500(); // update state?
    
    savedCameraId = g_previousCameraId;
    // Disable previous camera if valid
    if ((g_previousCameraId != 0xffffffff) && (g_previousCameraId < 0x1000)) {
        iVar6 = g_previousCameraId * 0x38;
        if ((&g_entityArray + iVar6 != (byte *)0x0) && ((byte)(&g_entityArray)[iVar6] < 4)) {
            if (*(int *)(&g_entityArray[0x44] + iVar6) != 0) {
                FUN_00606e60(*(int *)(&g_entityArray[0x44] + iVar6), 0x210000); // set flags with 0x210000
            }
            *(uint *)(&g_entityArray[0x34] + iVar6) = *(uint *)(&g_entityArray[0x34] + iVar6) & 0xfcad8fff | 0x210000;
            FUN_006189c0(); // apply changes
        }
    }
    g_currentCameraId = savedCameraId;
    
    if ((g_singletonPtr == &g_globalState) && (g_stateFlags != 0)) {
        FUN_006063b0(); // commit state change
    }
    FUN_00609810(1);
    
    // Set up fade parameters
    g_fadeRange = endValue - startValue;
    g_fadeDurationInv = g_screenHeight / duration; // inverse of duration? Actually DAT_00e2b1a4 is screenHeight? It's 1.0? Wait: it's a float value, likely aspect ratio or something.
    
    // Get entity dimensions for aspect ratio calculation
    if (entityIndex < 0x1000) {
        basePtr = (uint)&g_entityArray + entityIndex * 0x38;
    } else {
        basePtr = 0;
    }
    width = *(ushort *)(basePtr + 2); // +0x02 width? Or maybe sub-division count?
    
    if (entityIndex < 0x1000) {
        basePtr = (uint)&g_entityArray + entityIndex * 0x38;
    } else {
        basePtr = 0;
    }
    height = *(ushort *)(basePtr + 4); // +0x04 height?
    
    g_fadeStart = startValue;
    g_fadeCurrent = 0;
    g_fadeUnknown1 = 0;
    g_fadeUnknown2 = 0;
    g_fadeSourceRegion[0] = DAT_011f6a9c; // +0x28
    g_fadeSourceRegion[1] = DAT_011f6aac;
    
    // Send fade start command to state machine
    if ((g_singletonPtr == &g_globalState) && (g_stateFadeCallback != 0)) {
        FUN_0060aea0(g_stateData1, g_stateFadeCallback, &g_fadeStart, 2); // send data with two floats
    }
    g_fadeEntityIndex = entityIndex;
    
    if ((g_singletonPtr == &g_globalState) && (g_stateModified != 0)) {
        FUN_006063b0();
    }
    
    // Calculate aspect ratios based on entity dimensions
    fVar15 = g_screenHeight / (float)width;
    fVar14 = g_screenHeight / (float)height;
    g_aspectWidth = fVar15;
    g_aspectHeight = fVar14;
    
    if ((g_singletonPtr == &g_globalState) && (g_stateAspectCallback != 0)) {
        FUN_0060ac80(g_stateData2, g_stateAspectCallback, &g_aspectWidth);
    }
    FUN_00611850(); // update state again
    
    // Calculate offset values
    fVar15 = ((float)width - g_screenHeight) * fVar15;
    fVar14 = ((float)height - g_screenHeight) * fVar14;
    
    // Allocate a 16-float block for rendering? (0xd = size, 4 = type?)
    allocatedBlock = (undefined4 *)FUN_0060cd00(0xd, 4, 0, 1, 0);
    uVar16 = g_someFloat1;
    fVar7 = g_screenHeight;
    if (allocatedBlock != (undefined4 *)0x0) {
        // Fill with coordinates for a textured quad? Possibly a fullscreen overlay for fade
        allocatedBlock[1] = g_screenHeight;   // bottom-left y
        *allocatedBlock = uVar16;            // top-left x
        allocatedBlock[2] = 0;                // u?
        allocatedBlock[3] = 0;                // v?
        allocatedBlock[4] = fVar7;            // top-right x
        allocatedBlock[5] = fVar7;            // bottom-right x?
        allocatedBlock[6] = fVar15;           // ?
        allocatedBlock[7] = 0;
        allocatedBlock[8] = fVar7;            // 
        allocatedBlock[9] = uVar16;
        allocatedBlock[10] = fVar15;
        allocatedBlock[0xb] = fVar14;
        allocatedBlock[0xc] = uVar16;
        allocatedBlock[0xd] = uVar16;
        allocatedBlock[0xe] = 0;
        allocatedBlock[0xf] = fVar14;
        FUN_0060cde0(); // submit the block
    }
    FUN_00612e00(); // render?
    FUN_00609890(1); // present?
    
    // Loop for frameCount iterations: perform a fade between two cameras
    if (0 < frameCount) {
        local_48 = frameCount;
        do {
            // --- First half of fade: from first camera to second? ---
            uVar16 = g_cameraFlags2;
            uVar13 = g_cameraFlags1;
            g_cameraFlags1 = uVar10; // switch camera to second?
            g_cameraFlags2 = 0;
            FUN_00609340(0, uVar13, uVar16);
            FUN_0060db60(0, 0, 0, 0x3f800000, 0x3f800000);
            
            uVar16 = someGlobalIndex;
            (**(code **)(*g_renderDevice + 0xac))(g_renderDevice, 1, &someTexture, 1, uVar16, someOtherGlobal1, someOtherGlobal2);
            
            FUN_00606e60(uVar9, uStack_54); // apply flags? uStack_54 is uninitialized!
            g_stateEntityType = 5;
            g_stateData1 = g_stateData6;
            g_stateData2 = g_stateData7;
            if (g_singletonPtr == &g_globalState) {
                FUN_0060a460(g_stateData6);
            }
            FUN_00611500();
            g_overlayFlags = 0;
            g_fadeEntityIndex = uVar9; // switch entity index
            if ((g_singletonPtr == &g_globalState) && (g_stateModified != 0)) {
                FUN_006063b0();
            }
            FUN_00611850();
            
            // Allocate and fill a similar block (but with different data?)
            allocatedBlock = (undefined4 *)FUN_0060cd00(0xd, 4, 0, 1, 0);
            uVar8 = g_someFloat1;
            fVar15 = g_screenHeight;
            if (allocatedBlock != (undefined4 *)0x0) {
                *allocatedBlock = g_someFloat1;
                allocatedBlock[1] = fVar15;
                allocatedBlock[2] = fVar15;
                allocatedBlock[3] = fVar15;
                allocatedBlock[4] = fVar15;
                allocatedBlock[5] = uVar8;
                allocatedBlock[6] = uVar8;
                allocatedBlock[7] = uVar8;
                FUN_0060cde0();
            }
            if (g_unknownState != 0) {
                uVar13 = g_unknownState & 0xff;
                if ((&g_stateArray)[g_stateData1 * 0x10] != '\0') {
                    uVar13 = uVar13 + 0x10;
                }
                FUN_00618d40(); // some state update
                (&g_resultBuffer)[uVar13] = 0;
            }
            g_singletonPtr = (undefined **)0x0;
            g_singletonFlags = 0;
            FUN_00609890(1);
            
            // --- Second half of fade: from second back to first? ---
            uVar8 = g_cameraFlags2;
            uVar13 = g_cameraFlags1;
            g_cameraFlags1 = uVar9; // switch camera to first
            g_cameraFlags2 = 0;
            FUN_00609340(0, uVar13, uVar8);
            FUN_0060db60(0, 0, 0, 0x3f800000, 0x3f800000);
            FUN_00606e60(uVar16, unaff_EBX); // unaff_EBX is uninitialized! potential bug?
            (**(code **)(*g_renderDevice + 0xac))(g_renderDevice, 1, &someTexture, 1, someGlobalIndex, someOtherGlobal1, someOtherGlobal2);
            
            g_stateEntityType = 5;
            g_stateData1 = g_stateData6;
            g_stateData2 = g_stateData7;
            if (g_singletonPtr == &g_globalState) {
                FUN_0060a460(g_stateData6);
            }
            FUN_00611500();
            g_overlayFlags = 1; // flip overlay flag?
            g_fadeEntityIndex = uVar10; // switch entity index again
            if ((g_singletonPtr == &g_globalState) && (g_stateModified != 0)) {
                FUN_006063b0();
            }
            FUN_00611850();
            
            allocatedBlock = (undefined4 *)FUN_0060cd00(0xd, 4, 0, 1, 0);
            uVar16 = g_someFloat1;
            fVar15 = g_screenHeight;
            if (allocatedBlock != (undefined4 *)0x0) {
                *allocatedBlock = g_someFloat1;
                allocatedBlock[1] = fVar15;
                allocatedBlock[2] = fVar15;
                allocatedBlock[3] = fVar15;
                allocatedBlock[4] = fVar15;
                allocatedBlock[5] = uVar16;
                allocatedBlock[6] = uVar16;
                allocatedBlock[7] = uVar16;
                FUN_0060cde0();
            }
            if (g_unknownState != 0) {
                uVar13 = g_unknownState & 0xff;
                if ((&g_stateArray)[g_stateData1 * 0x10] != '\0') {
                    uVar13 = uVar13 + 0x10;
                }
                FUN_00618d40();
                (&g_resultBuffer)[uVar13] = 0;
            }
            g_singletonPtr = (undefined **)0x0;
            g_singletonFlags = 0;
            FUN_00609890(1);
            
            local_48 = local_48 + -1;
        } while (local_48 != 0);
    }
    
    // If additional setup flag is set, perform final setup and possibly cleanup
    uVar16 = g_cameraFlags2;
    uVar13 = g_cameraFlags1;
    if (enableAdditionalSetup != '\0') {
        g_cameraFlags1 = entityIndex;
        g_cameraFlags2 = 0;
        FUN_00609340(0, uVar13, uVar16);
        FUN_0060db60(0, 0, 0, 0x3f800000, 0x3f800000);
        
        // Disable uVar9 (second camera) if valid
        if ((uVar9 != 0xffffffff) && (uVar9 < 0x1000)) {
            iVar6 = uVar9 * 0x38;
            if ((&g_entityArray + iVar6 != (byte *)0x0) && ((byte)(&g_entityArray)[iVar6] < 4)) {
                if (*(int *)(&g_entityArray[0x44] + iVar6) != 0) {
                    FUN_00606e60(*(int *)(&g_entityArray[0x44] + iVar6), 0x200000);
                }
                *(uint *)(&g_entityArray[0x34] + iVar6) = *(uint *)(&g_entityArray[0x34] + iVar6) & 0xfcac8fff | 0x200000;
                FUN_006189c0();
            }
        }
        
        if (enableCleanup != '\0') {
            FUN_0042ac10(); // perform cleanup
        }
        
        g_stateEntityType = 6;
        g_stateData1 = g_stateData8;
        g_stateData2 = g_stateData9;
        if (g_singletonPtr == &g_globalState) {
            FUN_0060a460(g_stateData8);
        }
        FUN_00611500();
        g_fadeEntityIndex = uVar9;
        if ((g_singletonPtr == &g_globalState) && (g_stateModified != 0)) {
            FUN_006063b0();
        }
        FUN_00611850();
        FUN_00417cf0(1, 5, 6);
        
        // Clamp system state again
        if (g_systemState1 < 0x1b) {
            g_systemState1 = 0x1b;
        }
        if (0x1a < g_systemState2) {
            g_systemState2 = 0x1b;
        }
        g_someFlag3 = 1;
        
        // Allocate another block
        allocatedBlock = (undefined4 *)FUN_0060cd00(0xd, 4, 0, 1, 0);
        uVar16 = g_someFloat1;
        fVar15 = g_screenHeight;
        if (allocatedBlock != (undefined4 *)0x0) {
            *allocatedBlock = g_someFloat1;
            allocatedBlock[1] = fVar15;
            allocatedBlock[2] = 0;
            allocatedBlock[3] = 0;
            allocatedBlock[4] = fVar15;
            allocatedBlock[5] = fVar15;
            allocatedBlock[6] = fVar15;
            allocatedBlock[7] = 0;
            allocatedBlock[8] = fVar15;
            allocatedBlock[9] = uVar16;
            allocatedBlock[10] = fVar15;
            allocatedBlock[0xb] = fVar15;
            allocatedBlock[0xc] = uVar16;
            allocatedBlock[0xd] = uVar16;
            allocatedBlock[0xe] = 0;
            allocatedBlock[0xf] = fVar15;
            FUN_0060cde0();
        }
        if (g_unknownState != 0) {
            uVar13 = g_unknownState & 0xff;
            if ((&g_stateArray)[g_stateData1 * 0x10] != '\0') {
                uVar13 = uVar13 + 0x10;
            }
            FUN_00618d40();
            (&g_resultBuffer)[uVar13] = 0;
        }
        g_singletonPtr = (undefined **)0x0;
        g_singletonFlags = 0;
        if (enableCleanup != '\0') {
            FUN_00619210(); // final cleanup
        }
        FUN_00609890(1);
    }
    
    // Restore flags for entities
    FUN_00606e60(entityIndex, savedFlags & 0x30000);
    FUN_00606e60(uVar9, uVar3);
    FUN_00606e60(uVar10, uVar4);
    FUN_00417cf0(1, 5, 6);
    
    if (g_systemState1 < 0x1b) {
        g_systemState1 = 0x1b;
    }
    if (0x1a < g_systemState2) {
        g_systemState2 = 0x1b;
    }
    g_someFlag3 = 0;
    
    if (g_systemState1 < 0x16) {
        g_systemState1 = 0x16;
    }
    if (0x16 < g_systemState2) {
        g_systemState2 = 0x16;
    }
    g_someFlag2 = 2;
    
    if (g_systemState1 < 7) {
        g_systemState1 = 7;
    }
    g_someFlag1 = 1;
    if (7 < g_systemState2) {
        g_systemState2 = 7;
    }
    
    return g_cameraFlags1; // return current camera index
}
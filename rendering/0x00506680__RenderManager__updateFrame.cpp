// FUNC_NAME: RenderManager::updateFrame
// Address: 0x00506680
// Description: Processes the renderable object list for the current frame.
// Handles first-time initialization vs subsequent frames, performs per-object
// bounding box culling, fills a vertex buffer, and updates various render states.
// If bClearList is true, resets the root list pointer after processing.

// Global references (inferred from context):
// gRenderManager: at DAT_0120550c, points to a RenderManager instance.
// gRenderManager->frameStartedFlag: at offset 0x894 (bool)
// gRenderManager->nodeCount: at offset 0x16c
// gRenderManager->maxNodeCount: at offset 0x170
// gSceneReady: at DAT_0120575b (bool)
// gFrameCounter: at DAT_01205500 (int)
// gRootNodeList: at DAT_012054dc (pointer to node list structure)
// gDisplayWidth: at DAT_012058d0 (int)
// gDisplayHeight: at DAT_00f15988 (int)
// Various global render state constants:
//   DAT_011f3a30, DAT_011f39f4, DAT_011f3a10, DAT_011f3a3c, etc.

void RenderManager::updateFrame(bool bClearList) {
    RenderManager* mgr = gRenderManager;
    if (!gSceneReady) {
        initializeRenderSystem();
        return;
    }

    // Get the root node list from the render manager
    NodeList* rootList = getRootNodeList(mgr);
    int* currentFrame = &gFrameCounter;  // DAT_01205500

    // Dereference rootList to get the first renderable node pointer
    RenderNode** firstNodePtr = reinterpret_cast<RenderNode**>(*rootList);
    RenderNode* firstNode = *firstNodePtr;

    if (firstNode == nullptr) {
        // First-time frame setup or empty list
        if (mgr->frameStartedFlag == 0) {
            // Capture initial state
            int initialFrameCounter = *currentFrame;
            int nodeCount = DAT_012058a4;  // default if no manager
            if (gRootNodeList != nullptr) {
                nodeCount = gRootNodeList->nodeCount;
            }

            // Increment frame counter
            *currentFrame = *currentFrame + 1;

            int tempNodeCount = DAT_012058a4;
            int maxNodeCount = DAT_012058a8;
            if (gRootNodeList != nullptr) {
                tempNodeCount = gRootNodeList->nodeCount;
                maxNodeCount = gRootNodeList->maxNodeCount;
            }

            // If list is full, adjust frame counter to avoid wrap issues
            if (maxNodeCount == tempNodeCount) {
                *currentFrame = initialFrameCounter + 2;
            }

            // Push identity matrix, set default color
            pushWorldMatrix();
            setColor(0, 0, 0, 1.0f, 1.0f);  // RGBA: 0,0,0,1,1 ? possibly clear color
            enableDepthTest(true);           // probably glEnable(GL_DEPTH_TEST)
            enableAlphaBlend(true);          // glEnable(GL_BLEND)
            flushCommandBuffer();            // force draw

            // Mark frame as started and perform consistency check
            mgr->frameStartedFlag = 1;
            int currentGlobalCount = DAT_012058a4;
            if (gRootNodeList != nullptr) {
                currentGlobalCount = gRootNodeList->nodeCount;
            }
            if (maxNodeCount == currentGlobalCount) {
                *currentFrame = *currentFrame - 1;
            }

            if (gRootNodeList != nullptr) {
                currentGlobalCount = gRootNodeList->nodeCount;
            }
            if (nodeCount == currentGlobalCount) {
                *currentFrame = *currentFrame - 1;
                *rootList = 0;           // clear root list
                rootList->nodeCount = 0;
                return;
            }
            goto RESET_LIST;
        }
    } else {
        // Normal frame processing: list is non-empty
        int nodeCountStart = (gRootNodeList != nullptr) ? gRootNodeList->nodeCount : DAT_012058a4;

        *currentFrame = *currentFrame + 1;

        int maxCount = (gRootNodeList != nullptr) ? gRootNodeList->maxNodeCount : DAT_012058a8;
        int currentCount = (gRootNodeList != nullptr) ? gRootNodeList->nodeCount : DAT_012058a4;

        if (maxCount == currentCount) {
            *currentFrame = *currentFrame + 1;  // increment again if full
        }

        // Swap in new render states (probably for a different layer/pass)
        DAT_0121a204 = DAT_0121a35c;
        DAT_0121a200 = DAT_0121a358;

        // Release previous resources if necessary
        if (DAT_012058e8 == &DAT_0121a1f0) {
            releaseTextureOrBuffer(DAT_0121a35c);
            releaseTextureOrBuffer(DAT_0121a200);
        }

        int currentMaxCount = (gRootNodeList != nullptr) ? gRootNodeList->maxNodeCount : DAT_012058a8;
        setRenderState(currentMaxCount, 0x210000);  // some render state

        clearRenderBuffer();  // FUN_00536940

        // Update a list of per-object flags (D3DRS or OpenGL state)
        int renderTargetIdx = DAT_01218ee8;
        uint idx = 0;
        do {
            if (gRenderTargetList[idx] == renderTargetIdx) {  // DAT_01218e50
                if (idx < 20) {
                    gRenderTargetFlags[idx] &= 0xfffffffc;   // clear low 2 bits
                }
                break;
            }
            idx++;
        } while (idx < 20);

        // Store old camera matrix, then set new
        uint oldCamData2 = DAT_011f38f4;
        int oldCamData1 = DAT_011f38f0;
        DAT_011f38f0 = renderTargetIdx;
        DAT_011f38f4 = 0;
        setCameraMatrix(0, oldCamData1, oldCamData2);  // FUN_00609340

        setColor(0, 0, 0, 1.0f, 1.0f);

        // Check if camera changed and trigger event
        bool camChanged = (DAT_011f3910 != 0) || (DAT_011f3914 != 0);
        DAT_011f3910 = 0;
        DAT_011f3914 = 0;
        if (camChanged) {
            // Call vtable method at index 0x9c (probably onCamChanged)
            (*(void (__thiscall**)(RenderManager*, int))(*DAT_01205750 + 0x9c))(DAT_01205750, 0);
        }

        enableDepthTest(true);

        // Clamp display dimensions (D3DRS_Viewport?)
        if (DAT_012058d0 < 0x16) DAT_012058d0 = 0x16;
        if (0x16 < DAT_00f15988) DAT_00f15988 = 0x16;
        _DAT_011f3a30 = 1;

        if (DAT_012058d0 < 7) DAT_012058d0 = 7;
        if (7 < DAT_00f15988) DAT_00f15988 = 7;
        _DAT_011f39f4 = 0;

        if (DAT_012058d0 < 0xe) DAT_012058d0 = 0xe;
        if (0xe < DAT_00f15988) DAT_00f15988 = 0xe;
        _DAT_011f3a10 = 0;

        if (DAT_012058d0 < 0x19) DAT_012058d0 = 0x19;
        if (0x19 < DAT_00f15988) DAT_00f15988 = 0x19;
        _DAT_011f3a3c = 5;

        if (DAT_012058d0 < 0x18) DAT_012058d0 = 0x18;
        if (0x18 < DAT_00f15988) DAT_00f15988 = 0x18;
        _DAT_011f3a38 = 0;

        if (DAT_012058d0 < 0xf) DAT_012058d0 = 0xf;
        if (0xf < DAT_00f15988) DAT_00f15988 = 0xf;
        _DAT_011f3a14 = 0;

        if (DAT_012058d0 < 0x1b) DAT_012058d0 = 0x1b;
        if (0x1a < DAT_00f15988) DAT_00f15988 = 0x1b;
        _DAT_011f3a44 = 0;

        setViewport();  // FUN_00536550

        // Allocate vertex buffer for all nodes
        float* vertexData = static_cast<float*>(allocateVertexBuffer(1, rootList->nodeCount, 0, 1, 0));
        float fMulX = DAT_00e445e4;
        float fMulY = DAT_00e2ee80;
        float fAdd = DAT_00e2cd54;

        if (vertexData != nullptr) {
            RenderNode* currentNode = firstNode;
            for (int i = rootList->nodeCount; i != 0; i--) {
                // Write 10 floats per node (position + attributes)
                vertexData[0] = (static_cast<float>(currentNode->screenX) + fAdd) * fMulX;
                vertexData[1] = (static_cast<float>(currentNode->screenY) + fAdd) * fMulY;
                vertexData[2] = static_cast<float>(currentNode->depth);
                vertexData[3] = static_cast<float>(currentNode->colorR);
                vertexData[4] = static_cast<float>(currentNode->colorG);
                vertexData[5] = static_cast<float>(currentNode->colorB);
                vertexData[6] = gClipMinX;    // DAT_01218e44
                vertexData[7] = gClipMinY;    // DAT_01218e48
                vertexData[8] = static_cast<float>(currentNode->materialIdx);
                vertexData[9] = static_cast<float>(currentNode->textureIdx);

                // Check bounding box visibility (frustum culling)
                // If (depth + colorR) < 0 or (depth - colorR) > some threshold -> invisible
                // If (colorG + colorB) < 0 or (colorG - colorB) > some threshold -> invisible
                bool visible;
                float sum1 = static_cast<float>(currentNode->depth) + static_cast<float>(currentNode->colorR);
                float diff1 = static_cast<float>(currentNode->depth) - static_cast<float>(currentNode->colorR);
                if ((sum1 < 0.0f) || (diff1 > static_cast<float>(gFrustumThresholdX))) {
                    visible = false;
                } else {
                    float sum2 = static_cast<float>(currentNode->colorG) + static_cast<float>(currentNode->colorB);
                    float diff2 = static_cast<float>(currentNode->colorG) - static_cast<float>(currentNode->colorB);
                    if ((sum2 < 0.0f) || (diff2 > static_cast<float>(gFrustumThresholdY))) {
                        visible = false;
                    } else {
                        visible = true;
                    }
                }
                currentNode->visibilityFlag = visible ? 1 : 0;

                vertexData += 10;
                currentNode = currentNode->next;
            }
            unlockVertexBuffer();  // FUN_0060cde0
        }

        finalizeFrame();  // FUN_00612e00

        // Reset some states
        DAT_0121a310 = 0;
        DAT_0121a314 = 0;
        DAT_0121a318 = 0;

        enableAlphaBlend(true);
        flushCommandBuffer();

        // Apply second set of render state clamps (different values)
        if (DAT_012058d0 < 0x16) DAT_012058d0 = 0x16;
        if (0x16 < DAT_00f15988) DAT_00f15988 = 0x16;
        _DAT_011f3a30 = 1;

        if (DAT_012058d0 < 7) DAT_012058d0 = 7;
        if (7 < DAT_00f15988) DAT_00f15988 = 7;
        _DAT_011f39f4 = 1;

        if (DAT_012058d0 < 0xe) DAT_012058d0 = 0xe;
        if (0xe < DAT_00f15988) DAT_00f15988 = 0xe;
        _DAT_011f3a10 = 1;

        if (DAT_012058d0 < 0x19) DAT_012058d0 = 0x19;
        if (0x19 < DAT_00f15988) DAT_00f15988 = 0x19;
        _DAT_011f3a3c = 7;

        if (DAT_012058d0 < 0x18) DAT_012058d0 = 0x18;
        if (0x18 < DAT_00f15988) DAT_00f15988 = 0x18;
        _DAT_011f3a38 = 0;

        if (DAT_012058d0 < 0xf) DAT_012058d0 = 0xf;
        if (0xf < DAT_00f15988) DAT_00f15988 = 0xf;
        _DAT_011f3a14 = 0;

        if (DAT_012058d0 < 0x1b) DAT_012058d0 = 0x1b;
        if (0x1a < DAT_00f15988) DAT_00f15988 = 0x1b;
        _DAT_011f3a44 = 0;

        sortRenderables(1, 5, 6);  // FUN_00417cf0 (sort by depth, etc.)

        int frameStartedMgrOff = reinterpret_cast<int>(gRootNodeList);
        bool mgrExists = (gRootNodeList != nullptr);
        mgr->frameStartedFlag = 1;
        int currentCount2 = (mgrExists) ? gRootNodeList->nodeCount : DAT_012058a4;
        if (maxCount == currentCount2) {
            *currentFrame = *currentFrame - 1;
        }
        int currentCount3 = (mgrExists) ? gRootNodeList->nodeCount : DAT_012058a4;
        if (nodeCountStart == currentCount3) {
            *currentFrame = *currentFrame - 1;
        }
    }

    if (!bClearList) {
        return;
    }

RESET_LIST:
    *firstNodePtr = nullptr;
    rootList->nodeCount = 0;
    return;
}
// FUNC_NAME: PostProcessManager::updateSettings
void __thiscall PostProcessManager::updateSettings(void* this) {
    // Called from 0x005149c0 and 0x00515c20 (likely main render loop)
    // Updates global fog/depth parameters and shader uniforms

    // Push/pop render state group (1,2,1) or set group
    setRenderStateGroup(1, 2, 1);

    // Clamp global intensity bounds per channel (or per slot)
    // First slot: intensity range [0x16 (22), 0x16] and enable flag
    if (g_fogIntensityMin < 0x16) {
        g_fogIntensityMin = 0x16; // 22
    }
    if (0x16 < g_fogIntensityMax) {
        g_fogIntensityMax = 0x16;
    }
    g_fogSlotEnabled[0] = 1;

    // Second slot: range [7,7], disable flag
    if (g_fogIntensityMin < 7) {
        g_fogIntensityMin = 7;
    }
    if (7 < g_fogIntensityMax) {
        g_fogIntensityMax = 7;
    }
    g_fogSlotEnabled[1] = 0;

    // Third slot: range [0xe (14), 0xe], disable flag
    if (g_fogIntensityMin < 0xe) {
        g_fogIntensityMin = 0xe;
    }
    if (0xe < g_fogIntensityMax) {
        g_fogIntensityMax = 0xe;
    }
    g_fogSlotEnabled[2] = 0;

    // Fourth slot: range [0x19 (25), 0x19], enable flag with intensity 5
    if (g_fogIntensityMin < 0x19) {
        g_fogIntensityMin = 0x19;
    }
    if (0x19 < g_fogIntensityMax) {
        g_fogIntensityMax = 0x19;
    }
    g_fogSlotEnabled[3] = 5;

    // Fifth slot: range [0x18 (24), 0x18], disable flag
    if (g_fogIntensityMin < 0x18) {
        g_fogIntensityMin = 0x18;
    }
    if (0x18 < g_fogIntensityMax) {
        g_fogIntensityMax = 0x18;
    }
    g_fogSlotEnabled[4] = 0;

    // Sixth slot: range [0xf (15), 0xf], disable flag
    if (g_fogIntensityMin < 0xf) {
        g_fogIntensityMin = 0xf;
    }
    if (0xf < g_fogIntensityMax) {
        g_fogIntensityMax = 0xf;
    }
    g_fogSlotEnabled[5] = 0;

    // Seventh slot: range [0x1b (27), 0x1b], disable flag (upper bound check uses 0x1a)
    if (g_fogIntensityMin < 0x1b) {
        g_fogIntensityMin = 0x1b;
    }
    if (0x1a < g_fogIntensityMax) {
        g_fogIntensityMax = 0x1b;
    }
    g_fogSlotEnabled[6] = 0;

    // Push/pop render state group again (1,2,1)
    setRenderStateGroup(1, 2, 1);

    // Get shader handles
    g_currentTexture = g_previousTexture;
    g_depthTexture = 0;
    g_currentShader = g_fogShaderProgram;

    // Check if fog shader is active (comparing shader handle to predefined values)
    if ((g_fogShaderProgram == g_fogShaderA) || 
        (g_fogShaderProgram == g_fogShaderB) || 
        (g_fogShaderProgram == g_fogShaderC)) {
        // Retrieve uniform locations from the shader
        g_fogColorUniform = getShaderUniform(g_fogShaderProgram, "fog_color");
        g_fogParamsUniform = getShaderUniform(g_currentShader, "fog_params");
        g_depthTextureUniform = getShaderUniform(g_currentShader, "depth_texture");
    }

    // Release previous resources if target changed
    if (g_currentRenderTarget == &g_renderTargetStruct) {
        releaseShaderResource(g_currentShader);
        releaseShaderResource(g_currentTexture);
    }

    // Read camera/projection data from this pointer offsets
    float local0 = *((float*)this + 8);   // +0x20
    float local1 = *((float*)this + 9);   // +0x24
    float local2 = *((float*)this + 10);  // +0x28
    float local3 = *((float*)this + 17);  // +0x44

    // Call update functions (likely for view/projection transforms)
    updateViewProjection1();
    local0 = *((float*)this + 12);  // +0x30
    local1 = *((float*)this + 13);  // +0x34
    local2 = *((float*)this + 14);  // +0x38
    local3 = *((float*)this + 18);  // +0x48
    updateViewProjection2();

    // Fog/depth state check
    if ((g_currentFogState == g_expectedFogState) && (g_fogTransition == 0)) {
        enableFog(1);
    } else {
        interpolateFog(g_currentFogState, g_expectedFogState);
    }

    // Push/pop render state again
    setRenderStateGroup(1, 2, 1);

    // Repeat the same clamping pattern (seems redundant, likely from separated blocks)
    if (g_fogIntensityMin < 0x16) {
        g_fogIntensityMin = 0x16;
    }
    if (0x16 < g_fogIntensityMax) {
        g_fogIntensityMax = 0x16;
    }
    g_fogSlotEnabled[0] = 1;
    if (g_fogIntensityMin < 7) {
        g_fogIntensityMin = 7;
    }
    if (7 < g_fogIntensityMax) {
        g_fogIntensityMax = 7;
    }
    g_fogSlotEnabled[1] = 0;
    if (g_fogIntensityMin < 0xe) {
        g_fogIntensityMin = 0xe;
    }
    if (0xe < g_fogIntensityMax) {
        g_fogIntensityMax = 0xe;
    }
    g_fogSlotEnabled[2] = 0;
    if (g_fogIntensityMin < 0x19) {
        g_fogIntensityMin = 0x19;
    }
    if (0x19 < g_fogIntensityMax) {
        g_fogIntensityMax = 0x19;
    }
    g_fogSlotEnabled[3] = 5;
    if (g_fogIntensityMin < 0x18) {
        g_fogIntensityMin = 0x18;
    }
    if (0x18 < g_fogIntensityMax) {
        g_fogIntensityMax = 0x18;
    }
    g_fogSlotEnabled[4] = 0;
    if (g_fogIntensityMin < 0xf) {
        g_fogIntensityMin = 0xf;
    }
    if (0xf < g_fogIntensityMax) {
        g_fogIntensityMax = 0xf;
    }
    g_fogSlotEnabled[5] = 0;
    if (g_fogIntensityMin < 0x1b) {
        g_fogIntensityMin = 0x1b;
    }
    if (0x1a < g_fogIntensityMax) {
        g_fogIntensityMax = 0x1b;
    }
    g_fogSlotEnabled[6] = 0;

    // Push/pop render state again
    setRenderStateGroup(1, 2, 1);

    // Update global scale factors
    updateGlobalScales();

    // Compute scaled values from camera position (this offsets)
    float scale = g_globalScaleFactor;
    if (*((float*)this + 16) < g_maxScale) {  // +0x40
        scale = *((float*)this + 16) * g_scaleMultiplier;
    }
    float scaledPosX = scale * *(float*)this;      // +0x00
    float scaledPosY = scale * *((float*)this + 1); // +0x04
    float scaledPosZ = scale * *((float*)this + 2); // +0x08
    float scaledPosW = scale * *((float*)this + 3); // +0x0C
    float scale2 = g_globalScaleFactor;
    if (*((float*)this + 19) < g_maxScale) { // +0x4C
        scale2 = *((float*)this + 19) * g_scaleMultiplier;
    }
    float scaledDirX = scale2 * *((float*)this + 4);  // +0x10
    float scaledDirY = scale2 * *((float*)this + 5);  // +0x14
    float scaledDirZ = scale2 * *((float*)this + 6);  // +0x18
    float scaledDirW = scale2 * *((float*)this + 7);  // +0x1C

    // Combine into arrays and call projection update
    float posArray[4] = {scaledPosX, scaledPosY, scaledPosZ, scaledPosW};
    float dirArray[4] = {scaledDirX, scaledDirY, scaledDirZ, scaledDirW};
    updateCameraTransform(posArray, dirArray);

    // Update projection matrix
    updateProjection();

    // Allocate GPU buffer (type 0xd, size 4, count 1, unknown flags)
    uint32_t* buffer = (uint32_t*)allocateGPUBuffer(0xd, 4, 0, 1, 0);
    uint32_t valA = g_globalA;
    float valB = g_globalScaleFactor;
    if (buffer != 0) {
        // Fill buffer with 8 float-like values (packed as uint32)
        buffer[0] = valA;
        buffer[1] = valA; // repeated
        buffer[2] = *((uint32_t*)&valB);
        buffer[3] = valA;
        buffer[4] = *((uint32_t*)&valB);
        buffer[5] = *((uint32_t*)&valB);
        buffer[6] = valA;
        buffer[7] = *((uint32_t*)&valB);
        uploadGPUBuffer(); // commits the data
    }

    // Final update call
    updatePostProcess();

    // Again repeat clamping pattern with final flags (some changed)
    if (g_fogIntensityMin < 0x16) {
        g_fogIntensityMin = 0x16;
    }
    if (0x16 < g_fogIntensityMax) {
        g_fogIntensityMax = 0x16;
    }
    g_fogSlotEnabled[0] = 1;
    if (g_fogIntensityMin < 7) {
        g_fogIntensityMin = 7;
    }
    if (7 < g_fogIntensityMax) {
        g_fogIntensityMax = 7;
    }
    g_fogSlotEnabled[1] = 1; // changed from 0 to 1
    if (g_fogIntensityMin < 0xe) {
        g_fogIntensityMin = 0xe;
    }
    if (0xe < g_fogIntensityMax) {
        g_fogIntensityMax = 0xe;
    }
    g_fogSlotEnabled[2] = 1; // changed from 0 to 1
    if (g_fogIntensityMin < 0x19) {
        g_fogIntensityMin = 0x19;
    }
    if (0x19 < g_fogIntensityMax) {
        g_fogIntensityMax = 0x19;
    }
    g_fogSlotEnabled[3] = 7; // changed from 5 to 7
    if (g_fogIntensityMin < 0x18) {
        g_fogIntensityMin = 0x18;
    }
    if (0x18 < g_fogIntensityMax) {
        g_fogIntensityMax = 0x18;
    }
    g_fogSlotEnabled[4] = 0;
    if (g_fogIntensityMin < 0xf) {
        g_fogIntensityMin = 0xf;
    }
    if (0xf < g_fogIntensityMax) {
        g_fogIntensityMax = 0xf;
    }
    g_fogSlotEnabled[5] = 0;
    if (g_fogIntensityMin < 0x1b) {
        g_fogIntensityMin = 0x1b;
    }
    if (0x1a < g_fogIntensityMax) {
        g_fogIntensityMax = 0x1b;
    }
    g_fogSlotEnabled[6] = 0;

    // Final state group push (1,5,6)
    setRenderStateGroup(1, 5, 6);
}
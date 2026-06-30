// FUNC_NAME: GraphicsSettings::applyQuality
void GraphicsSettings::applyQuality(int param_1, uint qualityFlags)
{
    uint uVar1;
    
    *(uint *)(param_1 + 8) = qualityFlags;  // store quality flags at offset +0x8
    
    if ((char)qualityFlags < '\0') {        // high bit set = ultra quality
        g_qualityLevel = 4;
        g_shadowResolution = 0;
        g_shadowFilterQuality = 0;
        g_antialiasing = 2;
        g_textureQuality = 0x13;
        g_someBufferA = g_someBufferHighA;
        g_someBufferB = g_someBufferHighB;
        if (g_pCurrentQualityManager == &g_defaultQualityManager) {
            FUN_0060a460(g_someBufferHighB);
            FUN_0060a460(g_someBufferHighA);
        }
    }
    else if ((qualityFlags & 0x10) == 0) {   // bit 4 clear -> medium or low
        if ((qualityFlags & 2) == 0) {       // bit 1 clear -> low
            uVar1 = ~(qualityFlags >> 6) & 1;
        }
        else {                                // bit 1 set -> medium
            uVar1 = 2;
        }
        FUN_00534d70(uVar1);                  // apply sub-quality level
    }
    else {                                    // bit 4 set -> high quality
        g_someBufferA = g_someBufferHighA2;
        g_qualityLevel = 3;
        g_shadowResolution = 0;
        g_shadowFilterQuality = 0;
        g_antialiasing = 0;
        g_textureQuality = 0x12;
        g_someBufferB = g_someBufferHighB2;
        if (g_pCurrentQualityManager == &g_defaultQualityManager) {
            FUN_0060a460(g_someBufferHighB2);
            FUN_0060a460(g_someBufferHighA2);
        }
    }
    
    FUN_00534ff0(0);          // apply global v-sync?
    FUN_00534950();           // update shadow parameters
    FUN_00534ef0();           // update LOD distances
    FUN_00412f90(qualityFlags >> 2 & 2);  // set anisotropic filtering (0/2)
    FUN_00417cf0(1,5,6);      // set some render states (likely texture detail)
    
    // Ensure shadow cascade distance is at least 7
    if (g_shadowCascadeDistance < 7) {
        g_shadowCascadeDistance = 7;
    }
    if (7 > g_shadowFadeDistance) {
        g_shadowFadeDistance = 7;
    }
    g_shadowMapResolution1 = 1;  // e.g., 1024x1024
    
    // Raise to at least 0x0e = 14
    if (g_shadowCascadeDistance < 0xe) {
        g_shadowCascadeDistance = 0xe;
    }
    if (0xe > g_shadowFadeDistance) {
        g_shadowFadeDistance = 0xe;
    }
    g_shadowMapResolution2 = 1;  // second shadow map
    
    if ((qualityFlags & 1) != 0) {   // bit 0 set -> enable something (bloom?)
        FUN_0041e660(g_screenWidth, g_screenHeight);
    }
    
    // Ensure at least 0x19 = 25
    if (g_shadowCascadeDistance < 0x19) {
        g_shadowCascadeDistance = 0x19;
    }
    if (0x19 > g_shadowFadeDistance) {
        g_shadowFadeDistance = 0x19;
    }
    g_lightCount = 5;   // e.g., max dynamic lights
    
    // Ensure at least 0x18 = 24
    if (g_shadowCascadeDistance < 0x18) {
        g_shadowCascadeDistance = 0x18;
    }
    if (0x18 > g_shadowFadeDistance) {
        g_shadowFadeDistance = 0x18;
    }
    g_lightShadowsEnabled = 0;  // disable shadow for lights
    
    // Ensure at least 0x0f = 15
    if (g_shadowCascadeDistance < 0xf) {
        g_shadowCascadeDistance = 0xf;
    }
    if (0xf > g_shadowFadeDistance) {
        g_shadowFadeDistance = 0xf;
    }
    g_shadowFilterSize = 0;  // no shadow filtering
    
    *(undefined1 *)(param_1 + 4) = 0;  // clear flag at offset +0x4 (dirty bit?)
    return;
}
// FUNC_NAME: ScreenEffectManager::initShaderHandles
void ScreenEffectManager::initShaderHandles()
{
    // Load screen effect shaders and retrieve parameter handles
    // These are likely used for full-screen post-processing effects

    // Load first screen effect (e.g., from "shaders/screen_effect1.fx")
    g_screenEffect1 = FUN_0060a2e0(&PTR_DAT_010be970);          // +0x012198f0
    // Get technique from that effect
    g_screenTechnique1 = FUN_0060a380();                         // +0x012198f4

    // Load second screen effect
    g_screenEffect2 = FUN_0060a2e0(&PTR_DAT_010be9a0);          // +0x012198f8
    // Load third screen effect
    g_screenEffect3 = FUN_0060a2e0(&PTR_DAT_010be9b0);          // +0x012198fc

    // Get technique from third effect
    g_screenTechnique2 = FUN_0060a380();                         // +0x01219900

    // Load fourth screen effect
    g_screenEffect4 = FUN_0060a2e0(&PTR_DAT_010bea10);          // +0x01219904
    // Get technique from fourth effect
    g_screenTechnique3 = FUN_0060a380();                         // +0x01219908

    // Load fifth screen effect (likely a common screen shader)
    g_screenEffect5 = FUN_0060a2e0(&PTR_DAT_010bde90);          // +0x0121990c

    // Retrieve shader parameter handles by name from the loaded effects
    g_screenTextureParam1 = FUN_0060a580(g_screenEffect2, "screen_texture");          // +0x01219910
    g_screenTextureParam2 = FUN_0060a580(g_screenEffect3, "screen_texture");          // +0x01219914
    g_scalingParam = FUN_0060a580(g_screenEffect5, "scaling");                        // +0x01219918
    g_screenColorParam1 = FUN_0060a580(g_screenEffect2, "screen_color");              // +0x0121991c
    g_screenColorParam2 = FUN_0060a580(g_screenEffect1, "screen_color");              // +0x01219920
    g_halfPixelOffsetParam1 = FUN_0060a580(g_screenEffect2, "screen_texture_halfPixelOffset"); // +0x0121992c
    g_halfPixelOffsetParam2 = FUN_0060a580(g_screenEffect3, "screen_texture_halfPixelOffset"); // +0x01219930
    g_vPosScaleTranslationParam1 = FUN_0060a580(g_screenTechnique2, "vPosScaleTranslationVS"); // +0x01219924
    g_vPosScaleTranslationParam2 = FUN_0060a580(g_screenTechnique3, "vPosScaleTranslationVS"); // +0x01219928
}
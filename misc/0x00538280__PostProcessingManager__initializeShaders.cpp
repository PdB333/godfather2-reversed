// FUNC_NAME: PostProcessingManager::initializeShaders
void __thiscall PostProcessingManager::initializeShaders(void)
{
    initSystem();

    // Load primary bloom shader (handles: bloom_dcolor, bloom_blackcolor, bloom_facts, bb_texture, g_halfPixelOffset)
    m_bloomShader = loadShader("bloom_dcolor");  // +0x470
    bool useModulate = (DAT_0120575b == 0);      // global quality flag
    // Load bloom modulate shader variant (differs based on quality flag)
    m_modulateShader = loadShader(useModulate ? &PTR_DAT_010bdd20 : &PTR_DAT_010bdd10); // +0x474

    // Additional effect shaders
    m_tintShader = loadShader(&PTR_DAT_010bdd30);   // +0x478 (bloom tint)
    m_weightShader = loadShader(&PTR_DAT_010bdd40); // +0x468 (bloom weight)
    m_sizeShader = loadShader(&PTR_DAT_010bdd50);   // +0x46C (bloom size)

    // Load 14 motion blur pass shaders
    for (int i = 0; i < 14; i++)
    {
        m_motionBlurPassShaders[i] = loadShader(PTR_PTR_011282f8[i]); // +0x494
    }

    // Motion blur depth term shader
    m_motionBlurShader = loadShader(); // +0x4cc

    // DOF shader
    m_dofShader = loadShader(&PTR_DAT_010bdf40); // +0x47c

    // Additional effect shaders (shader A and B)
    m_shaderA = loadShader(&PTR_DAT_010be070); // +0x48c
    m_shaderB = loadShader(&PTR_DAT_010be080); // +0x490

    // --- Retrieve shader parameter handles ---

    // Bloom main shader parameters (from m_bloomShader)
    m_bloomDColor = getParameter(m_bloomShader, "bloom_dcolor");           // +0x254
    m_bloomBlackColor = getParameter(m_bloomShader, "bloom_blackcolor");   // +0x258
    m_bloomFacts = getParameter(m_bloomShader, "bloom_facts");             // +0x25C
    m_bloomBbTexture = getParameter(m_bloomShader, "bb_texture");          // +0x260
    m_bloomHalfPixelOffset = getParameter(m_bloomShader, "g_halfPixelOffset"); // +0x264

    // Bloom modulate shader parameters (from m_modulateShader)
    m_modulateDColor = getParameter(m_modulateShader, "bloom_dcolor");         // +0x26C
    m_modulateBlackColor = getParameter(m_modulateShader, "bloom_blackcolor");  // +0x270
    m_modulateFacts = getParameter(m_modulateShader, "bloom_facts");            // +0x274
    m_modulateBbTexture = getParameter(m_modulateShader, "bb_texture");         // +0x278
    m_modulateSampler = 0;  // +0x27C (init to 0)
    m_modulateQueryAlpha = 0; // +0x280 (init to 0)
    if (useModulate)
    {
        m_modulateQueryAlpha = getParameter(m_modulateShader, "queryModulateAlpha"); // +0x280
    }
    else
    {
        m_modulateSampler = getParameter(m_modulateShader, "modulate_sampler");     // +0x27C
    }
    m_modulateHalfPixelOffset = getParameter(m_modulateShader, "g_halfPixelOffset");             // +0x284
    m_modulateModulateHalfPixel = getParameter(m_modulateShader, "g_modulate_halfPixelOffset"); // +0x288

    // Bloom tint shader parameters (from m_tintShader)
    m_tintBbTexture = getParameter(m_tintShader, "bb_texture");              // +0x28C
    m_tintBloomTexture = getParameter(m_tintShader, "bloom_texture");        // +0x290
    m_tintColor = getParameter(m_tintShader, "bloom_tintColor");             // +0x294
    m_tintBlackColor = getParameter(m_tintShader, "bloom_blacktintColor");   // +0x298
    m_tintDColor = getParameter(m_tintShader, "bloom_dcolor");               // +0x29C
    m_tintBlackColor2 = getParameter(m_tintShader, "bloom_blackcolor");      // +0x2A0
    m_tintHalfPixel = getParameter(m_tintShader, "g_halfPixelOffset");       // +0x2A4
    m_tintBloomHalfPixel = getParameter(m_tintShader, "g_bloom_halfPixelOffset"); // +0x268

    // Bloom weight shader parameters (from m_weightShader)
    m_weightBbTexture = getParameter(m_weightShader, "bb_texture");          // +0x2A8
    m_weightGWeight = getParameter(m_weightShader, "gWeightBloom");          // +0x2AC
    m_weightHalfPixel = getParameter(m_weightShader, "g_halfPixelOffset");   // +0x2B0

    // Bloom size shader parameters (from m_sizeShader)
    m_sizeBbTexture = getParameter(m_sizeShader, "bb_texture");              // +0x2B4
    m_sizeGWeight = getParameter(m_sizeShader, "gWeightBloom");              // +0x2B8
    m_sizeOneOverSize = getParameter(m_sizeShader, "oneOverSize");           // +0x2BC (700)
    m_sizeHalfPixel = getParameter(m_sizeShader, "g_halfPixelOffset");       // +0x2C0

    // Motion blur depth term parameters (from m_motionBlurShader)
    m_motionBlurDepthTermX = getParameter(m_motionBlurShader, "MotionBlur_DepthTerm_X"); // +0x2C4
    m_motionBlurDepthTermY = getParameter(m_motionBlurShader, "MotionBlur_DepthTerm_Y"); // +0x2C8
    m_motionBlurDepthTermZ = getParameter(m_motionBlurShader, "MotionBlur_DepthTerm_Z"); // +0x2CC
    m_motionBlurDepthTermW = getParameter(m_motionBlurShader, "MotionBlur_DepthTerm_W"); // +0x2D0

    // DOF shader parameters (from m_dofShader)
    m_dofColor = getParameter(m_dofShader, "dof_color");                 // +0x424
    m_dofParams = getParameter(m_dofShader, "dof_params");               // +0x428
    m_dofWidths = getParameter(m_dofShader, "dof_widths");               // +0x42C
    m_dofBbTexture = getParameter(m_dofShader, "bb_texture");            // +0x430
    m_dofDepthTexture = getParameter(m_dofShader, "depth_texture");      // +0x434
    m_dofHalfPixelOffset = getParameter(m_dofShader, "dof_HalfPixelOffset"); // +0x438

    // Shader A parameters (from m_shaderA)
    m_shaderAConstant1 = getParameter(m_shaderA, &DAT_00e38b2c);  // +0x448
    m_shaderAConstant2 = getParameter(m_shaderA, &PTR_LAB_00e38b30); // +0x44C
    m_shaderAConstant3 = getParameter(m_shaderA, &PTR_LAB_00e38b34); // +0x450
    m_shaderABbTexture = getParameter(m_shaderA, "bb_texture");       // +0x454
    m_shaderAHalfPixel = getParameter(m_shaderA, "halfPixelOffset");  // +0x458

    // Shader B parameters (from m_shaderB)
    m_shaderBConstant1 = getParameter(m_shaderB, &DAT_00e38b48);  // +0x45C
    m_shaderBBbTexture = getParameter(m_shaderB, "bb_texture");       // +0x460
    m_shaderBHalfPixel = getParameter(m_shaderB, "halfPixelOffset");  // +0x464

    // Motion blur pass parameters (14 passes, each with 6 uniform handles)
    // These overwrite the DOF and shader A/B parameter handles in memory
    // (offset range 0x424 - 0x49E)
    int* passColor = &m_dofColor;         // +0x424, alias start of motion blur parameters
    for (int i = 0; i < 14; i++)
    {
        m_motionBlurColor[i] = getParameter(m_motionBlurPassShaders[i], "blur_color");                // +0x424 + i*4
        m_motionBlurBbTextureP[i] = getParameter(m_motionBlurPassShaders[i], "bb_texture_p");         // +0x432 + i*4
        m_motionBlurDepthTexture[i] = getParameter(m_motionBlurPassShaders[i], "depth_texture");      // +0x440 + i*4
        m_motionBlurPSConstant[i] = getParameter(m_motionBlurPassShaders[i], "MotionBlur_PSConstant");// +0x44E + i*4
        m_motionBlurScreenSize[i] = getParameter(m_motionBlurPassShaders[i], "screen_size");          // +0x45C + i*4
        m_motionBlurHalfPixelOffset[i] = getParameter(m_motionBlurPassShaders[i], "blur_halfPixelOffset"); // +0x46A + i*4
    }

    return;
}
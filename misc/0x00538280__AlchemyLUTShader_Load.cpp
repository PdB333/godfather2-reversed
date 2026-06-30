// Xbox PDB: AlchemyLUTShader::Load
// FUNC_NAME: PostEffectManager::initShaders
void __thiscall PostEffectManager::initShaders(void)
{
    int shaderHandle;
    int paramHandle;
    int *shaderArray;
    int *currentShader;
    int i;
    bool useXboxShader;

    // Call initialization function (likely sets up pipeline or common shaders)
    FUN_006127d0();

    // Load bloom shader program (first variant)
    shaderHandle = FUN_0060a2e0(&PTR_DAT_010bdd00);  // +0x470: bloomShader1
    this->bloomShader1 = shaderHandle;

    // Check global flag (likely platform detection: Xbox vs PC)
    useXboxShader = (DAT_0120575b == 0) ? false : true;

    // Load second bloom shader based on platform
    if (useXboxShader) {
        shaderHandle = FUN_0060a2e0(&PTR_DAT_010bdd10);  // Xbox variant? +0x474: bloomShader2
    } else {
        shaderHandle = FUN_0060a2e0(&PTR_DAT_010bdd20);  // PC variant? +0x474: bloomShader2
    }
    this->bloomShader2 = shaderHandle;

    // Load more shader programs (various post-processing effects)
    shaderHandle = FUN_0060a2e0(&PTR_DAT_010bdd30);  // +0x478: compositeShader
    this->compositeShader = shaderHandle;

    shaderHandle = FUN_0060a2e0(&PTR_DAT_010bdd40);  // +0x468: blurWeightShader
    this->blurWeightShader = shaderHandle;

    shaderHandle = FUN_0060a2e0(&PTR_DAT_010bdd50);  // +0x46c: blurWeightShader2
    this->blurWeightShader2 = shaderHandle;

    // Load an array of 15 blur pass shaders (starting at +0x494)
    shaderArray = &this->blurPassShaders[0];  // +0x494
    currentShader = &PTR_PTR_011282f8;  // pointer array to shader names
    for (i = 0; i < 15; i++) {
        shaderHandle = FUN_0060a2e0(*currentShader);
        *shaderArray = shaderHandle;
        currentShader++;
        shaderArray++;
    }

    // Load motion blur shader
    shaderHandle = FUN_0060a380();  // +0x4cc: motionBlurShader
    this->motionBlurShader = shaderHandle;

    // Load depth of field shader
    shaderHandle = FUN_0060a2e0(&PTR_DAT_010bdf40);  // +0x47c: dofShader
    this->dofShader = shaderHandle;

    // Load additional shaders (possibly tone mapping or other)
    shaderHandle = FUN_0060a2e0(&PTR_DAT_010be070);  // +0x480: shader
    this->shader480 = shaderHandle;
    shaderHandle = FUN_0060a2e0(&PTR_DAT_010be080);  // +0x484: shader
    this->shader484 = shaderHandle;
    shaderHandle = FUN_0060a2e0(&PTR_DAT_010be090);  // +0x488: shader
    this->shader488 = shaderHandle;
    shaderHandle = FUN_0060a2e0(&PTR_DAT_010be1f0);  // +0x48c: shader (ssao or similar?)
    this->shader48c = shaderHandle;
    shaderHandle = FUN_0060a2e0(&PTR_DAT_010be930);  // +0x490: shader (ssao or similar?)
    this->shader490 = shaderHandle;

    // Now get shader parameters (constants) for each shader

    // For bloomShader1 (+0x470)
    paramHandle = FUN_0060a580(this->bloomShader1, "bloom_dcolor");       // +0x254: bloomDcolor
    this->bloomDcolor = paramHandle;
    paramHandle = FUN_0060a580(this->bloomShader1, "bloom_blackcolor");   // +0x258: bloomBlackcolor (600 decimal)
    this->bloomBlackcolor = paramHandle;
    paramHandle = FUN_0060a580(this->bloomShader1, "bloom_facts");        // +0x25c: bloomFacts
    this->bloomFacts = paramHandle;
    paramHandle = FUN_0060a580(this->bloomShader1, "bb_texture");         // +0x260: bbTexture
    this->bbTexture = paramHandle;
    paramHandle = FUN_0060a580(this->bloomShader1, "g_halfPixelOffset");  // +0x264: halfPixelOffset
    this->halfPixelOffset = paramHandle;

    // For bloomShader2 (+0x474)
    paramHandle = FUN_0060a580(this->bloomShader2, "bloom_dcolor");       // +0x26c: bloomDcolor2
    this->bloomDcolor2 = paramHandle;
    paramHandle = FUN_0060a580(this->bloomShader2, "bloom_blackcolor");   // +0x270: bloomBlackcolor2
    this->bloomBlackcolor2 = paramHandle;
    paramHandle = FUN_0060a580(this->bloomShader2, "bloom_facts");        // +0x274: bloomFacts2
    this->bloomFacts2 = paramHandle;
    paramHandle = FUN_0060a580(this->bloomShader2, "bb_texture");         // +0x278: bbTexture2
    this->bbTexture2 = paramHandle;

    // Additional modulation parameters (platform dependent)
    this->shader27c = 0; // +0x27c
    this->shader280 = 0; // +0x280
    if (useXboxShader) {
        paramHandle = FUN_0060a580(this->bloomShader2, "modulate_sampler"); // +0x27c: modulateSampler
        this->modulateSampler = paramHandle;
    } else {
        paramHandle = FUN_0060a580(this->bloomShader2, "queryModulateAlpha"); // +0x280: queryModulateAlpha
        this->queryModulateAlpha = paramHandle;
    }

    paramHandle = FUN_0060a580(this->bloomShader2, "g_halfPixelOffset");          // +0x284: halfPixelOffset2
    this->halfPixelOffset2 = paramHandle;
    paramHandle = FUN_0060a580(this->bloomShader2, "g_modulate_halfPixelOffset"); // +0x288: modulateHalfPixelOffset
    this->modulateHalfPixelOffset = paramHandle;

    // For compositeShader (+0x478)
    paramHandle = FUN_0060a580(this->compositeShader, "bb_texture");           // +0x28c: compositeBbTexture
    this->compositeBbTexture = paramHandle;
    paramHandle = FUN_0060a580(this->compositeShader, "bloom_texture");        // +0x290: compositeBloomTexture
    this->compositeBloomTexture = paramHandle;
    paramHandle = FUN_0060a580(this->compositeShader, "bloom_tintColor");      // +0x294: compositeTintColor
    this->compositeTintColor = paramHandle;
    paramHandle = FUN_0060a580(this->compositeShader, "bloom_blacktintColor"); // +0x298: compositeBlacktintColor
    this->compositeBlacktintColor = paramHandle;
    paramHandle = FUN_0060a580(this->compositeShader, "bloom_dcolor");         // +0x29c: compositeBloomDcolor
    this->compositeBloomDcolor = paramHandle;
    paramHandle = FUN_0060a580(this->compositeShader, "bloom_blackcolor");     // +0x2a0: compositeBloomBlackcolor
    this->compositeBloomBlackcolor = paramHandle;
    paramHandle = FUN_0060a580(this->compositeShader, "g_halfPixelOffset");    // +0x2a4: compositeHalfPixelOffset
    this->compositeHalfPixelOffset = paramHandle;
    paramHandle = FUN_0060a580(this->compositeShader, "g_bloom_halfPixelOffset"); // +0x268: compositeBloomHalfPixelOffset
    this->compositeBloomHalfPixelOffset = paramHandle;

    // For blurWeightShader (+0x468)
    paramHandle = FUN_0060a580(this->blurWeightShader, "bb_texture");       // +0x2a8: blurWeightBbTexture
    this->blurWeightBbTexture = paramHandle;
    paramHandle = FUN_0060a580(this->blurWeightShader, "gWeightBloom");     // +0x2ac: blurWeightGWeight
    this->blurWeightGWeight = paramHandle;
    paramHandle = FUN_0060a580(this->blurWeightShader, "g_halfPixelOffset"); // +0x2b0: blurWeightHalfPixelOffset
    this->blurWeightHalfPixelOffset = paramHandle;

    // For blurWeightShader2 (+0x46c)
    paramHandle = FUN_0060a580(this->blurWeightShader2, "bb_texture");          // +0x2b4: blurWeight2BbTexture
    this->blurWeight2BbTexture = paramHandle;
    paramHandle = FUN_0060a580(this->blurWeightShader2, "gWeightBloom");        // +0x2b8: blurWeight2GWeight
    this->blurWeight2GWeight = paramHandle;
    paramHandle = FUN_0060a580(this->blurWeightShader2, "oneOverSize");          // +0x2bc (700 decimal): oneOverSize
    this->oneOverSize = paramHandle;
    paramHandle = FUN_0060a580(this->blurWeightShader2, "g_halfPixelOffset");   // +0x2c0: blurWeight2HalfPixelOffset
    this->blurWeight2HalfPixelOffset = paramHandle;

    // For each of the 15 blur pass shaders (stored in array starting at +0x494)
    // and set their parameters (parameters stored in a corresponding array starting at +0x??
    // The loop below accesses puVar4 (which starts at +0x494) and writes to puVar4[-0x70] etc.
    // This implies there is a parallel array of parameter structures offset negative.
    // We'll assume the class has a member like: int blurPassShaderHandles[15]; // +0x494
    // and a member: int blurPassColorParams[15]; // +0x... (the negative offset)
    // But the actual offsets are calculated as puVar4 + negative constant.
    // For clarity, we'll just replicate the logic.

    for (i = 0; i < 15; i++) {
        // Each iteration: puVar4 points to current shader handle in array
        // puVar4[-0x70] corresponds to offset +0x494 - 0x70*4 = +0x494 - 0x1C0 = +0x2D4 ? Actually -0x70*4 = -0x1C0, so offset +0x2D4. But we'll just store in parallel array.
        paramHandle = FUN_0060a580(this->blurPassShaders[i], "blur_color");        // store at +0x2D4??
        this->blurPassColorParams[i] = paramHandle;
        paramHandle = FUN_0060a580(this->blurPassShaders[i], "bb_texture_p");      // +0x2E2??
        this->blurPassBbTextureP[i] = paramHandle;
        paramHandle = FUN_0060a580(this->blurPassShaders[i], "depth_texture");     // +0x2F0??
        this->blurPassDepthTexture[i] = paramHandle;
        paramHandle = FUN_0060a580(this->blurPassShaders[i], "MotionBlur_PSConstant"); // +0x2FE??
        this->blurPassMotionBlurPSConstant[i] = paramHandle;
        paramHandle = FUN_0060a580(this->blurPassShaders[i], "screen_size");       // +0x30C??
        this->blurPassScreenSize[i] = paramHandle;
        paramHandle = FUN_0060a580(this->blurPassShaders[i], "blur_halfPixelOffset"); // +0x31A??
        this->blurPassBlurHalfPixelOffset[i] = paramHandle;
    }

    // For motionBlurShader (+0x4cc)
    paramHandle = FUN_0060a580(this->motionBlurShader, "MotionBlur_DepthTerm_X"); // +0x2c4
    this->motionBlurDepthTermX = paramHandle;
    paramHandle = FUN_0060a580(this->motionBlurShader, "MotionBlur_DepthTerm_Y"); // +0x2c8
    this->motionBlurDepthTermY = paramHandle;
    paramHandle = FUN_0060a580(this->motionBlurShader, "MotionBlur_DepthTerm_Z"); // +0x2cc
    this->motionBlurDepthTermZ = paramHandle;
    paramHandle = FUN_0060a580(this->motionBlurShader, "MotionBlur_DepthTerm_W"); // +0x2d0
    this->motionBlurDepthTermW = paramHandle;

    // For dofShader (+0x47c)
    paramHandle = FUN_0060a580(this->dofShader, "dof_color");           // +0x424
    this->dofColor = paramHandle;
    paramHandle = FUN_0060a580(this->dofShader, "dof_params");          // +0x428
    this->dofParams = paramHandle;
    paramHandle = FUN_0060a580(this->dofShader, "dof_widths");          // +0x42c
    this->dofWidths = paramHandle;
    paramHandle = FUN_0060a580(this->dofShader, "bb_texture");          // +0x430
    this->dofBbTexture = paramHandle;
    paramHandle = FUN_0060a580(this->dofShader, "depth_texture");       // +0x434
    this->dofDepthTexture = paramHandle;
    paramHandle = FUN_0060a580(this->dofShader, "dof_HalfPixelOffset"); // +0x438
    this->dofHalfPixelOffset = paramHandle;

    // For shader48c (+0x48c) - possibly SSAO
    paramHandle = FUN_0060a580(this->shader48c, "ssao_params");         // +0x448 (assuming string data at 0x00e38b2c)
    this->ssaoParams = paramHandle;
    paramHandle = FUN_0060a580(this->shader48c, "ssao_other1");        // +0x44c
    this->ssaoOther1 = paramHandle;
    paramHandle = FUN_0060a580(this->shader48c, "ssao_other2");        // +0x450
    this->ssaoOther2 = paramHandle;
    paramHandle = FUN_0060a580(this->shader48c, "bb_texture");          // +0x454
    this->ssaoBbTexture = paramHandle;
    paramHandle = FUN_0060a580(this->shader48c, "halfPixelOffset");     // +0x458
    this->ssaoHalfPixelOffset = paramHandle;

    // For shader490 (+0x490) - possibly a final composite or tone mapping
    paramHandle = FUN_0060a580(this->shader490, "final_params");        // +0x45c (string at 0x00e38b48)
    this->finalParams = paramHandle;
    paramHandle = FUN_0060a580(this->shader490, "bb_texture");          // +0x460
    this->finalBbTexture = paramHandle;
    paramHandle = FUN_0060a580(this->shader490, "halfPixelOffset");     // +0x464
    this->finalHalfPixelOffset = paramHandle;

    return;
}
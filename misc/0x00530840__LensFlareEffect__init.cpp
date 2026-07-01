// FUNC_NAME: LensFlareEffect::init

void __fastcall LensFlareEffect::init(void *this)
{
    uint shaderHandle;
    bool isNextGen;
    const char **shaderPath;

    // Call base class init (likely ScreenSpaceEffect::init)
    ScreenSpaceEffect::init();

    // Set some member at offset 0x12C (300) to 0
    *(int *)((char *)this + 0x12C) = 0;

    // Another initialization (possibly material or render state setup)
    FUN_00530630(); // Could be Material::setup or similar

    // Choose shader path based on global next-gen flag
    if (DAT_0120575b == '\0') {
        shaderPath = &PTR_DAT_010be990;  // "shaders/old_gen/..."?
    } else {
        shaderPath = &PTR_DAT_010be980;  // "shaders/next_gen/..."?
    }

    // Create shaders for different pieces of the effect
    // Each FUN_0060a2e0 likely returns a ShaderHandle (or MaterialHandle)
    shaderHandle = createShader(shaderPath);  // main effect shader?  
    *(int *)((char *)this + 0x108) = shaderHandle;  // m_coronaShader1

    shaderHandle = createShader(&PTR_DAT_010be9e0);
    *(int *)((char *)this + 0x110) = shaderHandle;  // m_coronaShader2

    shaderHandle = createShader(&PTR_DAT_010be9f0);
    *(int *)((char *)this + 0x10c) = shaderHandle;  // m_coronaShader3

    shaderHandle = createShader(&PTR_DAT_010be9d0);
    *(int *)((char *)this + 0x114) = shaderHandle;  // m_coronaShader4

    shaderHandle = createShader(&PTR_DAT_010be9c0);
    *(int *)((char *)this + 0x118) = shaderHandle;  // m_coronaShader5

    // Initialize parameter handles for alpha modulation
    // These are shader constant IDs (likely int handles)
    *(int *)((char *)this + 0xd8) = 0;   // m_modulateByCoronaInfoHandle
    *(int *)((char *)this + 0xdc) = 0;   // m_modulateSamplerHandle
    *(int *)((char *)this + 0xe0) = 0;   // m_queryModulateAlphaHandle

    if (DAT_0120575b == '\0') {
        // Old gen: use queryModulateAlpha
        shaderHandle = getShaderConstant(*(int *)((char *)this + 0x108), "queryModulateAlpha");
        *(int *)((char *)this + 0xe0) = shaderHandle;
    } else {
        // Next gen: use modulate_by_corona_info and modulate_sampler
        shaderHandle = getShaderConstant(*(int *)((char *)this + 0x108), "modulate_by_corona_info");
        *(int *)((char *)this + 0xd8) = shaderHandle;
        shaderHandle = getShaderConstant(*(int *)((char *)this + 0x108), "modulate_sampler");
        *(int *)((char *)this + 0xdc) = shaderHandle;
    }

    // Get constant handles for various uniforms
    // From shader 1 (0x108)
    shaderHandle = getShaderConstant(*(int *)((char *)this + 0x108), "screen_color");
    *(int *)((char *)this + 0xfc) = shaderHandle;   // m_screenColorHandle

    // From shader 5 (0x118)
    shaderHandle = getShaderConstant(*(int *)((char *)this + 0x118), "screen_texture");
    *(int *)((char *)this + 0x100) = shaderHandle;  // m_screenTextureHandle
    shaderHandle = getShaderConstant(*(int *)((char *)this + 0x118), "screen_texture_halfPixelOffset");
    *(int *)((char *)this + 0x104) = shaderHandle;  // m_screenTexHalfTexelHandle

    // From shader 3 (0x10c)
    shaderHandle = getShaderConstant(*(int *)((char *)this + 0x10c), "oneOverSize");
    *(int *)((char *)this + 0xe8) = shaderHandle;   // m_depthOneOverSizeHandle1
    shaderHandle = getShaderConstant(*(int *)((char *)this + 0x10c), "depth_textureZ");
    *(int *)((char *)this + 0xf0) = shaderHandle;   // m_depthTextureZHandle1

    // From shader 2 (0x110)
    shaderHandle = getShaderConstant(*(int *)((char *)this + 0x110), "oneOverSize");
    *(int *)((char *)this + 0xe4) = shaderHandle;   // m_depthOneOverSizeHandle2
    shaderHandle = getShaderConstant(*(int *)((char *)this + 0x110), "depth_textureZ");
    *(int *)((char *)this + 0xf4) = shaderHandle;   // m_depthTextureZHandle2

    // From shader 5 again
    shaderHandle = getShaderConstant(*(int *)((char *)this + 0x118), "oneOverSize");
    *(int *)((char *)this + 0xec) = shaderHandle;   // m_screenOneOverSizeHandle

    // Create another shader (maybe low-res or stencil)
    shaderHandle = createShader(&PTR_DAT_010bea00);
    *(int *)((char *)this + 0x128) = shaderHandle;  // m_lowResShader

    shaderHandle = getShaderConstant(*(int *)((char *)this + 0x128), "oneOverSize");
    *(int *)((char *)this + 0x11c) = shaderHandle;  // m_lowResOneOverSizeHandle
    shaderHandle = getShaderConstant(*(int *)((char *)this + 0x128), "texture_lowres");
    *(int *)((char *)this + 0x120) = shaderHandle;  // m_lowResTextureHandle
    shaderHandle = getShaderConstant(*(int *)((char *)this + 0x128), "texture_stencil");
    *(int *)((char *)this + 0x124) = shaderHandle;  // m_stencilTextureHandle

    // From shader 4 (0x114) - final composition?
    shaderHandle = getShaderConstant(*(int *)((char *)this + 0x114), "screen_texture");
    *(int *)((char *)this + 0xf8) = shaderHandle;   // m_compositeScreenTextureHandle
}
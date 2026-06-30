// FUNC_NAME: PostProcessEffect::cacheShaderParameters
void PostProcessEffect::cacheShaderParameters() {
    // Check if the first shader object (+0x14) is valid
    if (*(int*)(this + 0x14) == 0) {
        // Clear parameter handles if no shader is present
        *(int*)(this + 0xa4) = 0;  // kClearColor handle
        *(int*)(this + 0xc0) = 0;  // g_zbuffer_to_alpha_params handle
        *(int*)(this + 0xf0) = 0;  // kBlurIntensity handle
        *(int*)(this + 0xfc) = 0;  // ColorTexture handle
        *(int*)(this + 0x104) = 0; // ColorTexture3D handle
        *(int*)(this + 0x10c) = 0; // DepthTexture handle
        *(int*)(this + 0x114) = 0; // ToneMapTexture handle
        *(int*)(this + 0x11c) = 0; // kDelta handle
        *(int*)(this + 0x1e4) = 0; // ColorTexture_HalfPixelOffset handle
    } else {
        // Cache shader parameter handles from the first shader object
        *(int*)(this + 0xa4) = getParameterHandle(*(int*)(this + 0x14), "kClearColor");
        *(int*)(this + 0xc0) = getParameterHandle(*(int*)(this + 0x14), "g_zbuffer_to_alpha_params");
        *(int*)(this + 0xf0) = getParameterHandle(*(int*)(this + 0x14), "kBlurIntensity");
        *(int*)(this + 0xfc) = getParameterHandle(*(int*)(this + 0x14), "ColorTexture");
        *(int*)(this + 0x104) = getParameterHandle(*(int*)(this + 0x14), "ColorTexture3D");
        *(int*)(this + 0x10c) = getParameterHandle(*(int*)(this + 0x14), "DepthTexture");
        *(int*)(this + 0x114) = getParameterHandle(*(int*)(this + 0x14), "ToneMapTexture");
        *(int*)(this + 0x11c) = getParameterHandle(*(int*)(this + 0x14), "kDelta");
        *(int*)(this + 0x1e4) = getParameterHandle(*(int*)(this + 0x14), "ColorTexture_HalfPixelOffset");
    }
    // Cache parameter handles from the second shader object (+0x10)
    *(int*)(this + 0x12c) = getParameterHandle(*(int*)(this + 0x10), "gDeltaToRB");
    *(int*)(this + 0x120) = getParameterHandle(*(int*)(this + 0x10), "kDelta");
    *(int*)(this + 0x1e0) = getParameterHandle(*(int*)(this + 0x10), "vPosScaleTranslationVS");
}
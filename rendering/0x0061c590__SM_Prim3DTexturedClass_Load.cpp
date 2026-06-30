// Xbox PDB: SM_Prim3DTexturedClass::Load
// FUNC_NAME: ShaderEffect::initializeTextureParameters
void __thiscall ShaderEffect::initializeTextureParameters(void) {
    int effectHandle;
    int shaderParamHandle;
    
    // Get base effect handle (e.g., material handle)
    effectHandle = getEffectHandle();  // FUN_0060a380
    *(int *)(this + 0x10) = effectHandle;
    
    // Get shader parameter handles for various texture names
    shaderParamHandle = getParameterHandle(&PTR_DAT_00f10f7c);  // e.g., "ColorEffect"
    *(int *)(this + 0x14) = shaderParamHandle;
    
    // Additional initialization call
    initTextureSamplers();  // FUN_006127d0
    
    // Store the second handle again at a different offset
    *(int *)(this + 0x114) = *(int *)(this + 0x14);
    
    // Acquire more parameter handles for different passes or effect layers
    shaderParamHandle = getParameterHandle(&PTR_DAT_00f10f8c);  // "AlphaEffect"
    *(int *)(this + 0x118) = shaderParamHandle;
    
    shaderParamHandle = getParameterHandle(&PTR_DAT_00f10f9c);  // "DepthEffect"
    *(int *)(this + 0x11c) = shaderParamHandle;
    
    shaderParamHandle = getParameterHandle(&PTR_DAT_00f10fac);  // "YUVEffect"
    *(int *)(this + 0x120) = shaderParamHandle;
    
    shaderParamHandle = getParameterHandle(&PTR_DAT_00f10fbc);  // "YPlaneEffect"
    *(int *)(this + 0x124) = shaderParamHandle;
    
    shaderParamHandle = getParameterHandle(&PTR_DAT_00f10fcc);  // "YCoCgEffect"
    *(int *)(this + 300) = shaderParamHandle;  // +0x12C
    
    // Bind texture parameters to each effect layer
    *(int *)(this + 0xe4) = getTextureParameter(*(int *)(this + 0x114), "ColorTexture");
    *(int *)(this + 0xe8) = getTextureParameter(*(int *)(this + 0x118), "AlphaTexture");
    *(int *)(this + 0xec) = getTextureParameter(*(int *)(this + 0x11c), "DepthTexture");
    *(int *)(this + 0xf4) = getTextureParameter(*(int *)(this + 0x120), "YUVTexture");
    *(int *)(this + 0xf8) = getTextureParameter(*(int *)(this + 0x124), "YTexture");
    *(int *)(this + 0xfc) = getTextureParameter(*(int *)(this + 0x124), "UTexture");
    *(int *)(this + 0x100) = getTextureParameter(*(int *)(this + 0x124), "VTexture");
    *(int *)(this + 0x104) = getTextureParameter(*(int *)(this + 0x124), "YUV_UVscale");
    *(int *)(this + 0x10c) = getTextureParameter(*(int *)(this + 0x124), "YCoCgTexture");
    
    return;
}
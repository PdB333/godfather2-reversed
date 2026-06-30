// Xbox PDB: SM_Prim3DTexturedClass::Load
// FUNC_NAME: ShaderMaterial::initializeTechniquesAndSamplers
void __thiscall ShaderMaterial::initializeTechniquesAndSamplers()
{
    // Get effect manager or render device
    // Offset +0x10 likely stores some manager pointer
    *(void**)(this + 0x10) = getEffectManager();

    // Create/get multiple techniques from static data
    // +0x14 stores the first (base) technique handle
    *(void**)(this + 0x14) = createTechnique(PTR_DAT_00f1102c); // e.g., "BaseTechnique"

    // Finalize/commit technique collection
    compileTechniques();

    // Copy base technique to +0x114 (primary technique)
    *(void**)(this + 0x114) = *(void**)(this + 0x14);

    // Additional techniques for different render modes
    *(void**)(this + 0x118) = createTechnique(PTR_DAT_00f1103c); // e.g., "AlphaTechnique"
    *(void**)(this + 0x11c) = createTechnique(PTR_DAT_00f1104c); // e.g., "DepthTechnique"
    *(void**)(this + 0x120) = createTechnique(PTR_DAT_00f1106c); // e.g., "YUVTechnique"
    *(void**)(this + 0x124) = createTechnique(PTR_DAT_00f1107c); // e.g., "YOnlyTechnique"
    *(void**)(this + 0x128) = createTechnique(PTR_DAT_00f1105c); // e.g., "AlphaDepthTechnique"
    *(void**)(this + 300)   = createTechnique(PTR_DAT_00f1108c); // e.g., "YCoCgTechnique"  // +0x12C

    // Query texture sampler parameters from the base technique (+0x114)
    *(void**)(this + 0xe4) = getParameterHandle(*(void**)(this + 0x114), "ColorTexture");
    *(void**)(this + 0xe8) = getParameterHandle(*(void**)(this + 0x118), "AlphaTexture");
    *(void**)(this + 0xec) = getParameterHandle(*(void**)(this + 0x11c), "DepthTexture");
    *(void**)(this + 0xf0) = getParameterHandle(*(void**)(this + 0x128), "DepthTexture");      // from AlphaDepth technique
    *(void**)(this + 0xf4) = getParameterHandle(*(void**)(this + 0x120), "YUVTexture");
    *(void**)(this + 0xf8) = getParameterHandle(*(void**)(this + 0x124), "YTexture");
    *(void**)(this + 0xfc) = getParameterHandle(*(void**)(this + 0x124), "UTexture");
    *(void**)(this + 0x100) = getParameterHandle(*(void**)(this + 0x124), "VTexture");
    *(void**)(this + 0x110) = getParameterHandle(*(void**)(this + 0x124), "AlphaTexture");     // from YOnly technique
    *(void**)(this + 0x104) = getParameterHandle(*(void**)(this + 0x124), "YUV_UVscale");
    *(void**)(this + 0x10c) = getParameterHandle(*(void**)(this + 300), "YCoCgTexture");       // from YCoCg technique
}
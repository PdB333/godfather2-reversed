// Xbox PDB: SM_Prim3DTexturedClass::Load
// FUNC_NAME: PostProcessEffect::initializeParameters
void __thiscall PostProcessEffect::initializeParameters(void* this_ptr)
{
    // +0x10: Effect handle for base (probably vertex shader or main effect)
    int baseEffect = CreateEffect(); // 0x0060a380 - returns effect handle
    *(int*)((char*)this_ptr + 0x10) = baseEffect;

    // +0x14: Parameter handle for first texture set (ColorTexture?)
    int baseParam = GetEffectParameter("BaseEffect"); // 0x0060a2e0 - string at PTR_DAT_00f10f7c
    *(int*)((char*)this_ptr + 0x14) = baseParam;

    // Initialize default shader parameters (no args)
    InitializeDefaultShaderParameters(); // 0x006127d0

    // Copy base parameter to separate slot (+0x114)
    *(int*)((char*)this_ptr + 0x114) = *(int*)((char*)this_ptr + 0x14);

    // Create parameter handles for other texture sets
    int alphaParam = GetEffectParameter("AlphaEffect"); // PTR_DAT_00f10f8c
    *(int*)((char*)this_ptr + 0x118) = alphaParam;

    int depthParam = GetEffectParameter("DepthEffect"); // PTR_DAT_00f10f9c
    *(int*)((char*)this_ptr + 0x11c) = depthParam;

    int yuvParam = GetEffectParameter("YUVEffect"); // PTR_DAT_00f10fac
    *(int*)((char*)this_ptr + 0x120) = yuvParam;

    int yParam = GetEffectParameter("YEffect"); // PTR_DAT_00f10fbc
    *(int*)((char*)this_ptr + 0x124) = yParam;

    int uvParam = GetEffectParameter("UVEffect"); // PTR_DAT_00f10fcc
    *(int*)((char*)this_ptr + 0x12c) = uvParam;

    // Retrieve individual texture parameter indices from each effect
    // +0xe4: ColorTexture index in BaseEffect
    *(int*)((char*)this_ptr + 0xe4) = GetParameterIndex(*(int*)((char*)this_ptr + 0x114), "ColorTexture");
    // +0xe8: AlphaTexture index in AlphaEffect
    *(int*)((char*)this_ptr + 0xe8) = GetParameterIndex(*(int*)((char*)this_ptr + 0x118), "AlphaTexture");
    // +0xec: DepthTexture index in DepthEffect
    *(int*)((char*)this_ptr + 0xec) = GetParameterIndex(*(int*)((char*)this_ptr + 0x11c), "DepthTexture");
    // +0xf4: YUVTexture index in YUVEffect
    *(int*)((char*)this_ptr + 0xf4) = GetParameterIndex(*(int*)((char*)this_ptr + 0x120), "YUVTexture");
    // +0xf8: YTexture index in YEffect
    *(int*)((char*)this_ptr + 0xf8) = GetParameterIndex(*(int*)((char*)this_ptr + 0x124), "YTexture");
    // +0xfc: UTexture index in YEffect
    *(int*)((char*)this_ptr + 0xfc) = GetParameterIndex(*(int*)((char*)this_ptr + 0x124), "UTexture");
    // +0x100: VTexture index in YEffect
    *(int*)((char*)this_ptr + 0x100) = GetParameterIndex(*(int*)((char*)this_ptr + 0x124), "VTexture");
    // +0x104: YUV_UVscale index in YEffect
    *(int*)((char*)this_ptr + 0x104) = GetParameterIndex(*(int*)((char*)this_ptr + 0x124), "YUV_UVscale");
    // +0x10c: YCoCgTexture index in YEffect
    *(int*)((char*)this_ptr + 0x10c) = GetParameterIndex(*(int*)((char*)this_ptr + 0x124), "YCoCgTexture");
}
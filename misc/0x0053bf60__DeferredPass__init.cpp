// FUNC_NAME: DeferredPass::init
// Address: 0x0053bf60
// Role: Initializes shader parameter handles for a deferred rendering pass.

void __thiscall DeferredPass::init(void)
{
    // +0x10: effect handle (e.g., ID3DXEffect*)
    *(int*)(this + 0x10) = getDefaultEffect(); // FUN_0060a380

    // +0x14: technique handle (e.g., D3DXHANDLE)
    *(int*)(this + 0x14) = getTechnique("PostProcess"); // FUN_0060a2e0, PTR_DAT_010bea80 likely "PostProcess"

    // Unknown reset/setup call
    resetDevice(); // FUN_006127d0

    // +0xa8: another technique handle (second pass)
    *(int*)(this + 0xa8) = *(int*)(this + 0x14); // reuse main technique

    // +0xa4: second effect handle (different shader)
    *(int*)(this + 0xa4) = getTechnique("PostProcess2"); // FUN_0060a2e0, PTR_DAT_010bea70 likely "PostProcess2"

    // Retrieve all parameter handles from the second effect and store them
    // +0xac: "ColorTexture"
    *(int*)(this + 0xac) = getParameter(*(int*)(this + 0xa4), "ColorTexture"); // FUN_0060a580
    // +0xb0: "DepthTexture"
    *(int*)(this + 0xb0) = getParameter(*(int*)(this + 0xa4), "DepthTexture");
    // +0xb4: "g_nBuffer"
    *(int*)(this + 0xb4) = getParameter(*(int*)(this + 0xa4), "g_nBuffer");
    // +0xb8: "g_TexelSize"
    *(int*)(this + 0xb8) = getParameter(*(int*)(this + 0xa4), "g_TexelSize");
    // +0xbc: "g_BarrierAndWeights"
    *(int*)(this + 0xbc) = getParameter(*(int*)(this + 0xa4), "g_BarrierAndWeights");

    // Parameters from the first technique (via +0xa8, which is same as +0x14)
    // +0xc0: "bb_texture" (backbuffer texture)
    *(int*)(this + 0xc0) = getParameter(*(int*)(this + 0xa8), "bb_texture");
    // +0xc4: "g_TexelSize" (second effect)
    *(int*)(this + 0xc4) = getParameter(*(int*)(this + 0xa8), "g_TexelSize");

    // Parameters from the main technique (+0x14)
    // +0xe4: "g_halfPixelOffset" (from main)
    *(int*)(this + 0xe4) = getParameter(*(int*)(this + 0x14), "g_halfPixelOffset");
    // +0xe8: same from second technique (+0xa8)
    *(int*)(this + 0xe8) = getParameter(*(int*)(this + 0xa8), "g_halfPixelOffset");
}
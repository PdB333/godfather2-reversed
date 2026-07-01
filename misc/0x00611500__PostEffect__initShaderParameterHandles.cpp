// FUNC_NAME: PostEffect::initShaderParameterHandles
// Address: 0x00611500
// Initializes shader parameter handles for a post-processing effect.
// Checks if pixel effect (this+0x14) is loaded; if not, zeros out many fields.
// Then loads handles from pixel effect and vertex effect (this+0x10).

class PostEffect {
public:
    // +0x00: vtable pointer (4 bytes)
    // +0x04: possible parent class members (size unknown)
    // +0x10: pointer to vertex shader effect object (used for vertex shader parameters)
    // +0x14: pointer to pixel shader effect object (used for pixel shader parameters)
    // Following fields are shader parameter handles (int/uint)
    // +0xa4: kClearColor handle
    // +0xc0: g_zbuffer_to_alpha_params handle
    // +0xf0: kBlurIntensity handle
    // +0xfc: ColorTexture handle
    // +0x104: ColorTexture3D handle
    // +0x10c: DepthTexture handle
    // +0x114: ToneMapTexture handle
    // +0x11c: kDelta (pixel) handle
    // +0x1e4: ColorTexture_HalfPixelOffset handle
    // +0x12c (300 decimal): gDeltaToRB handle
    // +0x120: kDelta (vertex) handle
    // +0x1e0: vPosScaleTranslationVS handle
    // ...other members possible

    void __thiscall initShaderParameterHandles();
};

// Helper function: likely returns a parameter handle from a shader effect.
// Signature: int getParameterHandle(Effect* effect, const char* name);
extern int __cdecl FUN_0060a580(void* effect, const char* name);

void __thiscall PostEffect::initShaderParameterHandles()
{
    // this is in ESI
    int* pixelEffect = *(int**)(this + 0x14);   // pointer to pixel shader effect
    if (pixelEffect == 0) {
        // No pixel effect loaded, zero out parameter handles
        *(int*)(this + 0xa4) = 0;   // kClearColor
        *(int*)(this + 0xc0) = 0;   // g_zbuffer_to_alpha_params
        *(int*)(this + 0xf0) = 0;   // kBlurIntensity
        *(int*)(this + 0xfc) = 0;   // ColorTexture
        *(int*)(this + 0x104) = 0;  // ColorTexture3D
        *(int*)(this + 0x10c) = 0;  // DepthTexture
        *(int*)(this + 0x114) = 0;  // ToneMapTexture
        *(int*)(this + 0x11c) = 0;  // kDelta (pixel)
        *(int*)(this + 0x1e4) = 0;  // ColorTexture_HalfPixelOffset
    } else {
        // Load pixel shader parameter handles
        *(int*)(this + 0xa4) = FUN_0060a580(pixelEffect, "kClearColor");
        *(int*)(this + 0xc0) = FUN_0060a580(pixelEffect, "g_zbuffer_to_alpha_params");
        *(int*)(this + 0xf0) = FUN_0060a580(pixelEffect, "kBlurIntensity");
        *(int*)(this + 0xfc) = FUN_0060a580(pixelEffect, "ColorTexture");
        *(int*)(this + 0x104) = FUN_0060a580(pixelEffect, "ColorTexture3D");
        *(int*)(this + 0x10c) = FUN_0060a580(pixelEffect, "DepthTexture");
        *(int*)(this + 0x114) = FUN_0060a580(pixelEffect, "ToneMapTexture");
        *(int*)(this + 0x11c) = FUN_0060a580(pixelEffect, "kDelta");
        *(int*)(this + 0x1e4) = FUN_0060a580(pixelEffect, "ColorTexture_HalfPixelOffset");
    }

    // Load vertex shader parameter handles from separate effect object (+0x10)
    int* vertexEffect = *(int**)(this + 0x10);   // pointer to vertex shader effect
    *(int*)(this + 0x12c) = FUN_0060a580(vertexEffect, "gDeltaToRB");   // offset 300 decimal = 0x12c
    *(int*)(this + 0x120) = FUN_0060a580(vertexEffect, "kDelta");       // vertex kDelta
    *(int*)(this + 0x1e0) = FUN_0060a580(vertexEffect, "vPosScaleTranslationVS");
    return;
}
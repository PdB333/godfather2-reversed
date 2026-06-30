// FUNC_NAME: ShaderParameterManager::initializeHandles
// Function address: 0x0053cb00
// Role: Initializes shader parameter handles for multiple blur/halo effects and a stencil effect.
// Calls: base init, getShadingEffect, getShaderParameterId

struct ShaderParameterBlock {
    unsigned int effect;            // +0x00 (offset from block start)
    unsigned int haloColor[4];      // +0x04, +0x08, +0x0C, +0x10
    unsigned int haloParam[4];      // +0x14, +0x18, +0x1C, +0x20
    unsigned int maskTexture;       // +0x24
    unsigned int maskHalfPixel;     // +0x28
}; // total 0x2C (44) bytes

// Global table of 7 shader effect data pointers, ending at 0x11283b0
extern void* g_shaderEffectDataTable[7];
// Separate stencil effect data pointer
extern void* g_stencilEffectData;

// Imported engine functions
extern void initBase();                                    // FUN_006127d0
extern unsigned int getShadingEffect(void* data);          // FUN_0060a2e0
extern unsigned int getShaderParameterId(unsigned int effect, const char* name); // FUN_0060a580

// Member offsets within the class (this pointer)
#define OFFSET_EFFECT_BLOCKS 0xA4    // ShaderParameterBlock array start
#define OFFSET_STENCIL_EFFECT 0x1E4  // stencil effect handle
#define OFFSET_STENCIL_TEXTURE 0x1D8 // stencil texture handle
#define OFFSET_STENCIL_1OVERSIZE 0x1DC // stencil_1oversize handle
#define OFFSET_STENCIL_HALFPIXEL 0x1E0 // g_stencilHalfPixelOffset handle

// Static strings used for parameter names
static const char* g_haloColorNames[4] = {
    "halo_color1",
    "halo_color2",
    "halo_color3",
    "halo_color4"
};
static const char* g_haloParamNames[4] = {
    "halo_param1",
    "halo_param2",
    "halo_param3",
    "halo_param4"
};

void __fastcall ShaderParameterManager::initializeHandles(void* thisPtr) {
    ShaderParameterBlock* block;
    int i;

    initBase();

    // Process 7 shader effect blocks
    for (int blockIdx = 0; blockIdx < 7; blockIdx++) {
        block = (ShaderParameterBlock*)((char*)thisPtr + OFFSET_EFFECT_BLOCKS + blockIdx * sizeof(ShaderParameterBlock));

        // Load effect handle
        block->effect = getShadingEffect(g_shaderEffectDataTable[blockIdx]);

        // Mask texture and half-pixel offset
        block->maskTexture = getShaderParameterId(block->effect, "mask_texture");
        block->maskHalfPixel = getShaderParameterId(block->effect, "g_maskHalfPixelOffset");

        // Halo color and param pairs (4 each)
        for (i = 0; i < 4; i++) {
            block->haloColor[i] = getShaderParameterId(block->effect, g_haloColorNames[i]);
            block->haloParam[i] = getShaderParameterId(block->effect, g_haloParamNames[i]);
        }
    }

    // Process stencil effect separately
    {
        unsigned int stencilEffect = getShadingEffect(g_stencilEffectData);
        *(unsigned int*)((char*)thisPtr + OFFSET_STENCIL_EFFECT) = stencilEffect;
        *(unsigned int*)((char*)thisPtr + OFFSET_STENCIL_TEXTURE) = getShaderParameterId(stencilEffect, "stencil_texture");
        *(unsigned int*)((char*)thisPtr + OFFSET_STENCIL_1OVERSIZE) = getShaderParameterId(stencilEffect, "stencil_1oversize");
        *(unsigned int*)((char*)thisPtr + OFFSET_STENCIL_HALFPIXEL) = getShaderParameterId(stencilEffect, "g_stencilHalfPixelOffset");
    }
}
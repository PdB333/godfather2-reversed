// Xbox PDB: AlchemyGaussianBlurShader::Load
// FUNC_NAME: PostEffectManager::initEffects
// Address: 0x0053d040
// This function initializes an array of 14 post-effect shader parameter blocks.
// Each block contains 7 shader parameter handles (e.g., kDelta, screen_texture, depth_texture, etc.)
// and a final handle (halfPixelOffsetXY) that is set separately from texture asset strings.

#include <cstdint>

// The structure of each post effect's shader parameters
struct PostEffectShaderParams {
    int kDelta;              // +0x00
    int screenTexture;       // +0x04
    int bbTexture;           // +0x08 (fallback if screenTexture is 0)
    int depthTexture;        // +0x0C
    int screenColor;         // +0x10
    int lodFade;             // +0x14
    int dofParams;           // +0x18
    int halfPixelOffsetXY;   // +0x1C
};

// Class that manages a chain of post-processing effects
class PostEffectManager {
public:
    // Initializes the effect array (called from constructor)
    void __fastcall initEffects();

private:
    // Offset 0xE8: array of 14 PostEffectShaderParams
    // The first effect's halfPixelOffsetXY is set to a global handle
    // The remaining 13 effects get their halfPixelOffsetXY from texture asset strings.
};

// Forward declarations of helpers (likely from EARS engine)
extern void basePostEffectInit();          // FUN_006127d0
extern uint32_t loadTextureAsset(const char* name);  // FUN_0060a2e0
extern uint32_t getShaderParam(uint32_t effectHandle, const char* paramName); // FUN_0060a580

// External constant data (string pointers)
extern const char* textureAsset0;    // PTR_DAT_010be140
extern const char* textureAsset1;    // PTR_DAT_010be160
extern const char* textureAsset2;    // PTR_DAT_010be150
extern const char* textureAsset3;    // PTR_DAT_010be0a0
extern const char* textureAsset4;    // PTR_DAT_010be0b0
extern const char* textureAsset5;    // PTR_DAT_010be0c0
extern const char* textureAsset6;    // PTR_DAT_010be0d0
extern const char* textureAsset7;    // PTR_DAT_010be0e0
extern const char* textureAsset8;    // PTR_DAT_010be0f0
extern const char* textureAsset9;    // PTR_DAT_010be100
extern const char* textureAsset10;   // PTR_DAT_010be110
extern const char* textureAsset11;   // PTR_DAT_010be120
extern const char* textureAsset12;   // PTR_DAT_010be130

// Global handle for default effect
extern uint32_t defaultEffectHandle; // DAT_012198f8

void __fastcall PostEffectManager::initEffects()
{
    basePostEffectInit();

    // The array of 14 effect parameter blocks starts at offset 0xE8 in this object
    PostEffectShaderParams* effects = reinterpret_cast<PostEffectShaderParams*>(
        reinterpret_cast<char*>(this) + 0xE8);

    // Set the last field (halfPixelOffsetXY) of the first effect to a global handle
    effects[0].halfPixelOffsetXY = defaultEffectHandle;

    // For effects 1..13, load texture assets and store their handles
    effects[1].halfPixelOffsetXY = loadTextureAsset(textureAsset0);  // offset 0x124
    effects[2].halfPixelOffsetXY = loadTextureAsset(textureAsset1);  // offset 0x144
    effects[3].halfPixelOffsetXY = loadTextureAsset(textureAsset2);  // offset 0x164
    effects[4].halfPixelOffsetXY = loadTextureAsset(textureAsset3);  // offset 0x184
    effects[5].halfPixelOffsetXY = loadTextureAsset(textureAsset4);  // offset 0x1A4
    effects[6].halfPixelOffsetXY = loadTextureAsset(textureAsset5);  // offset 0x1C4
    effects[7].halfPixelOffsetXY = loadTextureAsset(textureAsset6);  // offset 0x1E4
    effects[8].halfPixelOffsetXY = loadTextureAsset(textureAsset7);  // offset 0x204
    effects[9].halfPixelOffsetXY = loadTextureAsset(textureAsset8);  // offset 0x224
    effects[10].halfPixelOffsetXY = loadTextureAsset(textureAsset9); // offset 0x244
    effects[11].halfPixelOffsetXY = loadTextureAsset(textureAsset10); // offset 0x264
    effects[12].halfPixelOffsetXY = loadTextureAsset(textureAsset11); // offset 0x284
    effects[13].halfPixelOffsetXY = loadTextureAsset(textureAsset12); // offset 0x2A4

    // Now fill in the remaining 7 shader parameter handles for all 14 effects
    for (int i = 0; i < 14; ++i)
    {
        PostEffectShaderParams& cur = effects[i];
        uint32_t effectHandle = cur.halfPixelOffsetXY;

        cur.kDelta = getShaderParam(effectHandle, "kDelta");
        int screenTex = getShaderParam(effectHandle, "screen_texture");
        if (screenTex == 0) {
            screenTex = getShaderParam(effectHandle, "bb_texture");
        }
        cur.screenTexture = screenTex;
        cur.depthTexture = getShaderParam(effectHandle, "depth_texture");
        cur.screenColor = getShaderParam(effectHandle, "screen_color");
        cur.lodFade = getShaderParam(effectHandle, "lod_fade");
        cur.dofParams = getShaderParam(effectHandle, "dof_params");
        // halfPixelOffsetXY is already set; no need to assign again
    }
}
// Xbox PDB: AlchemyScreenShared::Load
// FUNC_NAME: PostProcessManager::initShaderHandles
// Address: 0x00530630
// Role: Initializes global shader effect and parameter handles for post-processing effects.
// This function loads several shader/effect resources and retrieves their parameters (screen_texture, screen_color, scaling, half-pixel offset, vertex position scale).
// It is called during initialization to set up rendering state.

#include <cstdint>

// Forward declarations of engine functions (assumed from EA EARS)
// Loads a shader effect from a given path/name string.
uint32_t getEffect(const char* effectName);
// Creates a default parameter block (possibly for vertex shader constants).
uint32_t createDefaultParameterBlock();
// Retrieves a parameter handle by name from an effect/parameter block.
uint32_t getParameter(uint32_t effectHandle, const char* paramName);

// Global handles (likely static members of PostProcessManager)
extern uint32_t g_screenEffectA;          // DAT_012198f0
extern uint32_t g_screenEffectAParams;    // DAT_012198f4
extern uint32_t g_screenEffectB;          // DAT_012198f8
extern uint32_t g_screenEffectC;          // DAT_012198fc
extern uint32_t g_screenEffectDParams;    // DAT_01219900
extern uint32_t g_screenEffectD;          // DAT_01219904
extern uint32_t g_screenEffectEParams;    // DAT_01219908
extern uint32_t g_screenEffectE;          // DAT_0121990c
extern uint32_t g_screenTextureParamB;    // DAT_01219910
extern uint32_t g_screenTextureParamC;    // DAT_01219914
extern uint32_t g_scalingParamE;          // _DAT_01219918
extern uint32_t g_screenColorParamB;      // DAT_0121991c
extern uint32_t g_screenColorParamA;      // DAT_01219920
extern uint32_t g_screenTextureHalfPixelParamB; // DAT_0121992c
extern uint32_t g_screenTextureHalfPixelParamC; // DAT_01219930
extern uint32_t g_vPosScaleTranslationVSParamD; // DAT_01219924
extern uint32_t g_vPosScaleTranslationVSParamE; // DAT_01219928

void PostProcessManager::initShaderHandles()
{
    // Load effects by name (strings referenced via global PTR_DAT_*)
    g_screenEffectA = getEffect("effectA_path");              // PTR_DAT_010be970
    g_screenEffectAParams = createDefaultParameterBlock();    // FUN_0060a380

    g_screenEffectB = getEffect("effectB_path");              // PTR_DAT_010be9a0
    g_screenEffectC = getEffect("effectC_path");              // PTR_DAT_010be9b0

    g_screenEffectDParams = createDefaultParameterBlock();    // FUN_0060a380
    g_screenEffectD = getEffect("effectD_path");              // PTR_DAT_010bea10

    g_screenEffectEParams = createDefaultParameterBlock();    // FUN_0060a380
    g_screenEffectE = getEffect("effectE_path");              // PTR_DAT_010bde90

    // Retrieve shader parameters
    g_screenTextureParamB = getParameter(g_screenEffectB, "screen_texture");
    g_screenTextureParamC = getParameter(g_screenEffectC, "screen_texture");

    g_scalingParamE = getParameter(g_screenEffectE, "scaling");

    g_screenColorParamB = getParameter(g_screenEffectB, "screen_color");
    g_screenColorParamA = getParameter(g_screenEffectA, "screen_color");

    g_screenTextureHalfPixelParamB = getParameter(g_screenEffectB, "screen_texture_halfPixelOffset");
    g_screenTextureHalfPixelParamC = getParameter(g_screenEffectC, "screen_texture_halfPixelOffset");

    g_vPosScaleTranslationVSParamD = getParameter(g_screenEffectDParams, "vPosScaleTranslationVS");
    g_vPosScaleTranslationVSParamE = getParameter(g_screenEffectEParams, "vPosScaleTranslationVS");
}
// FUNC_NAME: PostEffectManager::initShaders

// 0x0053d6e0 - Initialize post-processing shader handles and parameter indices for multiple effect shaders

class PostEffectManager {
public:
    // +0x10: Shader system pointer (ID3D11DeviceContext or similar)
    uintptr_t m_shaderSystem;

    // +0xac: Handle for "vPosScaleTranslationVS" vertex shader parameter
    uint m_vPosScaleTranslationVSHandle;

    // Default constructor
    PostEffectManager() {
        // Initialize base (likely memset or sub-object constructor)
        baseInit();
        
        // Get shader system interface
        m_shaderSystem = getShaderSystem();
        
        // Per-shader block: up to 55 shader slots, each with:
        //   - shaderProgramHandle
        //   - handles[6] for texture parameters
        //   - handles for various bloom/DOF params
        //   - featureMask (bitmask indicating which parameters exist)
        struct PerShaderData {
            uint shaderProgramHandle;       // -0x1a relative to base
            uint textureHandles[6];         // -0x16 to -0x11
            uint bbTextureHandle;           // -0x19
            uint gLutParams1Handle;         // -0x18
            uint gLutParams2Handle;         // -0x17
            uint bloomTintColorHandle;      // -0x10
            uint bloomBlacktintColorHandle; // -0xf
            uint bloomTextureHandle;        // -0xe
            uint bloomDcolorHandle;         // -0xd
            uint bloomBlackcolorHandle;     // -0xc
            uint gTexelSizeHandle;          // -0xb
            uint vignetteTextureHandle;     // -10
            uint depthTextureHandle;        // -9
            uint dofParamsHandle;           // -8
            uint blurTextureHandle;         // -7
            uint dofFadeHandle;             // -6
            uint gLutBlueSliceHandle;       // -5
            uint saturateColorHandle;       // -4
            uint gHalfPixelOffsetHandle;    // -3
            uint gBloomHalfPixelOffsetHandle;// -2
            uint gBlurHalfPixelOffsetHandle; // -1
            uint featureMask;               // *puVar7 at base (offset 0)
        } m_shaderData[55]; // offset from DAT_01198ee8?

        // Global shader IDs array (DAT_011283b0, 55 entries)
        static int s_shaderIDs[55] = { /* ... */ };
        // Global string array for texture names (PTR_s_gLUTTexture1_010beb44)
        // 6 entries: "gLUTTexture1", etc.
        static const char* s_textureNames[6] = {
            "gLUTTexture1", "gLUTTexture2", "gLUTTexture3",
            "gLUTTexture4", "gLUTTexture5", "gLUTTexture6"
        };

        // Loop through each shader slot
        for (int i = 0; i < 55; i++) {
            PerShaderData* shader = &m_shaderData[i];
            uint shaderID = s_shaderIDs[i];
            
            shader->featureMask = 0; // Reset mask
            
            if (shaderID != 0) {
                // Load the shader program, store handle
                shader->shaderProgramHandle = loadShaderProgram(shaderID);
                
                // Load 6 texture parameter handles
                for (int j = 0; j < 6; j++) {
                    uint handle = getParameterHandle(shader->shaderProgramHandle, s_textureNames[j]);
                    shader->textureHandles[j] = handle;
                    if (handle != 0) {
                        shader->featureMask |= (0x100 << (j * 8)); // Bits 8, 9, ...? Actually pattern: 0x100, 0x200, ...
                    }
                }
                
                // Load additional post-processing parameter handles
                shader->bbTextureHandle = getParameterHandle(shader->shaderProgramHandle, "bb_texture");
                shader->gLutParams1Handle = getParameterHandle(shader->shaderProgramHandle, "gLUT_params1");
                shader->gLutParams2Handle = getParameterHandle(shader->shaderProgramHandle, "gLUT_params2");
                shader->bloomTintColorHandle = getParameterHandle(shader->shaderProgramHandle, "bloom_tintColor");
                shader->bloomBlacktintColorHandle = getParameterHandle(shader->shaderProgramHandle, "bloom_blacktintColor");
                shader->bloomTextureHandle = getParameterHandle(shader->shaderProgramHandle, "bloom_texture");
                shader->bloomDcolorHandle = getParameterHandle(shader->shaderProgramHandle, "bloom_dcolor");
                shader->bloomBlackcolorHandle = getParameterHandle(shader->shaderProgramHandle, "bloom_blackcolor");
                shader->gTexelSizeHandle = getParameterHandle(shader->shaderProgramHandle, "g_TexelSize");
                shader->vignetteTextureHandle = getParameterHandle(shader->shaderProgramHandle, "vignetteTexture");
                shader->depthTextureHandle = getParameterHandle(shader->shaderProgramHandle, "depth_texture");
                shader->dofParamsHandle = getParameterHandle(shader->shaderProgramHandle, "dof_params");
                shader->blurTextureHandle = getParameterHandle(shader->shaderProgramHandle, "blurTexture");
                shader->dofFadeHandle = getParameterHandle(shader->shaderProgramHandle, "dofFade");
                shader->gLutBlueSliceHandle = getParameterHandle(shader->shaderProgramHandle, "gLutBlueSlice");
                shader->saturateColorHandle = getParameterHandle(shader->shaderProgramHandle, "saturateColor");
                shader->gHalfPixelOffsetHandle = getParameterHandle(shader->shaderProgramHandle, "g_halfPixelOffset");
                shader->gBloomHalfPixelOffsetHandle = getParameterHandle(shader->shaderProgramHandle, "g_bloom_halfPixelOffset");
                shader->gBlurHalfPixelOffsetHandle = getParameterHandle(shader->shaderProgramHandle, "g_blur_halfPixelOffset");
                
                // Update feature mask based on which parameters exist
                if (shader->bloomTintColorHandle != 0) {
                    shader->featureMask |= 0x4;
                }
                if (shader->bloomBlackcolorHandle == 0 && (shader->featureMask & 0x4) != 0) {
                    shader->featureMask |= 0x8;
                }
                if (shader->gTexelSizeHandle != 0) {
                    shader->featureMask |= 0x10;
                }
                if (shader->vignetteTextureHandle != 0) {
                    shader->featureMask |= 0x1;
                }
                if (shader->dofParamsHandle != 0) {
                    shader->featureMask |= 0x20;
                }
                if (shader->gLutBlueSliceHandle != 0) {
                    shader->featureMask |= 0x80;
                }
                if (shader->saturateColorHandle != 0) {
                    shader->featureMask |= 0x2;
                }
            }
        }
        
        // Load a global vertex shader parameter if shader system is present
        if (m_shaderSystem != 0) {
            // Note: This uses m_shaderSystem directly, not a specific shader program handle.
            // Possibly the vertex shader is fixed/global.
            m_vPosScaleTranslationVSHandle = getParameterHandle(m_shaderSystem, "vPosScaleTranslationVS");
        }
    }

private:
    void baseInit();         // FUN_006127d0 - Initialize base class/vtable
    uintptr_t getShaderSystem(); // FUN_0060a380 - Get shader manager/device
    uint loadShaderProgram(int fileID);    // FUN_0060a2e0 - Load a shader by identifier
    uint getParameterHandle(uintptr_t shader, const char* name); // FUN_0060a580 - Get parameter location
};
// Note: This is a simplified reconstruction. The actual class layout likely involves multiple base classes and the data members are stored at fixed offsets relative to 'this'.
// FUN_00493ce0: ShaderConstantManager::initializeConstants

class ShaderConstantManager {
public:
    // Assuming virtual table pointer at +0x00, but not shown
    // Offsets (relative to this):
    // +0x10: unknownField0x10 (maybe a device pointer or something)
    // +0x14: rendererDevice
    // +0x230: some copy of +0x10
    // +0x234: rendererDevice (duplicate)
    // +0x2e0: handle for g_lightColorSH
    // +0x4b0: handle for g_shadowAttenuationBuffer
    // +0x4b8: handle for g_attenuationFactor (later overwritten by g_attenuationFactor2)
    // +0x4d0: handle for g_lightSampler

    void __thiscall initializeConstants() {
        // Get the renderer device from a global pointer
        void* rendererDevice = getRendererDevice(&PTR_DAT_0110a0fc);
        this->rendererDevice1 = rendererDevice; // +0x234
        this->rendererDevice2 = rendererDevice; // +0x14

        baseClassInit(); // FUN_004907a0

        // Copy something from offset 0x10 to 0x230
        this->field_0x230 = this->field_0x10;

        initLightingConstants(); // FUN_00493a10

        // Look up shader constant handles
        this->shadowAttenuationBufferHandle = getShaderConstantHandle(this->rendererDevice1, "g_shadowAttenuationBuffer"); // +0x4b0
        this->attenuationFactorHandle = getShaderConstantHandle(this->rendererDevice1, "g_attenuationFactor"); // +0x4b8

        initShadowConstants(); // FUN_00491d00

        this->lightColorSHHandle = getShaderConstantHandle(this->rendererDevice1, "g_lightColorSH"); // +0x2e0
        // Note: overwrites the previous attenuation factor handle
        this->attenuationFactorHandle = getShaderConstantHandle(this->rendererDevice1, "g_attenuationFactor2"); // +0x4b8
        this->lightSamplerHandle = getShaderConstantHandle(this->rendererDevice1, "g_lightSampler"); // +0x4d0
    }

private:
    // Member fields (declared in order of offset, but actual layout unknown)
    int field_0x10; // +0x10
    void* rendererDevice2; // +0x14
    int field_0x230; // +0x230, copied from field_0x10
    void* rendererDevice1; // +0x234
    int lightColorSHHandle; // +0x2e0
    int shadowAttenuationBufferHandle; // +0x4b0
    int attenuationFactorHandle; // +0x4b8
    int lightSamplerHandle; // +0x4d0
};

// External functions (stubs based on guessed names)
void* getRendererDevice(void** globalPtr);
void baseClassInit();
void initLightingConstants();
void initShadowConstants();
int getShaderConstantHandle(void* device, const char* name); // FUN_0060a580
// Xbox PDB: SM_DeferredSpotLightClass::GetParamHandles
// FUNC_NAME: LightShaderEffect::init
void LightShaderEffect::init() {
    // +0x10: pointer to shader (?) - set to global shader object
    *(void**)(this + 0x10) = (void*)DAT_01205458;

    // Call base class init (likely)
    FUN_00490a50(); // Base::init or similar

    // Look up shader constant handles by name
    // +0x1c0: handle for g_lightDirection
    *(int*)(this + 0x1c0) = FUN_0060a580(*(void**)(this + 0x14), "g_lightDirection");
    // +0x1e0: handle for g_spotLightCoordScale
    *(int*)(this + 0x1e0) = FUN_0060a580(DAT_01205458, "g_spotLightCoordScale");
}
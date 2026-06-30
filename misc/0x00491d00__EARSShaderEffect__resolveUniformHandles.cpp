// FUNC_NAME: EARSShaderEffect::resolveUniformHandles

void __thiscall EARSShaderEffect::resolveUniformHandles(void)
{
    // Call base initialization (likely sets up shader program state)
    baseInitialize();

    // Resolve uniform handles from the shader program stored at +0x14
    // +0x1c0: handle for "g_lightDirection"
    *(uint32_t *)(this + 0x1c0) = getShaderParameterHandle(
        *(uint32_t *)(this + 0x14), "g_lightDirection");

    // +0x1e0: handle for "g_shadowAttenuationBuffer"
    *(uint32_t *)(this + 0x1e0) = getShaderParameterHandle(
        *(uint32_t *)(this + 0x14), "g_shadowAttenuationBuffer");

    // +0x1e8: handle for "g_attenuationFactor"
    *(uint32_t *)(this + 0x1e8) = getShaderParameterHandle(
        *(uint32_t *)(this + 0x14), "g_attenuationFactor");

    // +0x200: handle for "g_shadowColor"
    *(uint32_t *)(this + 0x200) = getShaderParameterHandle(
        *(uint32_t *)(this + 0x14), "g_shadowColor");
}
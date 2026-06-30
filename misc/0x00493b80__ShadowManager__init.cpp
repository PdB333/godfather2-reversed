// FUNC_NAME: ShadowManager::init
void __thiscall ShadowManager::init(void)
{
    // Call base initialization
    baseInit();  // FUN_00493a10

    // Look up shader constant IDs for shadow attenuation
    // The member at +0x14 is probably a pointer to the renderer/device object
    int shadowAttenBufferID = getShaderConstant(*(void**)(this + 0x14), "g_shadowAttenuationBuffer");
    *(int*)(this + 0x290) = shadowAttenBufferID;

    int attenuationFactorID = getShaderConstant(*(void**)(this + 0x14), "g_attenuationFactor");
    *(int*)(this + 0x298) = attenuationFactorID;
}
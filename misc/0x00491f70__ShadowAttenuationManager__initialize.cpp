// FUNC_NAME: ShadowAttenuationManager::initialize
void __thiscall ShadowAttenuationManager::initialize()
{
    // Get render device/shadersystem handle via external global
    m_ShaderSystem = getShaderSystem(g_GlobalShaderSystem);  // offset +0x14

    // Initialize base class or other component
    initAttenuationBase();  // FUN_004907a0

    // Look up shader parameter handles for shadow attenuation
    m_ShadowAttenuationBufferHandle = getShaderParameter(m_ShaderSystem, "g_shadowAttenuationBuffer");  // offset +0x1e0
    m_AttenuationFactorHandle = getShaderParameter(m_ShaderSystem, "g_attenuationFactor");              // offset +0x1e8

    // Finalize setup
    finalizeAttenuation();  // FUN_00491d00
}
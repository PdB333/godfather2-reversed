// FUNC_NAME: ShadowShader::initShaderParameters
void ShadowShader::initShaderParameters() {
    // Base initialization
    baseInit(); // FUN_00490a50

    // Retrieve handle for light direction
    m_lightDirectionHandle = getShaderParameterHandle(m_shaderManager, "g_lightDirection"); // +0x1c0

    // Retrieve handles for 4 shadow samplers (g_shadowSampler0..3)
    for (int i = 0; i < 4; i++) {
        m_shadowSamplerHandles[i] = getShaderParameterHandle(m_shaderManager, s_shadowSamplerNames[i]); // +0x1e0 array of 4
    }

    // Retrieve other shadow-related parameter handles
    m_viewToShadowHandle = getShaderParameterHandle(m_shaderManager, "g_view_to_shadow"); // +0x200
    m_shadowMulAddConversionHandle = getShaderParameterHandle(m_shaderManager, "g_shadowMulAddConversion"); // +0x204
    m_shadowTextureSizeHandle = getShaderParameterHandle(m_shaderManager, "g_shadowTextureSize"); // +0x290
    m_shadowColorHandle = getShaderParameterHandle(m_shaderManager, "g_shadowColor"); // +0x29c
    m_shadowDensityHandle = getShaderParameterHandle(m_shaderManager, "g_shadowDensity"); // +0x2b0
    m_zPlaneNear123Handle = getShaderParameterHandle(m_shaderManager, "g_ZPlaneNear123"); // +0x2bc
}
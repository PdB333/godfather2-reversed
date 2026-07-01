// FUNC_NAME: LightingEffect::initShaderHandles
void LightingEffect::initShaderHandles(void)
{
    // Call base class initializer (e.g., EffectBase::init)
    baseInit();

    // Retrieve shader parameter handles from the shader manager (stored at +0x14)
    m_quadricMtxR   = getShaderHandle(m_shaderManager, "g_SHQuadricMtxR");   // +0x318
    m_quadricMtxG   = getShaderHandle(m_shaderManager, "g_SHQuadricMtxG");   // +0x31c
    m_quadricMtxB   = getShaderHandle(m_shaderManager, "g_SHQuadricMtxB");   // +0x320 (offset 800)
    m_lightDirection2 = getShaderHandle(m_shaderManager, "g_lightDirection2"); // +0x2d4
    m_lightColor2   = getShaderHandle(m_shaderManager, "g_lightColor2");     // +0x2f0
    m_diffuseAmbient2 = getShaderHandle(m_shaderManager, "g_diffuseAmbient2"); // +0x310
    m_lightColorSH  = getShaderHandle(m_shaderManager, "g_lightColorSH");    // +0x3f0
}
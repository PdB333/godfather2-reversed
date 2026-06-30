// Xbox PDB: SM_DeferredShadowSpotLightClass::GetParamHandles
// FUNC_NAME: ShadowShader::initUniforms

void ShadowShader::initUniforms()
{
    // +0x10: store some global shader program handle (maybe for spot shadows)
    *(int*)(this + 0x10) = g_shaderManager; // DAT_01205458

    // Call base class initialization (e.g., material common init)
    __thiscall baseInit(); // FUN_00490a50

    // Retrieve uniform locations for shadow shader inputs
    // +0x14: primary shader program handle (probably the shadow volume shader)
    *(int*)(this + 0x1c0) = getUniformLocation(*(int*)(this + 0x14), "g_lightDirection");
    // Note: second call uses global shader manager directly (possibly a different shader program for spot lights)
    *(int*)(this + 0x1e0) = getUniformLocation(g_shaderManager, "g_spotLightCoordScale");
    *(int*)(this + 0x1f0) = getUniformLocation(*(int*)(this + 0x14), "g_shadowSampler");
    *(int*)(this + 0x1f8) = getUniformLocation(*(int*)(this + 0x14), "g_view_to_shadow");
    *(int*)(this + 0x240) = getUniformLocation(*(int*)(this + 0x14), "g_shadowTextureSize");
    *(int*)(this + 0x24c) = getUniformLocation(*(int*)(this + 0x14), "g_shadowColor");
    *(int*)(this + 0x260) = getUniformLocation(*(int*)(this + 0x14), "g_shadowDensity");
}
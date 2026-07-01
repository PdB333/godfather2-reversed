// Xbox PDB: SM_DeferredBoxVars::GetParamHandles
// FUNC_NAME: BoxLightShader::initializeShaderHandles

void BoxLightShader::initializeShaderHandles(void)
{
    int handle;
    
    // +0x14: pointer to render device (IRenderDevice*)
    // FUN_0060a580 = getParameterHandle(IRenderDevice*, const char*)
    handle = getParameterHandle(*(IRenderDevice**)(this + 0x14), "g_boxLightInvMtx");
    *(int*)(this + 0x4) = handle;                           // m_hInvMtx
    
    handle = getParameterHandle(*(IRenderDevice**)(this + 0x14), "g_boxLightFBScale");
    *(int*)(this + 0x50) = handle;                          // m_hFBScale
    
    handle = getParameterHandle(*(IRenderDevice**)(this + 0x14), "g_boxLightFBOffset");
    *(int*)(this + 0x70) = handle;                          // m_hFBOffset
    
    return;
}
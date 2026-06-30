// 0x00493480: ShadowShader::initialize
void ShadowShader::initialize()
{
    // +0x10: handle to primary shader program (e.g., forward rendering shadow shader)
    this->field_0x10 = DAT_01205458;
    
    // Call base class initialization (likely initializes common shader state)
    // FUN_00490a50 is assumed to be a base class method (e.g., ShaderBase::init)
    this->initBase();
    
    // +0x14: handle to a secondary shader program (e.g., a specialized shadow pass)
    // +0x1c0: handle for "g_lightDirection" uniform/parameter in the secondary shader
    this->field_0x1c0 = getShaderConstantHandle(this->field_0x14, "g_lightDirection");
    
    // +0x1e0: handle for "g_spotLightCoordScale" uniform in the primary shader
    this->field_0x1e0 = getShaderConstantHandle(DAT_01205458, "g_spotLightCoordScale");
    
    // +0x1f0: handle for "g_lensMap" texture parameter in the secondary shader
    this->field_0x1f0 = getShaderConstantHandle(this->field_0x14, "g_lensMap");
    
    // +0x1f8: handle for "g_view_to_shadow" matrix uniform in the secondary shader
    this->field_0x1f8 = getShaderConstantHandle(this->field_0x14, "g_view_to_shadow");
}
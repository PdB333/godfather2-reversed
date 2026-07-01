// FUNC_NAME: ShaderEffect::initShaderParameters
void __thiscall ShaderEffect::initShaderParameters(void)
{
    // Store handles to shader constants for this effect
    // this->+0x14: pointer to shader program object
    // this->+0xa4: g_zBuffer handle
    // this->+0xa8: g_nBuffer handle
    // this->+0xac: g_lightCenter handle
    // this->+0xc0: g_lightColor handle
    // this->+0xe0: g_lightParams handle
    // this->+0x100: g_screenSpaceToWorldSpace handle
    // this->+0x150: g_screenSpaceToViewSpace handle
    // this->+0x1a0: g_invFBSize handle
    // this->+0x1ac: g_diffuseAmbient handle

    *(void**)(this + 0xa4) = getShaderParameterHandle(*(void**)(this + 0x14), "g_zBuffer");
    *(void**)(this + 0xa8) = getShaderParameterHandle(*(void**)(this + 0x14), "g_nBuffer");
    *(void**)(this + 0xac) = getShaderParameterHandle(*(void**)(this + 0x14), "g_lightCenter");
    *(void**)(this + 0xc0) = getShaderParameterHandle(*(void**)(this + 0x14), "g_lightColor");
    *(void**)(this + 0xe0) = getShaderParameterHandle(*(void**)(this + 0x14), "g_lightParams");
    *(void**)(this + 0x100) = getShaderParameterHandle(*(void**)(this + 0x14), "g_screenSpaceToWorldSpace");
    *(void**)(this + 0x150) = getShaderParameterHandle(*(void**)(this + 0x14), "g_screenSpaceToViewSpace");
    *(void**)(this + 0x1a0) = getShaderParameterHandle(*(void**)(this + 0x14), "g_invFBSize");
    *(void**)(this + 0x1ac) = getShaderParameterHandle(*(void**)(this + 0x14), "g_diffuseAmbient");

    // Finalize shader setup (e.g., bind parameters, upload constants)
    somePostInitFunction();
}
// FUNC_NAME: setVisualEffect
// Address: 0x00537c40
// Description: Toggles a visual effect (e.g., night vision, thermal) based on param_1.
// Uses global render manager and camera data.

void setVisualEffect(char enable)
{
    // g_renderManager: global render manager instance (DAT_0121a390)
    // g_camera: global camera structure (DAT_0121b63c)
    // +0x1c: some shader parameter index or constant ID
    uint32_t shaderParamIndex = *(uint32_t*)(g_camera + 0x1c);
    // Set the shader parameter (e.g., intensity, blend factor)
    setShaderConstant(g_renderManager, shaderParamIndex);

    // Choose the appropriate resource (texture/constant buffer) based on enable
    void* resource;
    if (enable == 0) {
        resource = &g_effectResourceOff; // DAT_00e2e770
    } else {
        resource = &g_effectResourceOn;  // DAT_011280d0
    }

    // +0x2c: another parameter (e.g., texture slot or render target index)
    uint32_t textureSlot = *(uint32_t*)(g_camera + 0x2c);
    // Bind the resource to the render manager
    setTexture(g_renderManager, textureSlot, resource);
}
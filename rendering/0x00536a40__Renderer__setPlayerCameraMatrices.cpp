// FUNC_NAME: Renderer::setPlayerCameraMatrices
void Renderer::setPlayerCameraMatrices(float proj[4], float view[4], float lightDir[4], float world[4])
{
    // Global storage for camera matrices
    _DAT_0121a2f4 = proj;       // +0x0: Projection matrix (4 floats)
    _DAT_0121a2f8 = view;       // +0x4: View matrix (4 floats)
    _DAT_0121a2fc = lightDir;   // +0x8: Light direction vector (4 floats)
    _DAT_0121a2c0 = world;      // +0x0: World matrix (4 floats) - stored separately
    _DAT_0121a2f0 = in_XMM0_Da; // +0x10: Unused/original value from XMM0

    // Check if we need to update shader constants
    if ((DAT_012058e8 == &DAT_0121a1f0) && (DAT_0121a200 == DAT_0121a368)) {
        // Update vertex shader constant buffer
        FUN_0060add0(DAT_0121a368, DAT_0121a328, &DAT_0121a2f0);  // SetVertexShaderConstantF
        // Update pixel shader constant buffer
        FUN_0060add0(DAT_0121a368, DAT_0121a344, &DAT_0121a2c0);  // SetPixelShaderConstantF
    }
}
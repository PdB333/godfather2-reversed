// FUNC_NAME: LightShaderManager::setupLightShaderParams
void __fastcall LightShaderManager::setupLightShaderParams(int thisPtr)
{
    // +0x1e0: pointer to self (likely used for some generic pattern)
    *(int *)(thisPtr + 0x1e0) = thisPtr;

    // Get the render device from global pointer
    int renderDevice = getRenderDevice(&PTR_DAT_0110a13c);
    // +0x14: render device handle
    *(int *)(thisPtr + 0x14) = renderDevice;

    // Initialize default box light settings (unknown internal setup)
    setupDefaultBoxLight();

    // Retrieve shader parameter handles for box lighting
    // +0x1e4: g_boxLightInvMtx handle
    *(int *)(thisPtr + 0x1e4) = getShaderParameter(*(int *)(*(int *)(thisPtr + 0x1e0) + 0x14), "g_boxLightInvMtx");
    // +0x230: g_boxLightFBScale handle
    *(int *)(thisPtr + 0x230) = getShaderParameter(*(int *)(*(int *)(thisPtr + 0x1e0) + 0x14), "g_boxLightFBScale");
    // +0x250: g_boxLightFBOffset handle
    *(int *)(thisPtr + 0x250) = getShaderParameter(*(int *)(*(int *)(thisPtr + 0x1e0) + 0x14), "g_boxLightFBOffset");

    // Initialize default directional light settings
    setupDefaultDirectionalLight();

    // Retrieve shader parameter handle for directional light direction
    // +0x1c0: g_lightDirection handle
    *(int *)(thisPtr + 0x1c0) = getShaderParameter(*(int *)(thisPtr + 0x14), "g_lightDirection");
}
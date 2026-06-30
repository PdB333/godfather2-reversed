// FUNC_NAME: Renderer::updateTextureAndShaderSets
void Renderer::updateTextureAndShaderSets(void)
{
    // Global flag indicating high-quality mode (e.g., from graphics settings)
    // DAT_01163840: bool g_bHighQuality
    // DAT_01163810: high-quality texture data
    // DAT_00e2e760: low-quality texture data
    // DAT_011637d0: high-quality shader data
    // DAT_00e2e720: low-quality shader data
    // DAT_0121a394: g_pRenderer (Renderer*)
    // DAT_0121b0ac: g_pRenderSettings (RenderSettings*)
    // Offsets 0x24, 0x28: likely textureSlotIndex, shaderSlotIndex

    void* pTextureData;
    if (DAT_01163840 == '\0') {
        pTextureData = &DAT_00e2e760;  // low-res textures
    } else {
        pTextureData = &DAT_01163810;  // high-res textures
    }
    setTextureData(DAT_0121a394, *(undefined4 *)(DAT_0121b0ac + 0x24), pTextureData);

    void* pShaderData;
    if (DAT_01163840 == '\0') {
        pShaderData = &DAT_00e2e720;  // low-quality shaders
    } else {
        pShaderData = &DAT_011637d0;  // high-quality shaders
    }
    setShaderData(DAT_0121a394, *(undefined4 *)(DAT_0121b0ac + 0x28), pShaderData);
}
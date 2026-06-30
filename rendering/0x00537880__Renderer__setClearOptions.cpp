// FUNC_NAME: Renderer::setClearOptions
void Renderer::setClearOptions(void)
{
    // Determine which texture/color data pointer to use based on a flag (DAT_01163840)
    // DAT_01163840 is a boolean flag (0 or 1) – possibly "use alternate clear color set"
    void* clearColorData;
    if (DAT_01163840 == '\0') {
        clearColorData = &DAT_00e2e760;  // Alternate clear color data
    } else {
        clearColorData = &DAT_01163810;  // Default clear color data
    }
    // Call function to set clear color on the render device (DAT_0121a394)
    // DAT_0121b0ac +0x24 is likely a pointer to a render target or framebuffer object
    FUN_0060add0(DAT_0121a394, *(uint32_t*)(DAT_0121b0ac + 0x24), clearColorData);

    // Determine which depth/stencil clear data pointer to use
    void* depthStencilData;
    if (DAT_01163840 == '\0') {
        depthStencilData = &DAT_00e2e720;  // Alternate depth/stencil clear data
    } else {
        depthStencilData = &DAT_011637d0;  // Default depth/stencil clear data
    }
    // Call function to set depth/stencil clear parameters
    // DAT_0121b0ac +0x28 is likely another render target (depth/stencil buffer)
    FUN_0060b020(DAT_0121a394, *(uint32_t*)(DAT_0121b0ac + 0x28), depthStencilData);
}
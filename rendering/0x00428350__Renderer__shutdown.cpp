// FUNC_NAME: Renderer::shutdown

void Renderer::shutdown(void)
{
    // Check if renderer was ever initialized
    if (g_bRendererInitialized != '\0')
    {
        // Zero out various renderer state counters
        g_dwRenderTargetCount    = 0;  // +0x0 at 0x01163cac
        g_dwDrawCallCount        = 0;  // +0x8 at 0x01163cb4
        g_dwTriangleCount        = 0;  // +0x10 at 0x01163cbc
        g_dwTextureBindCount     = 0;  // +0x18 at 0x01163cc4

        // Flush any remaining commands
        Renderer::flushCommandBuffer();

        // Release the rendering device
        Renderer::releaseDevice();

        // Process and destroy all render lists
        Renderer::forEachRenderList(Renderer::deleteRenderListCallback);

        // If post‑processing effects are active, destroy them
        if (g_bPostEffectsEnabled != '\0')
        {
            Renderer::destroyPostEffects();
            g_bPostEffectsEnabled = '\0';
        }
    }
}
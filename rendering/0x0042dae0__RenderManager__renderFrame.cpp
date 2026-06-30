// FUNC_NAME: RenderManager::renderFrame
void __thiscall RenderManager::renderFrame(void)
{
    uint flags = 0;                                 // uStack00000004
    // Set the render target from the current context (e.g. a framebuffer/texture)
    this->setRenderTarget(*(RenderTarget**)(this + 0x39f8)); // +0x39f8: pointer to render target

    // Check if current thread is the main game thread via TEB/PEB (offset 0x34 in PEB: is being debugged?)
    bool isMainThread = (*(int*)(*(int**)__readfsdword(0x2c) + 0x34) == 0);
    int clearColor;
    if ((&g_ThreadCheck)[isMainThread] == 0)         // g_ThreadCheck[0] or g_ThreadCheck[1]
    {
        clearColor = 1;                              // Default clear color
        if (*(int*)(this + 0x39f8) != 1)            // If render target is not 1 (backbuffer?)
            clearColor = g_ClearColor;               // Global clear color (DAT_0110abf4)
    }
    else
    {
        clearColor = g_ClearColor;
    }

    // Clamp viewport dimensions to minimum 14
    if (g_MinWidth < 14)
        g_MinWidth = 14;
    if (g_MaxWidth > 14)
        g_MaxWidth = 14;

    g_RenderLock = 0;                                // Unlock rendering (DAT_011f3a10)
    this->beginScene(g_ScreenResolutionX, g_ScreenResolutionY); // FUN_0041e660: begin rendering / set state

    // Main render call: pass clear color, flags (0x100 = e.g. clear depth?), viewport, etc.
    this->render(this, clearColor, flags | 0x100, this + 0x1f70, 0, 0); // +0x1f70: viewport structure

    // Clamp again (probably redundant)
    if (g_MinWidth < 14)
        g_MinWidth = 14;
    if (g_MaxWidth > 14)
        g_MaxWidth = 14;

    g_RenderLock = 1;                                // Re-lock rendering
    this->endScene(0, 0);
    return;
}
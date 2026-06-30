// FUNC_NAME: VideoManager::enforceResolutionConstraints
void VideoManager::enforceResolutionConstraints(void)
{
    // Call virtual function at vtable index 75 (offset 300)
    // This likely applies or validates a video mode configuration
    (*(void (__thiscall **)(VideoManager *, void *))(*this + 300))(this, &gDefaultVideoConfig);

    // Enforce minimum width (0xAE = 174)
    if (gCurrentWidth < 0xAE) {
        gCurrentWidth = 0xAE;
    }

    // Clear fullscreen flag (or some mode flag)
    gFullscreenFlag = 0;

    // Enforce maximum height (0xAE = 174)
    if (0xAE < gCurrentHeight) {
        gCurrentHeight = 0xAE;
    }
}
// FUNC_NAME: VideoSystem::setScreenMode
void __thiscall VideoSystem::setScreenMode(void) {
    // Get pointer to singleton/global video device object (likely from a manager)
    // FUN_009c8f80 returns a pointer to an object with vtable
    int *pVideoDevice = (int *)FUN_009c8f80();

    // Parameters for screen mode: mode=2, depth=16, flags=0 (e.g., fullscreen?)
    struct ScreenModeParams {
        int mode;       // +0x00: rendering mode (2 = maybe windowed? 1=fullscreen?)
        int depth;      // +0x04: color depth (0x10 = 16-bit)
        int flags;      // +0x08: flags (0 = default)
    } params;
    params.mode = 2;
    params.depth = 0x10;
    params.flags = 0;

    // Call the first virtual method on the video device (vtable index 0)
    // This likely sets the display mode / resolution
    (**(void (__thiscall **)(int, ScreenModeParams *))*pVideoDevice)((int)this, &params);
}
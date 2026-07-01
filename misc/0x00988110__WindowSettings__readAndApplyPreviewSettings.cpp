// FUNC_NAME: WindowSettings::readAndApplyPreviewSettings
// Address: 0x00988110
// Role: Reads new window settings from config, applies them temporarily, then restores old values; sets a flag indicating preview state.

void __fastcall WindowSettings::readAndApplyPreviewSettings(int thisPtr)
{
    // Save current settings
    int savedFullScreen = *(int *)(thisPtr + 0x70);    // +0x70: bool isFullScreen? (stored as int)
    int savedRefreshHz   = *(int *)(thisPtr + 0x78);    // +0x78: maybe refresh rate hz? (stored as int)
    int savedHeight      = *(int *)(thisPtr + 0x110);   // +0x110: window height
    int savedHz          = *(int *)(thisPtr + 0x118);   // +0x118: vertical refresh hz
    int savedWidth       = *(int *)(thisPtr + 0x114);   // +0x114: window width

    // Read new settings from config (likely global config manager)
    int newWidth  = ConfigManager::getInt("Window.Width",  1024); // 0x400 = 1024
    int newHeight = ConfigManager::getInt("Window.Height", 768);  // 0x300 = 768
    int newHz     = ConfigManager::getInt("Window.Hz",     60);   // 0x3c = 60
    bool newFullScreen = ConfigManager::getBool("Window.FullScreen", true); // default true

    // Apply new settings (store temporarily)
    *(int *)(thisPtr + 0x114) = newWidth;
    *(int *)(thisPtr + 0x110) = newHeight;
    *(int *)(thisPtr + 0x118) = newHz;
    *(int *)(thisPtr + 0x70)  = (newFullScreen ? 0 : 1); // note: stored as inverted (0 = fullscreen? depends on logic)
    *(int *)(thisPtr + 0x78)  = *(int *)(0x01129938 + 0x44); // some global value, likely refresh rate or monitor index

    // Call function to apply the new settings (e.g., to the rendering window)
    WindowSettings::applySettings(); // FUN_00986d10

    // Restore the saved settings (revert preview)
    *(int *)(thisPtr + 0x114) = savedWidth;
    *(int *)(thisPtr + 0x110) = savedHeight;
    *(int *)(thisPtr + 0x118) = savedHz;
    *(int *)(thisPtr + 0x70)  = savedFullScreen;
    *(int *)(thisPtr + 0x78)  = savedRefreshHz;

    // Mark preview as done
    *(char *)(thisPtr + 0x10d) = 1; // +0x10d: previewApplied flag
}
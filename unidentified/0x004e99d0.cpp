// FUN_004e99d0: VideoManager::applySettings
int __thiscall VideoManager::applySettings(int *settings)
{
    // settings[0] = device mode handle (passed to setDeviceHandle)
    // settings[1] = requested width (stored in DAT_010c2658)
    // settings[2] = requested height (stored in DAT_011947e4)
    g_requestedWidth = settings[1];   // DAT_010c2658
    g_requestedHeight = settings[2];  // DAT_011947e4
    setDeviceHandle(settings[0]);     // FUN_004e27a0
    setVSync(1);                      // FUN_0051f540
    commitSettings();                 // FUN_004e2870
    g_requestedWidth = -1;            // reset after commit
    g_requestedHeight = 0;            // reset after commit
    return 1;
}
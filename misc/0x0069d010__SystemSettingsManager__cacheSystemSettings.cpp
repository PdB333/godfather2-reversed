// FUNC_NAME: SystemSettingsManager::cacheSystemSettings
void SystemSettingsManager::cacheSystemSettings(void)
{
    // SPI_GETKEYBOARDSPEED (0x0A = 10) -> store keyboard repeat speed
    SystemParametersInfoA(SPI_GETKEYBOARDSPEED, 0, &g_keyboardSpeed, 0);

    // SPI_GETMOUSEHOVERWIDTH (0x3A = 58) -> store mouse hover width (buffer size 8? maybe unused)
    SystemParametersInfoA(SPI_GETMOUSEHOVERWIDTH, 8, &g_mouseHoverWidth, 0);

    // SPI_GETMOUSEHOVERHEIGHT (0x34 = 52) -> store mouse hover height (buffer size 8)
    // Note: 0x34 is not standard; likely a custom or alternative SPI constant for mouse hover height
    SystemParametersInfoA(0x34, 8, &g_mouseHoverHeight, 0);

    // SPI_GETMOUSEHOVERTIME (0x32 = 50) -> store mouse hover time (buffer size 0x18)
    // Again non-standard value; likely the game maps its own constants
    SystemParametersInfoA(0x32, 0x18, &g_mouseHoverTime, 0);

    // SPI_GETSCREENSAVETIMEOUT (0x0E = 14) -> store screen saver timeout
    SystemParametersInfoA(SPI_GETSCREENSAVETIMEOUT, 0, &g_screenSaverTimeout, 0);
}
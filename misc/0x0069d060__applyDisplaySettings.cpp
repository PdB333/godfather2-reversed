// FUNC_NAME: applyDisplaySettings
void applyDisplaySettings(void)
{
    UINT uiDragFullWindows = DAT_01129fb4;   // global: whether to enable full window drag
    int iModeCheck = FUN_006a17c0();         // check if exclusive/fullscreen mode
    if (iModeCheck == 0)
    {
        // Enable or disable full window dragging based on stored setting
        SystemParametersInfoA(SPI_SETDRAGFULLWINDOWS, uiDragFullWindows, nullptr, SPIF_UPDATEINIFILE);
    }
    // Set mouse hover width to 8 pixels
    SystemParametersInfoA(SPI_SETMOUSEHOVERWIDTH, 8, &DAT_00e50b44, 0);
    // Set mouse hover height to 8 pixels
    SystemParametersInfoA(SPI_SETMOUSEHOVERHEIGHT, 8, &DAT_00e50b4c, 0);
    // Set mouse hover time to 24 ms
    SystemParametersInfoA(SPI_SETMOUSEHOVERTIME, 0x18, &DAT_00e50b54, 0);
    // Activate or deactivate screen saver based on stored setting
    SystemParametersInfoA(SPI_SETSCREENSAVEACTIVE, DAT_01129fb8, nullptr, 0);
    return;
}
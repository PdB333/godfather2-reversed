// FUNC_NAME: System::readUIParameters
void readUIParameters(void)
{
    // Retrieve system parameters for UI settings (icon title wrap, non-client metrics, menu drop alignment, show sounds, icon title font)
    SystemParametersInfoA(10, 0, &g_iconTitleWrap, 0);                  // SPI_GETICONTITLEWRAP
    SystemParametersInfoA(0x3a, 8, &g_nonClientMetrics, 0);            // SPI_GETNONCLIENTMETRICS? (size 8 bytes)
    SystemParametersInfoA(0x34, 8, &g_menuDropAlignment, 0);           // SPI_GETMENUDROPALIGNMENT? (size 8 bytes)
    SystemParametersInfoA(0x32, 24, &g_showSounds, 0);                 // SPI_GETSHOWSOUNDS? (size 24 bytes)
    SystemParametersInfoA(0x0e, 0, &g_iconTitleLogFont, 0);            // SPI_GETICONTITLELOGFONT? (size 0? probably variable)
    return;
}
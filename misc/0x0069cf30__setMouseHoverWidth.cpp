// FUNC_NAME: setMouseHoverWidth
void setMouseHoverWidth(void)
{
    uint32_t mouseHoverWidth = g_mouseHoverWidth; // DAT_00e50b44
    if ((g_mouseSettingsFlags & 1) == 0) { // DAT_00e50b48 bit 0
        g_mouseSettingsFlags = g_mouseSettingsFlags & 0xfffffff3; // Clear bits 0 and 1
        SystemParametersInfoA(0x3b, 8, &mouseHoverWidth, 0); // SPI_SETMOUSEHOVERWIDTH
    }
}
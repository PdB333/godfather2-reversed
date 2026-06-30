// FUNC_NAME: setDragFullWindowsState

void setDragFullWindowsState(void)
{
    BOOL dragFullWindowEnabled = *(BOOL *)0x00e50b44; // Global: current drag full window state
    uint flags = *(uint *)0x00e50b48; // Global: flags controlling drag settings

    // Only apply if bit 0 is clear (not already applied or locked)
    if ((flags & 1) == 0)
    {
        // Compute potential new flags (bits 2 and 3 cleared) – not stored back, possibly debug or dead code
        uint local_4 = flags & 0xfffffff3;

        // Set system parameter: SPI_SETDRAGFULLWINDOWS (0x3b)
        // uiParam = 8 (unusual, maybe structure size?), pvParam = pointer to BOOL value
        SystemParametersInfoA(0x3b, 8, &dragFullWindowEnabled, 0);
    }
    return;
}
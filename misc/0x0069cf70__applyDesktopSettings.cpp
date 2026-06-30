// FUNC_NAME: applyDesktopSettings
// Function address: 0x0069cf70
// Role: Sets a desktop system parameter if not already applied, using a stored value. Updates a flag to prevent repeated calls.

void applyDesktopSettings(void)
{
    // Global variables storing desktop settings and flags
    // +0x00: DAT_00e50b4c - likely a buffer (e.g., wallpaper path or color value)
    // +0x00: DAT_00e50b50 - status flags (bit 0 indicates already applied? bits 2-3 cleared after call)
    undefined4 desktopParam = DAT_00e50b4c;
    uint statusFlags = DAT_00e50b50;

    // Check if the setting has already been applied (bit 0 is clear means not applied)
    if ((statusFlags & 1) == 0)
    {
        // Clear bits 2 and 3 to mark the operation as done
        statusFlags = statusFlags & 0xfffffff3;
        DAT_00e50b50 = statusFlags; // store updated flags

        // Call Windows API to set a system parameter (UI action 0x3b, likely SPI_SETDESKWALLPAPER or similar)
        SystemParametersInfoA(0x3b, 8, &desktopParam, 0);
    }
}
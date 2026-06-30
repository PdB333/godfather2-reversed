// FUNC_NAME: DisplaySettings::restoreSystemSettings

// Address: 0x0069d0c0
// Restores system display and input settings that were modified by the game.

#include <windows.h>

// Global variables storing original system settings
static DWORD g_originalMouseHoverWidth = 0;       // DAT_00e50b44
static DWORD g_originalMouseHoverFlags = 0;       // DAT_00e50b48
static DWORD g_originalScreenSaverTimeout = 0;    // DAT_00e50b4c
static DWORD g_originalScreenSaverFlags = 0;      // DAT_00e50b50

// Forward declaration of helper
bool isGameInForeground(void); // FUN_006a17c0

void restoreSystemSettings(void)
{
    // Check if game is in foreground; if not, disable screen saver? (0xB = SPI_SETSCREENSAVEACTIVE? Actually unclear)
    if (!isGameInForeground()) {
        SystemParametersInfoA(0xB, 0, (PVOID)0x0, 1); // Set some system parameter
    }

    // Restore mouse hover width (0x3B = SPI_SETMOUSEHOVERWIDTH)
    DWORD hoverWidth = g_originalMouseHoverWidth;
    if ((g_originalMouseHoverFlags & 1) == 0) {
        DWORD flags = g_originalMouseHoverFlags & 0xFFFFFFF3; // unused, possibly artifact
        SystemParametersInfoA(0x3B, 8, &hoverWidth, 0); // uParam = 8 might be incorrect; see comment
    }

    // Restore screen saver timeout (0x3B again? likely a copy-paste error, but following original)
    DWORD timeout = g_originalScreenSaverTimeout;
    if ((g_originalScreenSaverFlags & 1) == 0) {
        DWORD flags = g_originalScreenSaverFlags & 0xFFFFFFF3; // unused
        SystemParametersInfoA(0x3B, 8, &timeout, 0);
    }

    // Additional restore (likely screen saver timeout set to 0)
    FUN_0069cfb0(); // Unknown helper – possibly restore display resolution
    SystemParametersInfoA(0xF, 0, (PVOID)0x0, 0); // SPI_SETSCREENSAVETIMEOUT = 0xF, disable screen saver
}
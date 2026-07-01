// Xbox PDB: EARS_Apt_UICommunityMenu_HandleLeftShoulder
// FUNC_NAME: GameHUD::changeDisplayMode
// Address: 0x0091dd10
// Handles HUD display mode transitions based on a state field at +0xB8.
// Calls various UI management functions to switch between combat, overall, game modes, and specialty screens.
void __thiscall GameHUD::changeDisplayMode(void)
{
    char *screenName;

    switch (*(int *)((char *)this + 0xB8)) // Current display mode ID
    {
    case 1:
        // Reset mode: clear global flags and internal state
        setGlobalFlag(&DAT_01130448, 0); // Some global flag
        *(int *)((char *)this + 0xC0) = 0; // Internal mode sub-state
        *(int *)((char *)this + 0xB4) = 0; // Another field (maybe previous mode)
        resetHUDState(); // FUN_0091aa40
        return;

    case 10:
    case 11:
    case 12:
        // Combat display
        setGlobalFlag(&DAT_01130208, 0);
        setHUDSubMode(25); // 0x19
        screenName = "ShowCombat";
        break;

    case 13:
    case 14:
    case 15:
    case 16:
    case 17:
        // Overall display
        setGlobalFlag(&DAT_01130208, 0);
        setHUDSubMode(10);
        screenName = "ShowOverall";
        break;

    case 0x12:
    case 0x13:
    case 0x14:
    case 0x15:
    case 0x16:
    case 0x17:
    case 0x18:
        // Game modes display
        setGlobalFlag(&DAT_01130208, 0);
        setHUDSubMode(13); // 0xd
        screenName = "ShowGameModes";
        break;

    case 0x19:
        // Specialty display
        setGlobalFlag(&DAT_01130208, 0);
        setHUDSubMode(18); // 0x12
        screenName = "ShowSpecialty";
        break;

    default:
        // No action for other cases
        goto skipShow;
    }

    // Show the specified screen (likely posts a UI event or sets a new screen)
    showUIScreen(screenName, 0, &DAT_00d8510c, 0);
    setUIFocus(1, 0); // Enable input focus

skipShow:
    return;
}
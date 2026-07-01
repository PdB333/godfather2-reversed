// Xbox PDB: EARS_Apt_UICommunityMenu_HandleRightShoulder
// FUNC_NAME: UIMenuManager::handleMenuSwitch
void __thiscall UIMenuManager::handleMenuSwitch(void)
{
    const char* nextScreenName;
    
    // Switch on current screen ID at offset 0xB8
    // Screen IDs: 0xA-0xC = game modes, 0xD-0x11 = specialty, 0x12-0x18 = combat, 0x19 = overall
    switch (*(int*)(this + 0xB8))
    {
        case 10:   // Screen: Game Modes (first)
        case 11:
        case 12:
        {
            // Transition to Overall screen? (0x0A?)
            // Note: Reset some global flag (DAT_01130208) to 0
            FUN_00402050(&DAT_01130208, 0);   // Clear menu state
            FUN_00918110(0x0D);              // Set next screen to 13 (Specialty first?)
            nextScreenName = "ShowGameModes";
            break;
        }
        case 13:   // Screen: Specialty (first)
        case 14:
        case 15:
        case 16:
        case 17:
        case 18:
        case 19:
        case 20:
        case 21:
        {
            FUN_00402050(&DAT_01130208, 0);
            FUN_00918110(0x12);             // Set next screen to 18 (Combat first?)
            nextScreenName = "ShowSpecialty";
            break;
        }
        case 22:   // Screen: Combat (first)
        case 23:
        case 24:
        case 25:
        case 26:
        case 27:
        case 28:
        {
            FUN_00402050(&DAT_01130208, 0);
            FUN_00918110(0x19);             // Set next screen to 25 (Overall first?)
            nextScreenName = "ShowCombat";
            break;
        }
        case 29:   // Screen: Overall
        {
            FUN_00402050(&DAT_01130208, 0);
            FUN_00918110(10);               // Set next screen to 10 (Game Modes first?)
            nextScreenName = "ShowOverall";
            break;
        }
        default:
        {
            goto switchD_0091e12c_default;
        }
    }
    
    // Trigger the screen transition
    FUN_005a04a0(nextScreenName, 0, &DAT_00d8510c, 0);   // Show screen by name
    FUN_0091cd80(1, 0);                                   // Update UI flags
    
switchD_0091e12c_default:
    return;
}
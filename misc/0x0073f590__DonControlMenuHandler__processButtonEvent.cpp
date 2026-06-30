// FUNC_NAME: DonControlMenuHandler::processButtonEvent
// Address: 0x0073f590
// Handles input button events for the Don Control menu (up, down, select, cancel, etc.)
// Uses internal state at +0x50 (m_selectedIndex), +0x54 (m_previousIndex), +0x58 (m_pOwner)
// The owner pointer points to a field inside a Player object (sub 0x48 to get Player base).

char __thiscall DonControlMenuHandler::processButtonEvent(int param_2, int param_3, int param_4, int buttonId, int param_6) {
    char ret = 1;
    int playerObj;
    int buttonCase = buttonId - 10; // Normalize button IDs (10-15 map to 0-5)

    switch (buttonCase) {
    case 0: // DPAD_UP or similar
        // Save previous selection and update selected index
        if (*(int*)(this + 0x58) == 0) {
            playerObj = 0;
        } else {
            playerObj = *(int*)(this + 0x58) - 0x48; // Get Player base from member pointer
        }
        // Play generic sound (maybe UI tick)
        FUN_00481620();
        *(int*)(playerObj + 0x2580) = *(int*)(this + 0x50); // Store selected index in Player
        *(int*)(this + 0x54) = *(int*)(this + 0x50); // Save as previous

        int newSelection = FUN_0077dd80(); // Get new selection (maybe cycle)
        *(int*)(this + 0x50) = newSelection;
        if (*(int*)(this + 0x54) < newSelection) {
            int soundArray[4] = {0, 0xB16CDAA, 0x5FFC8021, 0xA96C264A}; // Sound IDs
            int unk1 = 0;
            int context = FUN_006fbc40(0, 0); // Audio context
            FUN_007f96a0(soundArray[*(int*)(this + 0x50)], 0, context, unk1); // Play sound
            FUN_006fbc70(); // Release audio context
        }

        int state = FUN_00806440(); // Get current menu state (2 = normal, 3 = submode?)
        if (state == 2) {
            if (*(int*)(this + 0x50) == 3) {
                FUN_00737940(0, 0); // Show/hide something
                if (*(int*)(this + 0x58) != 0) {
                    FUN_007f63e0(0x31); // Play sound (select)
                    return 1;
                }
                // Fall through to sound play
                goto playSelectSound;
            }
            // Check compatibility with menu state
            char isCompatible = FUN_00730210();
            if (isCompatible == 0) {
                // Not compatible, check flag
                if (*(int*)(this + 0x58) == 0) {
                    playerObj = 0;
                } else {
                    playerObj = *(int*)(this + 0x58) - 0x48;
                }
                if (((*(uint*)(playerObj + 0x1F98) >> 4) & 1) == 0) {
                    // Flag not set, do nothing
                    int showParam = 0;
                    // Fall through to show
                    goto showUI;
                }
                // Flag set, show with parameter 4
                if (*(int*)(this + 0x58) == 0) {
                    int showParam = 4;
                } else {
                    int showParam = 4;
                }
            } else {
                // Compatible, check another flag
                if (*(int*)(this + 0x58) == 0) {
                    playerObj = 0;
                } else {
                    playerObj = *(int*)(this + 0x58) - 0x48;
                }
                char flag = FUN_00898330(playerObj, 2);
                if (flag == 0) {
                    // Flag not set, same as incompatible path
                    goto checkIncompatible;
                }
                // Flag set, do nothing
                int showParam = 0;
            }
showUI:
            FUN_00737940(showParam, 0); // Show UI with parameter
            if (*(int*)(this + 0x58) != 0) {
                FUN_007f6420(0x31); // Play sound (different variant)
                return 1;
            }
            FUN_007f6420(0x31);
            return 1;
        } else if (state == 3) {
            // Submode state
            if (*(int*)(this + 0x58) == 0) {
                playerObj = 0;
            } else {
                playerObj = *(int*)(this + 0x58) - 0x48;
            }
            if (*(int*)(playerObj + 0x1ED4) == 0x637B907) { // Some special value
                return 1;
            }
            if (*(int*)(this + 0x58) == 0) {
                playerObj = 0;
            } else {
                playerObj = *(int*)(this + 0x58) - 0x48;
            }
            if ((*(uint*)(playerObj + 0x1F98) & 0xE2E) != 0) {
                return 1;
            }
            int pOwner = *(int*)(this + 0x58);
            if (*(int*)(this + 0x50) == 3) {
                if (pOwner != 0) {
                    FUN_007f63e0(0x31);
                    return 1;
                }
                // Fall through to play select sound
                goto playSelectSound;
            }
            // Not selected=3, go to common path
            goto handleUpCommon;
        }
        // For other states, do nothing special
        break;

    case 1: // DPAD_DOWN
        FUN_0073ede0(); // Handle down selection
        return 1;

    case 2: // DPAD_LEFT or RIGHT?
        FUN_0073f060(); // Handle horizontal movement
        return 1;

    case 3: // SELECT (A button)
        if ((*(int*)(this + 0x54) == 1) && (*(int*)(this + 0x50) == 0)) {
            // Special case: exit back to previous menu
            FUN_0071d610(); // Play cancel sound or transition
            if (*(int*)(this + 0x58) == 0) {
                playerObj = 0;
            } else {
                playerObj = *(int*)(this + 0x58) - 0x48;
            }
            FUN_006bea40(playerObj); // Reset player state
            FUN_009aeca0(); // Return to game
            return 1;
        }
        // Default select handling (if state doesn't match, break to default)
        break;

    case 4: // CANCEL (B button)
        if (*(int*)(this + 0x58) != 0) {
            FUN_007ff050(1); // Cancel with parameter 1
            return 1;
        }
        FUN_007ff050(1);
        return 1;

    case 5: // CONFIRM (Y button or start?)
        FUN_0073f0d0(); // Handle confirm action
        return 1;

    default:
        ret = FUN_004ac700(param_2, param_3, param_4, buttonId, param_6); // Default handler (base class?)
    }

    return ret;

playSelectSound:
    FUN_007f63e0(0x31);
    return 1;

handleUpCommon:
    if (pOwner != 0) {
        FUN_007f6420(0x31);
        return 1;
    }
    FUN_007f6420(0x31);
    return 1;

checkIncompatible:
    if (*(int*)(this + 0x58) == 0) {
        playerObj = 0;
    } else {
        playerObj = *(int*)(this + 0x58) - 0x48;
    }
    if (((*(uint*)(playerObj + 0x1F98) >> 4) & 1) == 0) {
        goto showUIwith0;
    }
    int showParam = 4;
    goto showUI;
showUIwith0:
    showParam = 0;
    goto showUI;
}
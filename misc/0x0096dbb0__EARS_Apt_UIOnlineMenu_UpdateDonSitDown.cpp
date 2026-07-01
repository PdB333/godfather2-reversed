// Xbox PDB: EARS_Apt_UIOnlineMenu_UpdateDonSitDown
// FUNC_NAME: GodfatherGameManager::processReadyStateInput

// This function processes input related to ready state management in the game.
// It handles host/client ready state changes and selection highlighting.

bool __fastcall GodfatherGameManager::processReadyStateInput(int thisPtr)
{
    int backupSelection;
    bool result = false;

    // Check if the host ready state flag is set (bit 9 of flags at +0x6f4)
    if ((*(uint *)(thisPtr + 0x6f4) >> 9 & 1) != 0) {
        char* stateStr = "true";
        char* stateFunc = nullptr;

        // Determine if we're setting host or client ready state
        if (*(char *)(thisPtr + 0x220) == '\0') {
            // Client (not host)
            if (*(char *)(thisPtr + 0x6f1) == '\0') {
                stateStr = "false";
            }
            stateFunc = "SetClientReadyState";
        } else {
            // Host
            if (*(char *)(thisPtr + 0x6f1) == '\0') {
                stateStr = "false";
            }
            stateFunc = "SetHostReadyState";
        }

        // Call the Lua function to set the ready state
        FUN_005a04a0(stateFunc, 0, &DAT_00d8cdec, 1, stateStr);
        
        // Clear the host ready state flag (bit 9)
        *(uint *)(thisPtr + 0x6f4) = *(uint *)(thisPtr + 0x6f4) & 0xfffffdff;
    }

    // Only process selection changes if we're the host
    if (*(char *)(thisPtr + 0x220) == '\0') {
        return false;
    }

    // Check if selection changed flag is set (bit 5 at +0x6f4)
    if ((*(uint *)(thisPtr + 0x6f4) >> 5 & 1) != 0) {
        backupSelection = *(int *)(thisPtr + 0xc4);
        
        // Update selection to current item
        *(int *)(thisPtr + 0xc4) = *(int *)(thisPtr + 0xc0);
        
        // Unhighlight the previously selected item
        FUN_005a04a0("UnHighlightSelected", 0, &DAT_00d8cdec, 0);
        
        // Restore and check if we switched to the first item
        *(int *)(thisPtr + 0xc4) = backupSelection;
        if (backupSelection == 1) {
            FUN_0096c920(); // Probably reset scroll position
        }
        
        // Update the display for the new selection
        FUN_0095fbc0(*(int *)(thisPtr + 0xc4) + *(int *)(thisPtr + 0xd4),   // Current index + offset
                     *(int *)(thisPtr + 0xc8),                                // Something at +0xc8
                     *(int *)(thisPtr + 0xcc));                              // Something at +0xcc
        
        // Update and highlight the new selection
        FUN_005a04a0("UpdateSelectItem", 0, &DAT_00d8cdec, 0);
        FUN_005a04a0("HighlightSelected", 0, &DAT_00d8cdec, 0);
        
        // Refresh display for the new selected item
        FUN_0095e7d0(*(int *)(thisPtr + 0xc4) + *(int *)(thisPtr + 0xd4));
        
        // Check if auto-ready flag is set (bit 10 at +0x6f4)
        if ((*(uint *)(thisPtr + 0x6f4) >> 10 & 1) != 0) {
            // Reset ready states
            *(char *)(thisPtr + 0x6f1) = 0;
            *(char *)(thisPtr + 0x6f0) = 0;
            FUN_005a04a0("SetReadyState", 0, &DAT_00d8cdec, 0);
            
            // Clear the auto-ready flag
            *(uint *)(thisPtr + 0x6f4) = *(uint *)(thisPtr + 0x6f4) & 0xfffffbff;
        }
        
        // Clear the selection changed flag
        *(uint *)(thisPtr + 0x6f4) = *(uint *)(thisPtr + 0x6f4) & 0xffffffdf;
    }

    // Check if history push flag is set (bit 6 at +0x6f4)
    if ((*(uint *)(thisPtr + 0x6f4) >> 6 & 1) != 0) {
        FUN_005a04a0("PushHistory", 0, &DAT_00d8cdec, 0);
        FUN_0096cd00(); // Probably navigates to previous screen
        
        // Set the history flag (bit 2)
        *(uint *)(thisPtr + 0x6f4) = *(uint *)(thisPtr + 0x6f4) | 4;
        result = true;
        
        // Reset ready states
        *(char *)(thisPtr + 0x6f1) = 0;
        *(char *)(thisPtr + 0x6f0) = 0;
        
        // Reset host and client ready states to false
        FUN_005a04a0("SetHostReadyState", 0, &DAT_00d8cdec, 1, "false");
        FUN_005a04a0("SetClientReadyState", 0, &DAT_00d8cdec, 1, "false");
        
        // Clear the history push flag
        *(uint *)(thisPtr + 0x6f4) = *(uint *)(thisPtr + 0x6f4) & 0xffffffbf;
    }

    return result;
}
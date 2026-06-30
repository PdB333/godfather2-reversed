// FUNC_NAME: UIManager::processCommand
void __thiscall UIManager::processCommand(CommandMessage* msg) {
    // msg->dword3 is used as a pointer + 0x48; subtract 0x48 to get base pointer
    Player* player = (Player*)(msg->dword3 ? (char*)msg->dword3 - 0x48 : 0);
    Player* playerArg1 = (Player*)(msg->dword1 ? (char*)msg->dword1 - 0x48 : 0);

    // Guard: dword3 must not be 0 or 0x48 (meaning player pointer invalid)
    if (msg->dword3 == 0 || msg->dword3 == 0x48) {
        return;
    }

    switch (msg->commandId) {
    case 3: case 4: case 5: case 6: case 7: case 8: case 9: case 10:
    case 0xb: case 0xc: case 0xd: case 0xe: case 0xf: case 0x10:
    case 0x11: case 0x12: case 0x13: case 0x14: case 0x15: case 0x16:
    case 0x17: case 0x18: case 0x19: case 0x1a: case 0x1b: case 0x1c:
    case 0x1d: case 0x1e: case 0x1f: case 0x20: case 0x21: case 0x22:
    case 0x25: case 0x26: case 0x2b: case 0x2c: case 0x2d:
        // No operation for these commands
        break;

    case 0x23: {
        // Command: initialise some player UI element
        enterCriticalSection((int)player + 0x1FC0); // player->dialogMutex
        unlockPlayer(player); // FUN_006f7ef0

        int* resource = nullptr;
        getSomeResource(&resource); // FUN_006f8940

        // If 'this' is valid, offset by 4 to get UITextManager pointer
        UIManager* uiMgr = (UIManager*)(this ? (char*)this + 4 : 0);
        setUIText(&g_uiTextLabel, uiMgr, 0); // FUN_00408c70

        if (resource) {
            releaseResource(resource); // FUN_004daf90
            return;
        }
        break;
    }

    case 0x24: {
        // Command: check if player has a certain flag and hide UI
        enterCriticalSection((int)player + 0x1FD0);
        if (player && (*(uint*)(*(int*)((int)player + 0x2124) + 0x20) >> 7 & 1) != 0) {
            hideSomeUI(0); // FUN_0071ed70
            setUIEnabled(&g_uiSomething, 0); // FUN_00402050
            return;
        }
        break;
    }

    case 0x27: {
        // Command: similar to 0x24 but also check game state
        enterCriticalSection((int)player + 0x1FC8);
        if (player && (*(uint*)(*(int*)((int)player + 0x2124) + 0x20) >> 7 & 1) != 0) {
            hideSomeUI(0);
            setUIEnabled(&g_uiSomething, 0);
        }
        if (getGameState() == 2) { // FUN_00806440
            requestGameStateChange(); // FUN_007856e0
            return;
        }
        break;
    }

    case 0x28: {
        // Command: play dialog sound for a player, set UI text
        stopSound(0, -1); // FUN_006ada80
        playDialogSound(playerArg1, 0xF4846C64); // FUN_0044b210

        // Set up UI string
        uint32_t localBuf[4]; // +0x00: local_30, +0x04: local_2c, +0x08: local_28, +0x0C: local_24
        int* uiPtr = g_uiTextPtr; // DAT_0112ad8c
        localBuf[1] = (uint32_t)localBuf; // local_2c points to local_24
        localBuf[2] = 0; // local_28

        int textOffset = player ? ((int)player + 0x3C) : 0; // player->dialogTextId
        setUIString((UIString*)uiPtr, textOffset, 0); // FUN_00408bf0

        enablePlayerDialog(playerArg1, 1); // FUN_00717730
        refreshUI(); // FUN_006ad490
        return;
    }

    case 0x29: {
        // Command: similar to 0x28 with different sound hash
        stopSound(0, -1);
        playDialogSound(playerArg1, 0x59BA7978);
        // Falls through to common LAB (shared with case 0x2a)
        goto commonDialogFlow;
    }

    case 0x2a: {
        // Command: set flag on player and play sound
        if (player) {
            *(uint*)((int)player + 0x1F58) |= 1; // set player->dialogFlag
        }
        stopSound(0, -1);
        playDialogSound(playerArg1, 0xEFF2C39E);
commonDialogFlow:
        // Same as case 0x28's flow after sound
        uint32_t localBuf[4];
        int* uiPtr = g_uiTextPtr;
        localBuf[1] = (uint32_t)localBuf;
        localBuf[2] = 0;
        int textOffset = player ? ((int)player + 0x3C) : 0;
        setUIString((UIString*)uiPtr, textOffset, 0);
        enablePlayerDialog(playerArg1, 1);
        refreshUI();
        break;
    }

    case 0x2e: {
        // Command: open menu (e.g., pause or ending)
        openMenu(); // FUN_00733ec0
        return;
    }

    default:
        // Unknown command ID, just return
        break;
    }
}
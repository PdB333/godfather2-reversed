// FUNC_NAME: InputSystem::getInputModeFlags
uint InputSystem::getInputModeFlags(void* unusedThis, Player* player)
{
    uint flags = 0x80; // Always set? Possibly "active" flag
    bool inGame = FUN_00481620();
    if (inGame) {
        bool inMenu = FUN_0089c630();
        if (!inMenu) {
            flags = 0x81; // Not in game+menu -> set bit 0
        }
        // else: stays 0x80 (both true)
    } else {
        flags = 0x81; // Not in game -> set bit 0
    }

    bool paused = FUN_00481660();
    if (!paused) {
        flags |= 0x100; // Not paused -> set bit 8
    }

    if ((player != nullptr) && ((player->flags & 0x01) != 0)) { // +0xAC is a flags byte (bit 0 = special state)
        flags |= 0x1000; // Set bit 12 for player-specific condition (e.g., dead/in car)
    }

    return flags;
}
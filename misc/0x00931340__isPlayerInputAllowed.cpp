// FUNC_NAME: isPlayerInputAllowed
bool isPlayerInputAllowed(void) {
    bool result = false;

    // g_globalFlags is a bitfield (address 0x01130590), bit 6 indicates cutscene or blocking state
    // g_someObject is a pointer to a manager object (address 0x01129928), byte at offset 0xb4 indicates active dialog/event
    if (((g_globalFlags >> 6) & 1) != 0 && *(char*)(g_someObject + 0xb4) != '\0') {
        return false;  // blocked by cutscene and script event
    }

    // g_gameMode is an integer game state identifier (address 0x01130548)
    switch (g_gameMode) {
        case 0xC:   // likely combat mode
        case 0xD:
        case 0xE:
        case 0xF:
        case 0x17:  // 23 - likely action mode
        case 0x18:  // 24
        case 0x1C:  // 28 - player-in-combat sub-mode
        case 0x1D:  // 29
            result = true;
            break;
    }

    return result;
}
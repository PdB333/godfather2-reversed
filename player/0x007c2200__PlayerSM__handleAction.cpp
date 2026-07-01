// FUNC_NAME: PlayerSM::handleAction
// Function address: 0x007c2200
// Handles action inputs for the player state machine (e.g., attack, cover toggle)

byte __thiscall PlayerSM::handleAction(int thisPtr, undefined4 param2, undefined4 param3, int actionId) {
    byte result = 0;
    char isAliveFlag;
    uint bitFlag;
    char* coverFlagPtr;

    if (actionId == 0x13) { // Attack action (fire weapon)
        isAliveFlag = Player::isAlive(); // 0x007f47a0 - check if player is alive
        if (isAliveFlag != '\0' && *(int*)(thisPtr + 0x8c) != 0) {
            bitFlag = *(uint*)(*(int*)(thisPtr + 0x8c) + 0x4c) >> 1; // Check bit 0 of a flags field
            result = (byte)bitFlag & 1;
            if ((bitFlag & 1) != 0) {
                isAliveFlag = Player::canFire(); // 0x00481660 - check if weapon can fire
                if (isAliveFlag != '\0') {
                    Player::playAnimation(0x18, 1, 0); // 0x0079fb90 - play fire animation
                }
            }
        }
    } else if (actionId == 0x14) { // Cover toggle action
        isAliveFlag = Player::canToggleCover(); // 0x00481640
        if (isAliveFlag != '\0') {
            coverFlagPtr = (char*)(*(int*)(thisPtr + 0x58) + 0x2224); // Pointer to cover flag (0 = not in cover, 1 = in cover)
            if (*coverFlagPtr == '\0') {
                *coverFlagPtr = '\x01'; // Set cover flag
                result = 1;
            }
        }
    } else {
        // Default action handling (base class)
        result = PlayerSM::handleActionDefault(); // 0x007ab790
    }
    return result;
}
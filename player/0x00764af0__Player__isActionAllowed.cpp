// FUNC_NAME: Player::isActionAllowed
// Address: 0x00764af0
// Role: Determines if a specified action (by type) is allowed for the player, based on game state flags, counters, and delegation.

bool __thiscall Player::isActionAllowed(int arg1, int arg2, int actionType, int arg3) {
    if (actionType == 10) {
        // Check a gameplay flag at offset 0x8e0 in the player data block (pointed by this->+0x50)
        if ((*(uint *)(*(int *)(this + 0x50) + 0x8e0) >> 10) & 1 == 0) {
            return false;
        }
        // Verify game mode or cheat state
        if (checkGameMode() == 0) {
            return false;
        }
        // Read action restriction value at offset 0x24c4
        int restriction = *(int *)(*(int *)(this + 0x50) + 0x24c4);
        if (restriction == 0 || restriction == 0x48) {
            return false;
        }
        return true;
    } else if (actionType == 11) {
        // If a specific pointer (this+0x20) is non-null, check an internal flag
        if (*(int *)(this + 0x20) != 0) {
            int flag = checkFlag(0x6862a74c); // hash of some condition
            return flag == 0;
        }
        return true;
    } else if (actionType == 12) {
        // Action type 12 requires a counter (from external function) to be at least 3
        int counter = getSomeCounter();
        if (counter < 3) {
            return false;
        }
        return true;
    } else {
        // All other action types are delegated to a base method
        return baseCanPerformAction(arg1, arg2, actionType, arg3);
    }
}
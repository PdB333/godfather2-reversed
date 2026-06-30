// FUNC_NAME: PlayerActionManager::isActionBlockedByConflicts
bool __thiscall PlayerActionManager::isActionBlockedByConflicts(int actionId) {
    // global flag for input validation (DAT_012055a3)
    if (g_bInputCheckEnabled && ((1 << (actionId & 0x1f)) & 0x3C0) != 0) {
        // actionId is in the conflicting group {6,7,8,9}
        // Check if any other action in the group is active
        if (actionId != 6 && isActionActive(6)) {
            return true;
        }
        if (actionId != 7 && isActionActive(7)) {
            return true;
        }
        if (actionId != 8 && isActionActive(8)) {
            return true;
        }
        if (actionId != 9 && isActionActive(9)) {
            return true;
        }
    }
    return false;
}
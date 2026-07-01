// FUNC_NAME: PlayerActionableInfo::handleActionQuery
// Address: 0x007d93f0
// Role: Dispatcher for player action queries (canPerformAction checks). 
// Takes an action ID (0x13-0x25) and returns whether the action is allowed.
// Default case delegates to a base handler (FUN_007ab790).

bool __thiscall PlayerActionableInfo::handleActionQuery(int actionId, int arg2, int arg3, int arg5) {
    bool result;
    bool temp;

    switch (actionId - 0x13) {
    case 0: // Action 0x13
        return canPerformAttack(); // FUN_007d8c80
    case 1: // Action 0x14
        if (*(int*)(this + 0x20) == 0) { // +0x20: some flag/pointer
            temp = canPerformInteract(); // FUN_007d8cf0
            if (temp) return true;
        }
        break;
    case 2: // Action 0x15
        return canUseItem(); // FUN_007d8e50
    case 3: // Action 0x16
        return canEnterVehicle(); // FUN_007d9050
    case 4: // Action 0x17
        return canExitVehicle(); // FUN_007d90b0
    case 5: // Action 0x18
        return canTalkToNPC(); // FUN_007d9270
    case 6: // Action 0x19
        return canPickupItem(); // FUN_007d8610
    case 7: // Action 0x1A
        temp = canPerformSpecialAction(); // FUN_007d8b50
        if (temp) return temp;
        temp = isPlayerInCombat(); // FUN_00481640 (global)
        if (!temp) return false;
        if (*(char*)(*(int*)(this + 0x58) + 0x2358) != '\0') // +0x58: pointer to player data, +0x2358: flag
            return false;
        return true;
    case 8: // Action 0x1B
        return !canPerformAction8(); // FUN_007d89f0
    case 9: // Action 0x1C
        return canPerformAction9(); // FUN_007d8d50
    case 10: // Action 0x1D
        return !canPerformAction10(); // FUN_007d8a70
    case 11: // Action 0x1E
        return !canPerformAction11(); // FUN_007d8aa0
    case 12: // Action 0x1F
        return !canPerformAction12(); // FUN_007d9200
    case 13: // Action 0x20
        return !canPerformAction13(); // FUN_007d8af0
    case 14: // Action 0x21
        return !canPerformAction14(); // FUN_007d8b20
    case 15: // Action 0x22
        return isAction15Allowed(); // FUN_007f7c50
    case 16: // Action 0x23
        return checkAchievementFlag(0x2b); // FUN_00690210
    case 17: // Action 0x24
        if (checkAchievementFlag(0x36)) { // FUN_00690210
            clearAchievementFlag(0x36); // FUN_006901e0
            return true;
        }
        break;
    case 18: // Action 0x25
        if (checkAchievementFlag(0x37)) {
            clearAchievementFlag(0x37);
            return true;
        }
        break;
    default:
        return baseHandler(arg2, arg3, actionId, arg5); // FUN_007ab790
    }
    return false;
}
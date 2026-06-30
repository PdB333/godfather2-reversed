// FUNC_NAME: handleControllerAction
bool handleControllerAction(int param1, int param2, int actionCode)
{
    bool conflict = false;
    bool settingA = getConfigBool(0xe); // +0x??: game setting flag
    bool settingB = isCheatActive(0x6eae57f2); // hash for developer mode cheat

    // Special handling for action codes 0x2a (42) and 0x2b (43) (e.g., punch/kick)
    if (actionCode == 0x2a || actionCode == 0x2b) {
        if (!settingA) {
            if (!settingB) goto actionAllowed;
        } else if (settingB) goto conflictCheck;
        conflict = true; // only one flag active -> allow
    }

conflictCheck:
    // Block action if any flag is set and no conflict override
    if ((settingA || settingB) && !conflict) {
        return false;
    }

actionAllowed:
    int actionType;
    if (actionCode == 0x2a) {
        actionType = 1;
    } else if (actionCode == 0x2b) {
        actionType = 2;
    } else if (actionCode == 0x26 || actionCode == 0x29) {
        actionType = 3;
    } else {
        return false; // unknown action code
    }

    // Dispatch to actual action handler
    executeAction(param1, param2, actionType);
    return true;
}
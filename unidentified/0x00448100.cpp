// FUN_NAME: FlagManager::checkAndResetFlag
// This function checks a specific flag (index 0) on the object. 
// If the flag is set, it writes true to outFlag and returns immediately.
// If the flag is not set, it writes false to outFlag and clears the flag (resets it).
// Commonly used to detect one-shot events or state transitions.

void FlagManager::checkAndResetFlag(bool* outFlag) {
    if (isFlagSet(0) != 0) {
        *outFlag = true;
        return;
    }
    *outFlag = false;
    resetFlag(0);
}
// FUNC_NAME: PlayerActionableTargetSM::checkConditionForAction
bool PlayerActionableTargetSM::checkConditionForAction()
{
    // This function likely checks if a particular action or cheat is active
    // using hash IDs for commands.  It also uses a global player pointer (ESI) and
    // possibly a global command system.
    //
    // this+0x100 points to a command system object with a virtual method at +0x10
    // that takes a hash and an output int (e.g., isCommandActive).
    int commandSystem = *(int*)(this + 0x100);
    auto isCommandActive = (char(*)(int, int*))(*(int*)(commandSystem + 0x10));

    int outVal1 = 0;
    char cmd1Result = isCommandActive(0x383225a1, &outVal1);    // first command hash (e.g., "debug_ai")
    if (cmd1Result == '\0' || g_pGlobalPlayer == 0)  // g_pGlobalPlayer is unaff_ESI
    {
        int outVal2;
        char cmd2Result = isCommandActive(0x369ac561, &outVal2); // second command hash (e.g., "god_mode")
        if (cmd2Result != '\0' && g_hashConstantAsPointer != 0) // g_hashConstantAsPointer = iVar4 (0x383225a1) used as pointer? Possibly decompile bug
        {
            int gameTime = getGameTime(); // FUN_0077dd80()
            bool timeCondition = 2 < gameTime;
            if (!timeCondition)
                return false;

            if (*(int*)(g_hashConstantAsPointer + 0x2238) != 0) // +0x2238: some flag/timer
                return true;
            return false;
        }
    }
    else
    {
        if (*(int*)(g_pGlobalPlayer + 0x26d0) != 0 &&       // +0x26d0: some player timer
            g_currentTime < (g_baseTime + *(int*)(g_pGlobalPlayer + 0x26d0)))
        {
            return true;
        }
    }
    return false;
}
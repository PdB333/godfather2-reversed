// FUN_0072fbf0: Sentient::updateBehaviorState
void __thiscall Sentient::updateBehaviorState(int* thisPtr)
{
    bool bFlag;
    int iResult;
    uint uRandom;
    float10 fRandom;
    char buffer[16]; // local_10

    // Early out if game is not active
    if (!isGameActive()) {
        return;
    }

    // Skip if game is paused or menu is open
    if (isGamePaused()) {
        return;
    }

    // Get global entity manager pointer (g_entityManager)
    int* entityMgr = getGlobalEntityManager(g_entityManager);

    // Check if we should use the default behavior path
    if ((entityMgr == nullptr) || (entityMgr[0x1c/4] == 0) || (entityMgr[0x1c/4] == 0x48)) {
        // Branch 1: Determine behavior based on conditions
        bool hasIdleBehavior = hasCharacterBehavior(0x2ca3cff6); // "idle" hash
        bool idleFlag = ((thisPtr[0x238] >> 3) & 1) != 0; // check flag at +0x8E0 bit 3
        fRandom = (float10)generateRandomFloat();
        float idleThreshold = (float10)g_idleThreshold;

        if (!hasIdleBehavior || idleFlag || fRandom <= idleThreshold) {
            // Force idle behavior
            thisPtr[0x861] = 0x2ca3cff6; // behavior hash for idle
        } else {
            // Choose game-mode dependent behavior
            int gameMode = getCurrentGameMode();
            if (gameMode == 2) {
                thisPtr[0x861] = 0xe3d490c0; // -0x1c2b6f40
            } else if (gameMode == 3) {
                thisPtr[0x861] = 0xb596110a; // -0x4a69eef6
            } else {
                // Check another flag at this+0x1F54 (byte)
                if ((*(byte*)(thisPtr + 0x7d5) & 1) == 0) {
                    thisPtr[0x861] = 0x6c6aed11;
                } else {
                    thisPtr[0x861] = 0x3598f590;
                }
            }
        }
    } else {
        // Branch 2: Use default behavior evaluation
        thisPtr[0x861] = evaluateDefaultBehavior();

        // Check if global condition allows sending a behavior message
        int** globalArray = (int**)(g_someGlobalArray + 4);
        if ((*globalArray != nullptr) && (*globalArray != (int*)0x1f30)) {
            bool condA = checkConditionFlagA(0x30);
            bool condB = checkConditionFlagB(0x48);
            if (!condA && !condB) {
                // Random chance to send message
                uRandom = randomInt(100);
                if (uRandom < (uint)thisPtr[0x7d9]) {
                    profilingBegin(0, 0);
                    bFlag = sendBehaviorMessage(thisPtr, buffer, 0);
                    profilingEnd();
                    if (bFlag) {
                        goto LAB_SEND_DONE;
                    }
                }
                // Fallback: log the event
                uint profilingContext = profilingBegin(0, 0);
                logBehaviorEvent(0x8a13f7b2, 0, profilingContext, 0);
                profilingEnd();
            }
        }
    }

LAB_SEND_DONE:
    // If a behavior was selected, invoke its virtual method at vtable+0x14c
    if (thisPtr[0x861] != 0) {
        (*(void (__thiscall**)(int, int, int))thisPtr[0x861])(1, 0);
        // Note: vtable[0x14c] typically corresponds to behavior::start(priority, flags)
    }
}
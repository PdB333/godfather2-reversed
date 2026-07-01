// FUNC_NAME: ConditionManager::checkCondition
// Address: 0x007d4c20
// Role: Dispatches condition checks for game state, UI permissions, and random triggers.

bool __thiscall ConditionManager::checkCondition(
    int param2,            // Additional context parameter
    int param3,            // Additional context parameter
    int conditionType,     // Condition ID (0x13 + switch index)
    int param5             // Extra parameter
) {
    // Pointer to a subsystem (e.g., player state machine) stored at +0x58
    int* subsystemPtr = *(int**)(this + 0x58);
    bool result = false;

    switch (conditionType - 0x13) {
    case 0: {
        // Random trigger condition
        GameManager* gameMgr = GameManager::getInstance();
        // Audio channel handle (0x36 = 54)
        int audioHandle = getAudioChannel(0x36);
        bool isAudioPlaying = checkAudioPlaying(audioHandle);

        if ((isAudioPlaying) &&
            (*(float*)(this + 0x30) <= g_minTriggerInterval) &&
            (gameMgr != nullptr)) {
            // Get random 0..1 from game manager's RNG function pointer at +0x1a8
            float randomFloat = (**(code**)(*gameMgr + 0x1a8))(gameMgr);
            if (g_triggerProbability <= randomFloat * g_triggerThreshold) {
                result = true;
            }
        }

        // Check if cutscene flag needs clearing
        if ((gameMgr != nullptr) &&
            ((gameMgr->flags & 0x08) != 0) &&
            ((gameMgr->flags & 0xFFFFFFF7) != gameMgr->flags)) {
            // Clear cutscene flag via vtable at offset +0x28 of the manager's event system
            (**(code**)(gameMgr->eventSystem + 0x28))(0x10);
            gameMgr->flags &= 0xFFFFFFF7;
        }

        if ((*(uint*)(subsystemPtr + 0x249c) & 0x20) != 0) {
            return false;
        }
        break;
    }
    case 1: {
        // Game control active check
        bool inSubstate = *(byte*)(this + 0xc5) != 0;
        bool isPaused = isGamePaused();
        bool inGameState = checkGameState(10);
        if (inSubstate && (isPaused || !inGameState)) {
            return false;
        }
        return true;
    }
    case 2: {
        // Check if game manager exists
        GameManager* gameMgr = GameManager::getInstance();
        return gameMgr == nullptr;
    }
    case 3: {
        // Check if manager has a specific pointer at +0xb78
        GameManager* gameMgr = GameManager::getInstance();
        if (gameMgr != nullptr && *(int*)(gameMgr + 0xb78) != 0) {
            return true;
        }
        break;
    }
    case 4:
        // Return first byte at +0xc4
        return *(byte*)(this + 0xc4) == 0;
    case 5:
        // Return first byte at +0xc4 (inverted)
        return *(byte*)(this + 0xc4) != 0;
    case 6: {
        // Check if cutscene/streaming is blocking
        GameManager* gameMgr = GameManager::getInstance();
        if (gameMgr != nullptr) {
            bool isBlocking = isCutsceneOrStreamBlocking(gameMgr);
            return !isBlocking;
        }
        break;
    }
    default:
        // Fallback to base class handler
        result = baseConditionCheck(param2, param3, conditionType, param5);
    }

    return result;
}
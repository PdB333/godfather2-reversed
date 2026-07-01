// FUNC_NAME: ScoreDisplay::updateScoreDisplay
// Address: 0x0094e020
// Updates score display and score limit text fields based on string parameters.

void __thiscall ScoreDisplay::updateScoreDisplay(int param_2, int param_3) {
    // Check if update is enabled (flag at +0x48)
    if (*(char *)(this + 0x48) == 0) {
        return;
    }

    // Local string objects (EASTL fixed_string or similar)
    // Structure: pointer, size, capacity, allocator function pointer
    struct StringObj {
        char *ptr;
        int size;
        int capacity;
        void (*dealloc)(void *);
    };

    StringObj playerNameStr;   // local_10
    StringObj opponentNameStr; // local_20
    StringObj scoreLimitStr;   // local_30

    // Initialize to empty
    playerNameStr.ptr = nullptr;
    playerNameStr.size = 0;
    playerNameStr.capacity = 0;
    playerNameStr.dealloc = nullptr;

    opponentNameStr.ptr = nullptr;
    opponentNameStr.size = 0;
    opponentNameStr.capacity = 0;
    opponentNameStr.dealloc = nullptr;

    scoreLimitStr.ptr = nullptr;
    scoreLimitStr.size = 0;
    scoreLimitStr.capacity = 0;
    scoreLimitStr.dealloc = nullptr;

    // Resolve string from param_2 (player name hash?) into playerNameStr
    getStringFromHash(param_2, &playerNameStr, 1);
    // Resolve string from param_3 (opponent name hash?) into opponentNameStr
    getStringFromHash(param_3, &opponentNameStr, 1);

    // Set player name text (handle at +0x74)
    char *playerText = playerNameStr.ptr;
    if (playerText == nullptr) {
        playerText = emptyString; // DAT_0120546e
    }
    setText(*(int *)(this + 0x74), playerText, 0x20, playerNameStr.size);

    // Set opponent name text (handle at +0x78)
    char *opponentText = opponentNameStr.ptr;
    if (opponentText == nullptr) {
        opponentText = emptyString;
    }
    setText(*(int *)(this + 0x78), opponentText, 0x20, opponentNameStr.size);

    // Trigger UI update event
    sendUIEvent("UpdateScoreDisplay", 0, &g_uiContext, 0); // DAT_00d8b7d4

    // Resolve score limit string from member at +0x80
    getStringFromHash(*(int *)(this + 0x80), &scoreLimitStr, 1);

    // Set score limit text (handle at +0x7c)
    char *scoreLimitText = scoreLimitStr.ptr;
    if (scoreLimitText == nullptr) {
        scoreLimitText = emptyString;
    }
    setText(*(int *)(this + 0x7c), scoreLimitText, 0x20, scoreLimitStr.size);

    // Trigger score limit update event
    sendUIEvent("SetScoreLimit", 0, &g_uiContext, 0);

    // Free allocated strings if they were allocated
    if (scoreLimitStr.ptr != nullptr) {
        scoreLimitStr.dealloc(scoreLimitStr.ptr);
    }
    if (opponentNameStr.ptr != nullptr) {
        opponentNameStr.dealloc(opponentNameStr.ptr);
    }
    if (playerNameStr.ptr != nullptr) {
        playerNameStr.dealloc(playerNameStr.ptr);
    }
}
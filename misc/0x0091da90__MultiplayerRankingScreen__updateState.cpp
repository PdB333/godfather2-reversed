// FUNC_NAME: MultiplayerRankingScreen::updateState
void __fastcall MultiplayerRankingScreen::updateState(int this)
{
    int stateMode = *(int *)(this + 0xb8);     // state identifier, +0xB8
    int count = *(int *)(this + 0xb4);          // some counter, +0xB4
    int value = *(int *)(this + 0xc0);          // associated value, +0xC0
    int rankingDataPtr = *(int *)(this + 0xf0); // pointer to ranking text data, +0xF0

    if (stateMode == 1)
    {
        // If there is pending data to process, lock critical section and clear
        if (count + value != 0)
        {
            EnterCriticalSection(&g_rankingMutex, 0); // FUN_00402050, lock with spin count 0
        }
        // Call virtual function at index 25 (0x64/4) on the behavior object at +0x50
        int behaviorPtr = *(int *)(this + 0x50); // pointer to behavior object, +0x50
        (*(void (**)(int, int))(*(int *)behaviorPtr + 100))(this + 0xc0, count);
        return;
    }

    if ((unsigned int)(stateMode - 10) < 0x10) // stateMode between 10 and 25 inclusive
    {
        if (count + value != 0)
        {
            EnterCriticalSection(&g_rankingMutex, 0);
        }
        // Set internal target value
        SetTargetValue((int *)(this + 0xc0), count); // FUN_0091cea0
        // Update the ranking text data (likely copying 0x80 bytes)
        UpdateRankingTextData(count + value, rankingDataPtr, 0x80); // FUN_00918940
        // Send UI event "UpdateRankingText" with ranking data pointer
        SendUIMessage("UpdateRankingText", 0, &g_rankingUIContext, 1, rankingDataPtr); // FUN_005a04a0
        return;
    }

    // Default: send "MoveUp" UI event (no operation in this context?)
    SendUIMessage("MoveUp", 0, &g_rankingUIContext, 0);
}
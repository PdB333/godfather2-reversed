// FUNC_NAME: StatsManager::processStatsUpdate
void StatsManager::processStatsUpdate(int contextFlags)
{
    GameStateManager* gameStateMgr = gGameStateManager;
    if (gameStateMgr == nullptr)
        return;

    int currentState = gameStateMgr->currentGameState; // +0x2e
    if (currentState != 0xd && currentState != 0xe && currentState != 0xf &&
        currentState != 0x10 && currentState != 0x11)
        return;

    debugPrint();
    gameStateMgr->vtable->someMethod(); // (**(code **)(*gameStateMgr + 8))()

    bool isPaused = isGamePaused(); // FUN_009185a0
    bool bPaused = (isPaused == 0);

    uint statCount = 0;
    if (contextFlags != 0 && gameStateMgr->isMultiplayer == '\0') // +0x2f
    {
        if (checkStatsUpdateAllowed()) // FUN_00adc2d0
        {
            const char* errorStr = getStatsErrorString(); // FUN_00adc2e0
            logMessage(errorStr, "Failed to update stats"); // FUN_005676d0
            finalizeStatsUpdate(bPaused, 0); // FUN_0091ac70
            return;
        }

        if (gIsMultiplayer == '\0') // DAT_00e54d1c
        {
            beginSinglePlayerStats(contextFlags); // FUN_00ae6d70
            statCount = getStatsCount(); // FUN_0091a2d0
            uint processed = 0;
            uint count = statCount;
            if (count != 0)
            {
                do
                {
                    void* mem = allocateMemory(0x30); // FUN_009c8e50
                    StatEntry* entry;
                    if (mem == nullptr)
                        entry = nullptr;
                    else
                        entry = constructStatEntry(); // FUN_00917c30

                    int state = gameStateMgr->currentGameState;
                    if (state == 0xd)
                    {
                        addSinglePlayerStat(entry, processed, 0x23, 0x21, 0x22); // FUN_00917d80
                    }
                    else if (state == 0xe)
                    {
                        addSinglePlayerStat(entry, processed, 0x26, 0x24, 0x25);
                    }
                    else if (state == 0xf)
                    {
                        addSinglePlayerStat(entry, processed, 0x29, 0x27, 0x28);
                    }
                    else if (state == 0x10)
                    {
                        addSinglePlayerStat(entry, processed, 0x2c, 0x2a, 0x2b);
                    }
                    // else state 0x11? No action for that state in this path

                    releaseStatEntry(entry); // FUN_0091a760
                    processed++;
                } while (processed < count);
            }
        }
        else
        {
            beginMultiplayerStats(contextFlags); // FUN_00ae6ba0
            statCount = getStatsCount(); // FUN_0091a2d0
            uint processed = 0;
            uint count = statCount;
            if (count != 0)
            {
                do
                {
                    void* mem = allocateMemory(0x30);
                    StatEntry* entry;
                    if (mem == nullptr)
                        entry = nullptr;
                    else
                        entry = constructStatEntry();

                    int state = gameStateMgr->currentGameState;
                    if (state == 0xd)
                    {
                        addMultiplayerStat(entry, processed, 0x23, 0x21, 0x22); // FUN_00917f40
                    }
                    else if (state == 0xe)
                    {
                        addMultiplayerStat(entry, processed, 0x26, 0x24, 0x25);
                    }
                    else if (state == 0xf)
                    {
                        addMultiplayerStat(entry, processed, 0x29, 0x27, 0x28);
                    }
                    else if (state == 0x10)
                    {
                        addMultiplayerStat(entry, processed, 0x2c, 0x2a, 0x2b);
                    }

                    releaseStatEntry(entry);
                    processed++;
                    if (count <= processed)
                    {
                        finalizeStatsUpdate(bPaused, count);
                        return;
                    }
                } while (true);
            }
        }
    }

    finalizeStatsUpdate(bPaused, statCount);
}
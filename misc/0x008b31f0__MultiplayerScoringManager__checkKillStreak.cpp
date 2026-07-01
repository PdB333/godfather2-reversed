// FUNC_NAME: MultiplayerScoringManager::checkKillStreak
void __thiscall MultiplayerScoringManager::checkKillStreak(int this, int param2, int playerId) 
{
    int temp1;
    int temp2;
    int iteratorRetValue;
    int killCount = 0;
    // Iterator structure on stack; elements: iterator (pointer), status fields
    int (*iteratorFuncPtr)(); // Function pointer for operator()
    char tempBuffer[4112];
    char textBuffer[12];
    int eventIteratorState[3]; // For fanfare state

    // FUN_004bab20 likely creates an iterator from param2 and playerId
    // local_1040 -> address of iterator on stack, local_103c, local_1038 -> internal states
    // We'll assume there's a helper class KillEventIterator.
    KillEventIterator iterator;
    FUN_004bab20(&iterator, param2, playerId);

    if (playerId == -1) return;

    // Loop through kill events
    while (iterator.flags != 0) { // local_103c !=0 or local_1038 !=0
        iteratorRetValue = iterator.getNextEvent(); // calls vtable method
        if ((*(int*)(iteratorRetValue + 8) == *(int*)(this + 0x50)) &&
            (*(int*)(iteratorRetValue + 0x10) == playerId) &&
            (*(int*)(iteratorRetValue + 0x0C) > 0)) 
        {
            // Found a kill event from same team/player
            killCount++;
            iterator.moveToNext(); // call vtable[2] to advance
        }
        else if ((*(int*)(iteratorRetValue + 0x14) == playerId) ||
                 (*(int*)(iteratorRetValue + 0x0C) < 0)) 
        {
            // Event not relevant – stop iterating
            break;
        }
        else 
        {
            iterator.moveToNext(); // unrelated event, skip
        }
    }

    // Check if killCount is within valid range for this streak
    if ((killCount >= *(int*)(this + 0x64)) && (killCount <= *(int*)(this + 0x68))) 
    {
        // Start logging
        FUN_00604be0();

        char* playerName = (char*)FUN_004baf60(playerId);
        char** namePtr = (char**)FUN_004bb600(playerName);
        char* displayName = *namePtr;
        if (displayName == 0) 
        {
            displayName = "&DAT_0120546e"; // Default string placeholder
        }

        FUN_00604c10(0x70, displayName); // Log player name
        FUN_00604c80(0x73, killCount);   // Log kill count

        // Prepare fanfare HUD element
        eventIteratorState[0] = 0;
        eventIteratorState[1] = 0;
        eventIteratorState[2] = 0;
        int (*finalizeCallback)(int) = 0;

        FUN_006038a0(DAT_012234a4, tempBuffer, eventIteratorState, "$hud_fanfare_mp_player_killing_spree");
        FUN_0094e5d0(eventIteratorState); // Start fanfare display

        // Check if this is the initial streak (killCount == minKills) and player is local
        if (killCount == *(int*)(this + 0x64))
        {
            int* globalPtr = *(int**)(0x12233a0 + 4);
            if (globalPtr != 0 && *(int*)(globalPtr - 0x1f30) != 0 && 
                *(int*)(globalPtr - 0x1f30 + 0x1f30 - 0x38) == playerId) 
            {
                // Award streak bonus or update state
                FUN_0045ca00(globalPtr - 0x1f30);
                FUN_0045c400(this + 0x6c, textBuffer, 0);
                FUN_0045cac0();
            }
        }

        // Clean up fanfare resources if allocated
        if (eventIteratorState[0] != 0) 
        {
            finalizeCallback(eventIteratorState[0]);
        }

        FUN_00604c00(); // End logging
    }

    return;
}
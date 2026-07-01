// FUNC_NAME: MultiplayerScenarioManager::startJoiningGame

void __thiscall MultiplayerScenarioManager::startJoiningGame(int* thisPtr, uint32 arg0, uint32 arg1)
{
    int joiningGameState;

    // Call virtual method at vtable offset 0xc (likely pre-join initialization)
    (*(void (__thiscall**)(int*))(*(int**)thisPtr + 3))(thisPtr);

    if (g_bMultiplayerEnabled != 0) {
        // Allocate memory for joining game state structure (size 0xf0 bytes)
        joiningGameState = allocateMemory(0xf0);

        if (joiningGameState == 0) {
            joiningGameState = 0;
        } else {
            // Initialize the state object (construct with parameter 0)
            joiningGameState = ConstructJoiningGameState(0);
        }

        // Set loading phase/state (2 and 3 likely represent "joining game" phase)
        SetLoadingState(2, 3);

        // Display "Joining Game" localized message
        ShowLocalizedString("$mp_joining_game");

        // Set state field at +0xc to 0xd (likely an enum for "joining" state)
        *(uint32*)(joiningGameState + 0xc) = 0xd;

        // Show loading screen (set visible)
        ShowLoadingScreen(1);

        // Set a constant identifier at +0x20 (possibly a magic number or RTTI)
        *(uint32*)(joiningGameState + 0x20) = 0xe8d242ca;

        // Set function pointer at +0x14 to the join result callback (label 0x0096f710)
        *(void**)(joiningGameState + 0x14) = &JoiningGameResultCallback;

        // Start loading tick/timer
        StartLoadingTick();

        // Process join game parameters (arg0 and arg1 from caller)
        ProcessJoinParameters(arg0, arg1);
    }
}
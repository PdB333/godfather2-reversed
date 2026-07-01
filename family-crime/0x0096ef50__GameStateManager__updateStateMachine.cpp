// FUNC_NAME: GameStateManager::updateStateMachine
// Address: 0x0096ef50
// Role: State machine update for game flow management (EARS::GameStateManager)
// Handles transitions between initialization, loading, gameplay, and menu states.

void __thiscall GameStateManager::updateStateMachine(int *this)
{
    // State at +0xDC
    int state = this[0x37]; // mState

    // Global reference to main game manager (DAT_01223484)
    // Check if certain subsystems are idle/ready
    bool isSubsystemReady()
    {
        // +0x28, +0x2c from game manager: two pointers
        bool ready = (*(int*)(DAT_01223484 + 0x28) == 0 && *(int*)(DAT_01223484 + 0x2c) == 0);
        // Also check if the pointer is null? The condition DAT_01223484 == -0x28 is unusual - likely a sentinel check
        if (DAT_01223484 == -0x28) // perhaps indicates null context?
            ready = true;

        // +0x34: another subsystem pointer, if non-null then call its virtual +0x20
        if (*(int*)(DAT_01223484 + 0x34) != 0)
        {
            if (!(**(code**)(**(int**)(DAT_01223484 + 0x34) + 0x20))())
                ready = false;
        }
        return ready;
    }

    switch (state)
    {
    case 0: // kState_Init
        // Setup a timer or transition callback: param_1+4 (offset 0x10) points to something
        FUN_005c02f0(this + 4, &LAB_0096ee10, 1);
        FUN_008a43b0(0); // e.g., setLoadingScreen(false)
        FUN_00402050(&DAT_01130310, 0); // e.g., setAudioVolume(0)
        // Call virtual member function at vtable+0x2C (e.g., onStart)
        (**(code**)(*this + 0x2c))();
        // Global state flag
        DAT_00e5672c = 0x11;
        FUN_00931010(); // e.g., initialize rendering
        return;

    case 1: // kState_Load
        // Set two timer/state indices to -1
        this[0x67] = -1; // mLoadTimer1 at +0x19C
        this[0x68] = -1; // mLoadTimer2 at +0x1A0
        // Clear a byte flag at +0x221
        *(char*)(this + 0x221) = 0;
        // Fall through to case 5

    case 5: // kState_WaitForReady
        if (isSubsystemReady())
        {
            FUN_0096a230(); // e.g., transitionToPlay()
            return;
        }
        break;

    case 2: // kState_Menu
        // (also reached from cases 6,8,9 via goto)
        FUN_00402050(&DAT_01130310, 0);
        FUN_0096a2f0(); // e.g., enterMenuState()
        return;

    case 3: // kState_Game
        FUN_00402050(&DAT_01130310, 0);
        FUN_00966d90(); // e.g., setupGameWorld()
        FUN_00969720(); // e.g., startHavokSimulation()
        // Call a method on a child object at +0x2EC (param_1[0xbb]) via virtual +0x94
        (**(code**)(this[0xbb] + 0x94))();
        return;

    case 4: // kState_Ready
        // Clear two flag bytes
        *(char*)(this + 0x6F1) = 0; // mReadyFlagA
        *(char*)(this + 0x1BC) = 0; // mReadyFlagB
        // Log "SetReadyState"
        FUN_005a04a0("SetReadyState", 0, &DAT_00d8cdec, 0);
        FUN_00969c50(); // e.g., finalizeLoading()
        return;

    case 6: // kState_UnloadA
    case 8: // kState_UnloadB
    case 9: // kState_UnloadC
        if (isSubsystemReady())
        {
            // Go to case 2 (menu state)
            FUN_00402050(&DAT_01130310, 0);
            FUN_0096a2f0();
            return;
        }
        break;

    case 7: // kState_SubMenu
        if (isSubsystemReady())
        {
            if (FUN_00567990() == '\0') // e.g., checkTransitionBlocked
            {
                FUN_0096a230(); // transition to play
                return;
            }
        }
        break;

    case 0xB: // kState_Pause
        FUN_0096d810(1); // e.g., pauseGame(true)
        break;

    case 0xC: // kState_Exit
        FUN_00402050(&DAT_01130310, 0);
        FUN_00967d90(); // e.g., cleanupAndExit()
        return;
    }
}
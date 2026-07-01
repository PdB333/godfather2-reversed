// FUNC_NAME: MultiplayerScenarioManager::updateMatchSearchTimer
// Address: 0x0096f9b0
// Role: Updates the match search timer. When timer expires (<=0), allocates and initializes a new match search state, sets UI message, and calls virtual function.

void __thiscall MultiplayerScenarioManager::updateMatchSearchTimer(int param_2)
{
    // offset 0x5d is float m_searchTimer (at offset 0x174)
    if (*(float*)(this + 0x174) <= 0.0f)
    {
        // Allocate 0xF0 bytes (240) for a new match search state object
        int* pState = (int*)FUN_009c8e50(0xF0);
        if (pState != 0)
        {
            // Initialize the state (constructor, parameter 0)
            pState = (int*)FUN_00982280(0);
        }
        // Set UI state and message
        FUN_00981f10(2, 3);
        FUN_00981eb0("$mp_match_searching");
        // State fields: +0x0C = state type (13 = searching)
        pState[0x3] = 0xD;  // 0x0C/4 = 3
        FUN_00982400(1);
        // +0x20 = some identifier (hash?)
        pState[0x8] = 0xE8D242CA; // 0x20/4 = 8
        // +0x14 = function pointer to state handler
        *(void**)(pState + 0x5) = &LAB_0096f710; // 0x14/4 = 5
        FUN_00982e10();
        // Call virtual function at vtable offset 0xC (index 3)
        (*(void (__thiscall**)(MultiplayerScenarioManager*))(*(DWORD*)this + 0xC))(this);
    }
    // Reset the timer to the given value
    *(float*)(this + 0x174) = (float)param_2;
}
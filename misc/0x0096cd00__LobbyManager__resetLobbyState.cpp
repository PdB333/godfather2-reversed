// FUNC_NAME: LobbyManager::resetLobbyState

void __fastcall LobbyManager::resetLobbyState(int thisPtr)
{
    // Reset global lobby active flag
    g_lobbyActive = 0;

    // Reset internal lobby timers / state
    resetLobbyTimers();

    // Copy selected player index (offset 0x1F4 -> +0x160)
    *(char *)(thisPtr + 0x160) = *(char *)(thisPtr + 500);  // decimal 500 == 0x1F4

    // Build lobby request with current member data
    // Offsets: +0x120, +0x128, +0x12C, +0x130, +0x138, +0xE4, +0x114, +0x124, +0xFC, +0x104
    buildLobbyRequest(
        *(int *)(thisPtr + 0x120),
        *(int *)(thisPtr + 0x128),
        *(int *)(thisPtr + 0x12C),   // decimal 300 == 0x12C
        *(int *)(thisPtr + 0x130),
        *(int *)(thisPtr + 0x138),
        *(int *)(thisPtr + 0xE4),
        *(int *)(thisPtr + 0x114),
        *(int *)(thisPtr + 0x124),
        *(int *)(thisPtr + 0xFC),
        *(int *)(thisPtr + 0x104)
    );

    // Show lobby UI via script call
    scriptCall("ShowLobby", 0, &DAT_00d8cdec, 0);

    // Set lobby phase to 7 (e.g., LobbyPhase_Active)
    setLobbyPhase(7);

    // Push state machine callback (state machine at +0x10, label at LAB_0096ccb0, mode 1)
    pushStateMachineState(thisPtr + 0x10, &LAB_0096ccb0, 1);
}
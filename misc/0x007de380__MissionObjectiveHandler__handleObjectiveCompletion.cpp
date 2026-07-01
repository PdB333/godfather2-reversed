// FUNC_NAME: MissionObjectiveHandler::handleObjectiveCompletion

void __thiscall MissionObjectiveHandler::handleObjectiveCompletion(void) {
    // Profiler/debug event
    debugEvent(0x25);

    // Get the owning entity (e.g., player)
    Entity* pOwner = *(Entity**)(this + 0x58);
    // Clear bit 17 (0x20000) in flags at offset 0x249c
    *(uint32_t*)(pOwner + 0x249c) &= 0xFFFDFFFF;

    // Get current objective pointer (e.g., active crime scene or mission goal)
    Objective* pCurrentObjective = *(Objective**)(pOwner + 0x74C);
    Objective* pObjectiveBase = nullptr;
    if (pCurrentObjective != nullptr) {
        pObjectiveBase = (Objective*)((int)pCurrentObjective - 0x48); // Parent structure offset
    }

    // Check if the objective is in a specific state (e.g., has dialog flag)
    if (pObjectiveBase != nullptr && *(uint8_t*)(pCurrentObjective + 0x160) == 1) {
        // Look up a specific object by hash
        if (FindObjectByHash(0xC4BC3CE7, 0) != 0) {
            // Get the audio manager
            if (GetAudioManager() != 0) {
                // Prepare audio parameters
                uint32_t audioParam2 = 0;
                uint32_t audioParam1 = GetCurrentPlayerId(0, 0);
                // Play a specific audio event (hash 0x315898D5) on channel 0x40
                PlayAudioEvent(0x315898D5, 0x40, audioParam1, audioParam2);
                // Release? (likely end of audio setup)
                ReleaseAudioResource();

                // Retrieve global game manager and call its method
                GameManager* pGameManager = (GameManager*)GetGlobalPointer(DAT_01130FA0);
                if (pGameManager != nullptr) {
                    // vtable offset +0x24: likely HandleEvent(uint32 hash) or similar
                    pGameManager->vtbl->HandleEvent(0x315898D5);
                }
            }
        }
        // Reset some state (e.g., timer) and set UI flag
        ResetObjectiveState(0);
        SetDialogFlag(0x26, 0);
    }

    // Extract an index from the owner's data (at offset 0x6E8 >> 2)
    int32_t dialogIndex = *(uint32_t*)(pOwner + 0x6E8) >> 2;

    // Decide which dialog to play based on objective state
    if (pObjectiveBase != nullptr && *(uint8_t*)(pObjectiveBase + 0x1AA) == 2) {
        // Objective is in a specific phase (e.g., completed with positive outcome)
        if (*(uint8_t*)(pObjectiveBase + 0x1A8) == 1) {
            // Play success dialog
            PlayDialogEvent(0x8986BBA, 0, dialogIndex, 1, 1, 1, 0, *(uint32_t*)(pOwner + 0x1DBC));
            ShowDialogUI();
            return;
        }
        // Otherwise play neutral/failure dialog
        PlayDialogEvent(0x3DD3A028, 0, dialogIndex, 1, 1, 1, 0, *(uint32_t*)(pOwner + 0x1DBC));
        ShowDialogUI();
        return;
    }

    // Default: play generic outcome dialog
    PlayDialogEvent(0x61FFFCC9, 0, dialogIndex, 1, 1, 1, 0, *(uint32_t*)(pOwner + 0x1DBC));
    ShowDialogUI();
}
// FUNC_NAME: MultiplayerScenarioManager::showLobbyLeaveConfirmation
void __thiscall MultiplayerScenarioManager::showLobbyLeaveConfirmation(MultiplayerScenarioManager* this) {
    int dialogPtr;
    
    dialogPtr = allocateDialogMemory(0xf0);
    if (dialogPtr != 0) {
        dialogPtr = createConfirmationDialog(0);
    }
    
    // Dialog flag (type?) = 2
    *(int*)(dialogPtr + 0x0C) = 2;
    
    // Magic constants (timer/ID?)
    *(int*)(dialogPtr + 0x20) = 0xB9754031;
    *(int*)(dialogPtr + 0x1C) = 0x997DEE17;
    
    // Check current lobby state (at +0xDC)
    if (*(int*)(this + 0xDC) == 5) {
        setLocalizedString("$mp_confirm_leaving_host_lobby");
        *(void**)(dialogPtr + 0x14) = &LAB_00965640;  // Host lobby confirmation callback
    } else if (*(int*)(this + 0xDC) == 7) {
        setLocalizedString("$mp_confirm_leaving_join_lobby");
        *(void**)(dialogPtr + 0x14) = &LAB_009655E0;  // Join lobby confirmation callback
        showLobbyLeaveDialog();
        return;
    }
    showLobbyLeaveDialog();
}
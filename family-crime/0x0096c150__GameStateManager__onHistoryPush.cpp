// FUNC_NAME: GameStateManager::onHistoryPush

void __fastcall GameStateManager::onHistoryPush(GameStateManager* this)
{
    // Global flag: possibly enables history push events
    if (g_bHistoryPushEnabled != 0) {
        // Set state to 4 (e.g., STATE_HISTORY_PUSH)
        this->stateField = 4; // +0x1e4

        // Clear or reset sub-object at offset 0x1a8 (e.g., a timer or data buffer)
        this->clearSubObject(); // FUN_008a3be0(this + 0x1a8)

        // Log history push event with reference data
        PushHistory("PushHistory", 0, &g_historyData, 0); // FUN_005a04a0

        // Perform global update (e.g., frame tick or event propagation)
        GlobalUpdate(); // FUN_00969720

        // Call virtual method at vtable offset 0x94 (index 37)
        // Likely handles the new state or updates internal state machine
        (this->vtable->onStateEnter)(this); // (**(code **)(*(int *)(param_1 + 0x2ec) + 0x94))()
    }
}
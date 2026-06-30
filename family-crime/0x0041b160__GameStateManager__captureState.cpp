// FUNC_NAME: GameStateManager::captureState
void GameStateManager::captureState(void)
{
    // 76-byte buffer for storing a snapshot of game state
    uint8_t stateBuffer[76];

    // Perform pre-capture initialization (FUN_00417560)
    stateCaptureInit();

    // Fill buffer with current state data (FUN_004919f0)
    captureStateData(stateBuffer);
}
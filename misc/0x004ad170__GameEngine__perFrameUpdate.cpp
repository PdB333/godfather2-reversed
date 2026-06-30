// FUNC_NAME: GameEngine::perFrameUpdate
// Function address: 0x004ad170
// Identified role: Simple wrapper that delegates to the actual per-frame update routine (0x004ae6f0).
// This function is called from many game systems to trigger a common update step.
void GameEngine::perFrameUpdate(void)
{
    // Delegate to the real update implementation
    FUN_004ae6f0();
    return;
}
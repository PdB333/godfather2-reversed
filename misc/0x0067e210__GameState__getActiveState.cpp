// FUNC_NAME: GameState::getActiveState
int GameState::getActiveState(void)
{
    uint upper24;
    
    upper24 = (uint)g_gameStatePtr >> 8;
    if (g_gameStatePtr != (GameState*)0) {
        // Return pointer with low byte replaced by flag at +0x1c
        return (upper24 << 8) | (*(int *)((int)g_gameStatePtr + 0x1c) != 0);
    }
    return (uint)upper24 << 8; // Returns 0 when null
}
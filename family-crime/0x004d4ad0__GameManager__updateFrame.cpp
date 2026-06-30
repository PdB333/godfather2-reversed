// FUNC_NAME: GameManager::updateFrame
// Function address: 0x004d4ad0
// Role: Main per-frame update wrapper. Resets frame state then delegates to core update logic.
// Parameters: param1 and param2 are likely delta time and some game state flag.
void GameManager::updateFrame(int param1, int param2)
{
    // Reset frame-level state (e.g., clear input accumulators, render targets, etc.)
    FUN_004d4060(0, 0);
    // Perform actual frame update (physics, AI, rendering, etc.)
    FUN_004d4a90(param1, param2);
}
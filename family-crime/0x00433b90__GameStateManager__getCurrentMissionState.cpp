// FUNC_NAME: GameStateManager::getCurrentMissionState
// Function address: 0x00433b90
// This getter retrieves a 32-bit value from the game state object pointed to by this+0x4, at offset 0x39F8.
// The offset 0x39F8 likely stores the active mission index or state.
uint32_t __thiscall GameStateManager::getCurrentMissionState(void)
{
    // Dereference this+0x4 to get pointer to main game state structure
    uint8_t* pGameState = *(uint8_t**)((uint8_t*)this + 4);
    // Return the 32-bit value at offset 0x39F8 within the game state
    return *(uint32_t*)(pGameState + 0x39F8);
}
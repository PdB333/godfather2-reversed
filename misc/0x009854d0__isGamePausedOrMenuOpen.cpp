// FUNC_NAME: isGamePausedOrMenuOpen
// Address: 0x009854d0
// Checks if the game is in a paused or menu state based on global game state.
// Returns true if either pause count is non-zero or the menu flag (bit 7) is set.

struct GlobalGameState {
    // +0x00: unknown
    // +0x04: unknown
    // +0x08: unknown
    // +0x0c: pause counter (0 = not paused)
    int32_t pauseCount;
    // +0x10: flags (bit 7 = menu open flag)
    uint32_t flags;
};

extern GlobalGameState* g_gameState; // DAT_01129828

bool isGamePausedOrMenuOpen() {
    // Return false only when not paused and no menu is open
    if (g_gameState->pauseCount == 0 && ((g_gameState->flags >> 7) & 1) == 0) {
        return false;
    }
    return true;
}
// FUNC_NAME: isGameStateFreeRoam
// Address: 0x004df190
// Returns true if the global game state equals 7 (e.g., free roam mode).

extern int g_currentGameState;  // +0x01194540

bool isGameStateFreeRoam() {
    return g_currentGameState == 7;
}
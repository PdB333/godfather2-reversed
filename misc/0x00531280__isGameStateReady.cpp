// FUNC_NAME: isGameStateReady
bool isGameStateReady(void)
{
    // Check if game state is set to 0x06 (likely a specific mode) and a flag is non-zero
    if ((g_gameState == 0x06) && (g_someFlag != 0)) {
        return true;
    }
    return false;
}
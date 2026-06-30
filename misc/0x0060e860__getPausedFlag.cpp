// FUNC_NAME: getPausedFlag
unsigned char getPausedFlag(void)
{
    // Global flag at 0x0120587f, likely indicates if the game is paused
    // Stored as a single byte, read by many systems (input, animation, etc.)
    return g_isPaused;
}
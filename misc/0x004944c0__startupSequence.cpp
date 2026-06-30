// FUNC_NAME: startupSequence
// Function at 0x004944c0: Top-level startup sequence - calls core engine initialization then game-specific initialization.
void startupSequence(void)
{
    coreEngineInit();   // 0x00490b20
    gameplayInit();     // 0x00494220
}
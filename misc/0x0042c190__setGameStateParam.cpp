// FUNC_NAME: setGameStateParam
void __cdecl setGameStateParam(int value)
{
    // Global variable at 0x0110ac2c - stores a game state parameter or flag
    g_gameStateParam = value;
}
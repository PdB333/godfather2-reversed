// FUNC_NAME: Debug::logPlayerInformation
void Debug::logPlayerInformation(void)
{
    int outputBuffer; // +0x00 (4-byte output buffer)
    int unused1 = 0; // local_1c
    int unused2 = 0; // local_18
    int unused3 = 0; // local_14

    // Call debug logging function with:
    //   - g_pGameManager (global 0x0121a390)
    //   - g_pPlayerManager + 0x18 (likely m_pActivePlayer offset)
    //   - pointer to output buffer (unused afterwards)
    Debug::logPosition(g_pGameManager, *(int*)(g_pPlayerManager + 0x18), &outputBuffer);
}
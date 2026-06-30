// FUNC_NAME: setGlobalFlag
// Address: 0x0049e640
// Role: Sets a global boolean flag to 1 (enabled). The flag at offset 0x0120546c likely controls a game state or toggle.

void setGlobalFlag(void)
{
    g_bSomeFlag = 1; // DAT_0120546c
    return;
}
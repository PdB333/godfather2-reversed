// FUNC_NAME: initializeMaxPacketSize
// Address: 0x0065b260
// Role: Ensures the global max packet size is clamped to 256 bytes (0x100). Calls a subordinate initializer first.

void initializeMaxPacketSize(void)
{
    FUN_0065b320();
    if ((g_maxPacketSize < 256) || (256 < g_maxPacketSize)) {
        g_maxPacketSize = 256;
    }
    return;
}
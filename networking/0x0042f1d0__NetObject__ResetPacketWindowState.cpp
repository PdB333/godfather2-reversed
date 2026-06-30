// FUNC_NAME: NetObject::ResetPacketWindowState

void NetObject::ResetPacketWindowState() {
    // Offset 0x60: packet window base sequence
    mBaseSeq = 0;
    // Offset 0x64: next expected sequence
    mNextSeq = 0;
    // Offset 0x68: last ack value
    mLastAck = 0;
    // Offset 0x6C: lost packet count
    mLostCount = 0;
    // Offset 0x70: duplicate packet count
    mDupCount = 0;
    // Offset 0x74: window size counter
    mWindowSize = 0;
    // Offset 0x78: invalid handle (-1) for ghost index
    mGhostIndex = 0xFFFFFFFF;

    // Ensure global subsystems are initialized
    if (g_subsystem1InitFlag != 1) {
        (*(void (__thiscall **)(void *, int, int))(*g_enginePtr + 0x198))(g_enginePtr, 1, 1);
        g_subsystem1InitFlag = 1;
    }
    if (g_subsystem2InitFlag != 0) {
        (*(void (__thiscall **)(void *, int, int, int, int))(*g_enginePtr + 0x190))(g_enginePtr, 1, 0, 0, 0);
        g_subsystem2InitFlag = 0;
    }
}
// FUNC_NAME: clearGlobalFlag
// Address: 0x0068ac20
// Clears a global byte flag (DAT_01129a71) to 0. Likely a debug or state flag.
void clearGlobalFlag(void) {
    g_byteFlag = 0; // DAT_01129a71
}
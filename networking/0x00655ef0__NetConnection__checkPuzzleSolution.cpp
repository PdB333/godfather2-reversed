// FUNC_NAME: NetConnection::checkPuzzleSolution
void NetConnection::checkPuzzleSolution() {
    // +0x148: puzzle challenge data buffer
    // +0x133: secondary challenge data
    // +0x13b: additional challenge data
    // +0x144: challenge length
    // +0x14c: another parameter (likely nonce or key)
    bool bSolved = verifyPuzzle(
        (char*)(this + 0x148),
        (char*)(this + 0x133),
        (char*)(this + 0x13b),
        *(uint32_t*)(this + 0x144),
        *(uint32_t*)(this + 0x14c)
    );
    if (bSolved) {
        // +0x1a0: puzzle start timestamp
        int iCurrentTime = getTickCount();  // FUN_0065c190
        logPrintf("Client puzzle solved in %d ms.", iCurrentTime - *(int*)(this + 0x1a0));
        // +0x1b4: puzzle state (4 = solved)
        *(uint32_t*)(this + 0x1b4) = 4;
        onPuzzleSolved();  // FUN_00655f50
    }
}
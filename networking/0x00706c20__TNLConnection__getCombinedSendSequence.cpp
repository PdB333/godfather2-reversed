// FUNC_NAME: TNLConnection::getCombinedSendSequence
uint __thiscall TNLConnection::getCombinedSendSequence() {
    // Offsets verified from xbox debug symbols:
    // +0x278 = mLastAckedSequence (uint32)
    // +0x27c = mNextSendSequence (uint32)
    uint nextSeq = *(uint *)(this + 0x27c) + 2;
    uint lastAcked = *(uint *)(this + 0x278);
    bool windowFull = lastAcked <= nextSeq;
    // Pack: high 24 bits = nextSeq > 8, low 8 bits = windowFull
    return ((nextSeq >> 8) & 0xFFFFFF) << 8 | (windowFull ? 1 : 0);
}
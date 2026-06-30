// FUNC_NAME: PacketChannel::reset
void PacketChannel::reset()
{
    // Clear all fields - offsets based on reverse engineering
    *(uint64_t *)(this + 0x80) = 0;           // +0x80: m_packetTimestamp or m_lastAckTime
    *(int32_t *)(this + 0x168) = 0;           // +0x168: m_someCounter
    *(uint8_t *)this = 0;                     // +0x00: m_typeTag or m_active
    *(int32_t *)(this + 0x130) = 0;           // +0x130: m_cumulativeLoss?
    *(int32_t *)(this + 0xf8) = 0;            // +0xf8: m_bufferIndex?
    *(int32_t *)(this + 0x9c) = 0xffffffff;   // +0x9c: m_sendSequenceBase (initial -1)
    *(int32_t *)(this + 0xa0) = 0xffffffff;   // +0xa0: m_recvSequenceBase (initial -1)
    *(uint8_t *)(this + 0xfd) = 0;            // +0xfd: m_unreliableFlag
    *(uint8_t *)(this + 0xfe) = 0;            // +0xfe: m_compressedFlag?
    *(uint8_t *)(this + 0xff) = 0;            // +0xff: m_encryptedFlag?
    *(int32_t *)(this + 0x100) = 0;           // +0x100: m_sendWindowSize
    *(int32_t *)(this + 0x108) = 0;           // +0x108: m_recvWindowSize
    *(uint8_t *)(this + 0xfc) = 3;            // +0xfc: m_maxRetransmits (default 3)
    *(int32_t *)(this + 0x104) = 0x20;        // +0x104: m_windowSpan (32)
    *(uint64_t *)(this + 0x10c) = 0;          // +0x10c: m_sendFlagsMask
    *(uint64_t *)(this + 0x114) = 0;          // +0x114: m_recvFlagsMask
    *(int32_t *)(this + 0x134) = DAT_00e2eff4; // +0x134: m_timeoutThreshold from global
    *(int32_t *)(this + 0xa4) = 0;            // +0xa4: m_someIndex
    *(int32_t *)(this + 0x94) = DAT_00e4459c; // +0x94: m_initialSequence from global
    *(int32_t *)(this + 0x88) = 0x1000;       // +0x88: m_sendBufferSize (4096)
    *(int32_t *)(this + 0x8c) = 0x1000;       // +0x8c: m_recvBufferSize (4096)
    *(int32_t *)(this + 0x90) = 0;            // +0x90: m_bufferOffset
    *(int32_t *)(this + 0x98) = 0;            // +0x98: m_nextSequence
}
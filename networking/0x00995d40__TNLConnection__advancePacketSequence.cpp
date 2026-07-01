// FUNC_NAME: TNLConnection::advancePacketSequence
void __thiscall TNLConnection::advancePacketSequence(void* thisPtr) {
    // +0x04: current send sequence number
    uint32_t& currentSequence = *(uint32_t*)((uint8_t*)thisPtr + 4);
    // +0x08: maximum sequence number (top 2 bits used as flags, masked to 30-bit value)
    uint32_t maxSequence = *(uint32_t*)((uint8_t*)thisPtr + 8) & 0x3FFFFFFF;

    // Check for sequence wrap: if current equals max, flush or reset buffer (size 0x40 = 64)
    if (currentSequence == maxSequence) {
        FUN_00aa4190(thisPtr, 0x40); // likely flushSendBuffer or resetWindow
    }

    // Advance sequence number
    currentSequence++;

    // Post-increment debug/log call
    FUN_005420c0(); // likely debugPrint or packetLog
}
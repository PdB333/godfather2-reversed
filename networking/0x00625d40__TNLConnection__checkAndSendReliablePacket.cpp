// FUNC_NAME: TNLConnection::checkAndSendReliablePacket
void TNLConnection::checkAndSendReliablePacket() {
    // this+0x10 -> pointer to ReliableBuffer (struct with fields at +0x20 and +0x24)
    uint32_t* buffer = *(uint32_t**)(this + 0x10);
    uint32_t currentCount = *(uint32_t*)(buffer + 0x20);  // +0x20: number of outstanding reliable packets
    uint32_t maxCount = *(uint32_t*)(buffer + 0x24);      // +0x24: max allowed outstanding

    if (currentCount <= maxCount) {
        // Room to queue another reliable packet
        FUN_00627360(); // likely builds/queues the packet
    }

    // Always attempt to flush/send the buffer
    uint32_t temp; // stack placeholder (actual usage unknown)
    FUN_00636910(&temp); // send/flush call with local buffer reference
}
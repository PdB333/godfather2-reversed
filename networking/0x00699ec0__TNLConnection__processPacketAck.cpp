// FUNC_NAME: TNLConnection::processPacketAck
uint TNLConnection::processPacketAck(uint packetFlags) {
    int* slotPtr = (int*)getPacketSlot(&packetFlags, packetFlags);
    if (*slotPtr == this->mExpectedSeq) { // +0x04: expected acknowledge sequence number
        packetFlags &= 0xFFFFFF00; // Clear low byte: mark as acknowledged
    } else {
        markPacketLost(*slotPtr + 0x20); // +0x20: slot index or timeout data
        packetFlags = (packetFlags & 0xFFFFFF00) | 0x01; // Set low byte: mark for retransmit
    }
    return packetFlags & 0xFF;
}
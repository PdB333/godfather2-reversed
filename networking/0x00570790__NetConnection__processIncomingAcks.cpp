// FUNC_NAME: NetConnection::processIncomingAcks
void NetConnection::processIncomingAcks(void *packetWindow) {
    int entryCount = this->ackEntryCount; // +0x24
    for (int i = 0; i < entryCount; ++i) {
        uint32_t *entry = this->ackEntries[i]; // +0x28: array of pointer to {seq, ackBits}
        applyAckEntry(packetWindow, entry[0], entry[1]); // FUN_00573200
    }
    if (this->ackFlags != 0) { // +0x34
        applyAckBlock(packetWindow, this->ackBlockParam, this->ackFlags); // FUN_005732d0 // +0x38, +0x34
    }
    if (*(uint32_t *)((uintptr_t)packetWindow + 0x34) < this->maxReceivedSeq) { // +0x20
        *(uint32_t *)((uintptr_t)packetWindow + 0x34) = this->maxReceivedSeq;
    }
}
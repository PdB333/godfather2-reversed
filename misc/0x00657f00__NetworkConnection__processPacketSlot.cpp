// FUNC_NAME: NetworkConnection::processPacketSlot
int NetworkConnection::processPacketSlot(int slotIndex, int unused, int expectedResult, uint param4) {
    // +0x04: uint32 m_sequenceOrAck (network byte order)
    uint localAck = ntohl(*(uint32*)(this + 4));
    uint localSeq  = ntohl(*(uint32*)(this + 4)); // same field, but passed by pointer for potential modification
    int result = FUN_0065d220(DAT_0122355c, slotIndex, &localSeq, param4);
    if (result == expectedResult) {
        return 2;
    }
    return result;
}
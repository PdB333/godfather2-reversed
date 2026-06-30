// FUNC_NAME: TNLConnection::updateOutgoingAckBlock

void __thiscall TNLConnection::updateOutgoingAckBlock(int *this, uint ackStartSeq, uint ackCount)
{
    // this[6] = m_outgoingBufferWriteIndex, this[7] = m_outgoingBufferReadIndex
    // Check if there is a pending packet in the send buffer
    if (this[7] < this[6]) {
        // Calculate pointer to packet header word within the packet pool.
        // Structure: this[0] = m_packetPool (pointer to pool structure)
        // Pool +0x0C = pointer to allocated packet buffer array
        // Each packet header is 4 bytes, indexed by this[6] (write index)
        uint *packetHeaderPtr = (uint *)(*(int *)(this[0] + 0xC) - 4 + this[6] * 4);
        uint header = *packetHeaderPtr;

        // Check packet type (low 6 bits) is 3 (ReliableOrdered or similar)
        if (((header & 0x3F) == 3) &&
            // Top byte is sequence number of this packet, must be <= ackStartSeq
            ((header >> 24) <= ackStartSeq) &&
            // Bits 15-23 are the current ack count, we can only increase it by one
            (ackStartSeq <= ((header >> 15) & 0x1FF) + 1))
        {
            uint currentAck = (header >> 15) & 0x1FF;
            uint newAck = ackStartSeq + ackCount - 1;

            if (newAck <= currentAck) {
                return; // No need to update
            }

            // Replace bits 15-23 with new ack count
            *packetHeaderPtr = ((newAck << 15) ^ header) & 0xFF8000 ^ header;
            return;
        }
    }

    // No suitable existing packet – construct and send a new ack packet immediately
    // Build header: type=3, seq in bits 24-31, ack count in bits 15-23
    uint newHeader = ((ackStartSeq + ackCount - 1) << 15) | (ackStartSeq << 24) | 3;
    // this[3] = m_connectionEndpoint, +8 = some address field (e.g., socket or remote address)
    FUN_006438e0(newHeader, *(int *)(this[3] + 8));
}
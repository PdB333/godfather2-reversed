// FUNC_NAME: TNLConnection::readPacket
// Address: 0x00622110
// This function reads a packet from the TNL connection's receive buffer, handling sequence numbers and possible fragmentation.
// param_1: this pointer (TNLConnection*)
// param_2: output buffer (uint32*)
// param_3: pointer to sequence number (uint32*)
// param_4: optional validation pointer (should be this or null)
// param_5: pointer to a packet buffer descriptor (likely current chunk)
// Returns: pointer to param_2 with the read data

uint32* TNLConnection::readPacket(TNLConnection* this, uint32* outBuffer, uint32* seqNum, void* validationPtr, PacketBuffer* bufferDesc)
{
    char cVar1;
    uint32* puVar2;
    bool bVar3;
    int local_c;
    int local_8;

    // If connection is disconnected, just copy the packet as-is (flag 1 = reliable?)
    if (*(int*)(this + 0x20) == 0) {
        readPacketData(this, outBuffer, 1, seqNum);
        return outBuffer;
    }

    // Get the current receive buffer descriptor
    local_8 = **(int**)(this + 0x1c);

    // Validation: param_4 should be either null or this pointer
    if ((validationPtr == 0) || (validationPtr != this)) {
        debugAssert(); // FUN_00b97aea - likely assertion failure
    }

    // Check if bufferDesc matches the current receive buffer
    if (bufferDesc == (PacketBuffer*)local_8) {
        // If the sequence number is less than the buffer's stored sequence, we need to copy the packet
        if (*seqNum < *(uint32*)(bufferDesc + 0xc)) {
            readPacketData(this, outBuffer, 1, seqNum);
            return outBuffer;
        }
    }
    else {
        // Re-read the receive buffer pointer (might have changed)
        local_8 = *(int*)(this + 0x1c);
        if ((validationPtr == 0) || (validationPtr != this)) {
            debugAssert();
        }
        if (bufferDesc == (PacketBuffer*)local_8) {
            // Check if the sequence number is beyond the buffer's stored sequence
            if (*(uint32*)(*(int*)(*(int*)(this + 0x1c) + 8) + 0xc) < *seqNum) {
                readPacketData(this, outBuffer, 0, seqNum);
                return outBuffer;
            }
        }
        else {
            // Compare sequence numbers
            bVar3 = *(uint32*)(bufferDesc + 0xc) < *seqNum;
            if (*seqNum < *(uint32*)(bufferDesc + 0xc)) {
                unknownFunction1(); // FUN_006242f0 - likely some sequence adjustment
                if (*(uint32*)(bufferDesc + 0xc) < *seqNum) {
                    // Check if the packet is fragmented (offset +0x25 in a sub-structure)
                    if (*(char*)(*(int*)(bufferDesc + 8) + 0x25) == '\0') {
                        readPacketData(this, outBuffer, 1, seqNum);
                        return outBuffer;
                    }
                    readPacketData(this, outBuffer, 0, seqNum);
                    return outBuffer;
                }
                bVar3 = *(uint32*)(bufferDesc + 0xc) < *seqNum;
            }
            if (bVar3) {
                local_8 = *(int*)(this + 0x1c);
                local_c = (int)this;
                unknownFunction2(); // FUN_00623fa0 - maybe advance buffer?
                cVar1 = checkPacketAvailable(); // FUN_006229f0 - returns true if packet available?
                if ((cVar1 != '\0') || (*seqNum < *(uint32*)(bufferDesc + 0xc))) {
                    if (*(char*)(*(int*)(bufferDesc + 8) + 0x25) == '\0') {
                        readPacketData(this, outBuffer, 1, seqNum);
                        return outBuffer;
                    }
                    readPacketData(this, outBuffer, 0, seqNum);
                    return outBuffer;
                }
            }
        }
    }

    // If we get here, we need to copy the actual packet data from the buffer
    puVar2 = getPacketDataPointer(this, &local_c, seqNum); // FUN_00622aa0
    *outBuffer = *puVar2;
    outBuffer[1] = puVar2[1];
    return outBuffer;
}
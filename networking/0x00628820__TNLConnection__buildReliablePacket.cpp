// FUNC_NAME: TNLConnection::buildReliablePacket

int __thiscall TNLConnection::buildReliablePacket(int this, int sequenceDelta)
{
    int slotIndex;
    int result;
    unsigned int currentCount;
    unsigned int capacity;
    int* pData;
    int* pOld;
    int* pWrite;
    int numPackets;

    // Check if sequenceDelta is within [-9999, 0] range (unsigned trick)
    // This adjusts the delta to point to a past or current position in the buffer
    if ((unsigned int)(sequenceDelta + 9999) < 10000) {
        sequenceDelta = ((*(int*)(this + 0x8) - *(int*)(this + 0xc)) >> 3) + 1 + sequenceDelta;
    }

    // Check if buffer is full: capacity <= count
    // Buffer header at this+0x10 has capacity at +0x20 and count at +0x24
    capacity = *(uint*)(*(int*)(this + 0x10) + 0x20);
    currentCount = *(uint*)(*(int*)(this + 0x10) + 0x24);
    if (capacity <= currentCount) {
        flushBuffer(this); // FUN_00627360
    }

    // Write a packet of type 4 (likely a control or reliable marker)
    pWrite = *(int**)(this + 0x8);   // +0x8: current write pointer
    *pWrite = 4;                     // packet type
    pWrite[1] = getSequenceNumber(); // FUN_00638920 – assign sequence number
    *(int*)(this + 0x8) = (int)pWrite + 8; // advance write pointer by 8 bytes

    advanceWritePointer(this); // FUN_00625e70 – probably updates count

    // Try to allocate a stable slot for pending tracking
    slotIndex = tryAllocateSlot(this); // FUN_00628380 – returns slot index or -1
    if (slotIndex < 0) {
        // Allocation failed; handle by possibly overwriting an old pending packet
        handleAllocationFailure(this); // FUN_00628430

        // Copy from buffer at offset based on sequenceDelta
        if (sequenceDelta < 1) {
            pOld = (int*)getBufferBase(this); // FUN_00625430 – start of buffer
        } else {
            pOld = (int*)(*(int*)(this + 0xc) + -8 + sequenceDelta * 8); // +0xc: end of buffer
        }
        pWrite = *(int**)(this + 0x8);
        *pWrite = *pOld;
        pWrite[1] = pOld[1];
        *(int*)(this + 0x8) = (int)pWrite + 8;

        advanceWritePointer(this); // FUN_00625e70

        slotIndex = tryAllocateSlot(this); // FUN_00628380
        if (slotIndex < 0) {
            // Still failing; start flushing unacknowledged packets
            numPackets = 1;
            while (true) {
                // Get next pending packet from the outgoing queue
                if (sequenceDelta < 1) {
                    getBufferBase(this); // FUN_00625430 – just fetch (return ignored)
                }
                pData = (int*)getNextPendingPacket(this); // FUN_00637f10 – pointer to 8-byte entry
                pWrite = *(int**)(this + 0x8);
                *pWrite = *pData;
                pWrite[1] = pData[1];
                *(int*)(this + 0x8) = (int)pWrite + 8;

                int oldWrite = *(int*)(this + 0x8);
                int ackStatus = isPacketAcknowledged(this); // FUN_00625740
                *(int*)(this + 0x8) = oldWrite - 8; // revert write if ack? Actually we removed the packet

                if (ackStatus == 0) {
                    break; // stop at the first unacknowledged packet
                }
                numPackets += 1;
            }
            slotIndex = numPackets - 1;
        }
    }
    return slotIndex;
}
//FUNC_NAME: PacketBuffer::readPacket
// Function address: 0x0063ca10
// Role: Reads a packet from the internal buffer by sequence index. Handles reliable/unreliable packet types and buffer management.

int PacketBuffer::readPacket(int sequenceIndex)
{
    int* packetPtr;
    int* currentReadPtr;
    int* tempPtr;
    int packetType;
    int result;

    // If sequenceIndex < 1, fetch the next packet from the network layer
    if (sequenceIndex < 1)
    {
        packetPtr = (int*)fetchNextPacket(); // FUN_00625430
        goto checkPacket;
    }
    else
    {
        // Calculate pointer to the packet at the given sequence index
        // Buffer grows downward: base at m_bufferBase, top at m_bufferBase - 8
        packetPtr = (int*)(*(int*)(this + 0x0C) - 8 + sequenceIndex * 8);
        // If the requested packet is beyond the current read pointer, fetch more
        if (packetPtr < *(int**)(this + 0x08))
            goto checkPacket;
    }

    // No packet available, advance read pointer (pop empty?)
    advanceReadPointer(); // FUN_00625ca0
    goto end;

checkPacket:
    if ((packetPtr == (int*)0x0) || (*packetPtr == -1))
        goto advanceAndEnd;

    packetType = *packetPtr;
    if (packetType == 7)
    {
        // Reliable packet type
        if (isReliablePacket() == 0) // FUN_00625f80
        {
            advanceReadPointer(); // FUN_00625ca0
        }
        else
        {
            processReliablePacket(); // FUN_00625e70
            currentReadPtr = (int*)(*(int*)(this + 0x08) - 8);
            // Check if the packet type is valid (not 3 or 4)
            if ((currentReadPtr == (int*)0x0) || (*currentReadPtr != 4 && *currentReadPtr != 3))
            {
                *(int**)(this + 0x08) = currentReadPtr;
                advanceReadPointer(); // FUN_00625ca0
            }
        }
    }
    else if (packetType == 5)
    {
        // Unreliable packet type
        processUnreliablePacket(); // FUN_00625700
        processReliablePacket(); // FUN_00625e70
        currentReadPtr = (int*)(*(int*)(this + 0x08) - 8);
        if ((currentReadPtr == (int*)0x0) || (*currentReadPtr != 4 && *currentReadPtr != 3))
        {
            *(int**)(this + 0x08) = currentReadPtr;
            advanceReadPointer(); // FUN_00625ca0
        }
        else
        {
            advanceReadPointer(); // FUN_00625ca0
            // Shift buffer entries to remove the processed packet
            int* src = *(int**)(this + 0x08);
            int* dst = src;
            for (; src - 4 < dst; dst -= 2)
            {
                *dst = dst[-2];
                dst[1] = dst[-1];
            }
            // Copy the first two entries to the end (circular shift)
            int* first = *(int**)(this + 0x08);
            src[-4] = *first;
            src[-3] = first[1];
            // Check buffer capacity and possibly flush
            if (*(uint*)(*(int*)(this + 0x10) + 0x20) <= *(uint*)(*(int*)(this + 0x10) + 0x24))
            {
                checkBufferOverflow(); // FUN_00627360
            }
            resetBuffer(); // FUN_006343b0
            *(int*)(this + 0x08) = *(int*)(this + 0x08) - 8;
        }
    }
    else
    {
        advanceReadPointer(); // FUN_00625ca0
    }

end:
    result = *(int*)(this + 0x08);
    if ((int*)(result - 8) == (int*)0x0)
        return 0;
    if (*(int*)(result - 8) == 4)
        return *(int*)(result - 4) + 0x10;
    if (isValidPacket() != 0) // FUN_00633990
        return *(int*)(result - 4) + 0x10;
    else
        result = 0;
    if (*(uint*)(*(int*)(this + 0x10) + 0x20) <= *(uint*)(*(int*)(this + 0x10) + 0x24))
    {
        checkBufferOverflow(); // FUN_00627360
    }
    return result;
}
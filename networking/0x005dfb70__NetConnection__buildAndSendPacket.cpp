// FUNC_NAME: NetConnection::buildAndSendPacket
// Address: 0x005dfb70
undefined4* NetConnection::buildAndSendPacket(int thisPtr, undefined4* outputPacket, uint* sequenceNumber, int considerSequence, int remoteSequence)
{
    char cVar1;
    undefined4* puVar2;
    bool bVar3;
    int someState;
    int packetQueuePtr;

    // If the connection is not active (mIsConnected at +0x20 == 0), send immediately as reliable
    if (*(int*)(thisPtr + 0x20) == 0) {
        sendPacketInternal(thisPtr, outputPacket, 1, sequenceNumber);
        return outputPacket;
    }

    // Get the head of the packet queue (stored as pointer to head node at +0x1c)
    packetQueuePtr = **(int**)(thisPtr + 0x1c);

    // Safety check: if considerSequence is provided but does not point to this connection, assert
    if ((considerSequence == 0) || (considerSequence != thisPtr)) {
        lockCriticalSection();
    }

    // If the remote sequence matches the current queue head, check if enough space in window
    if (remoteSequence == packetQueuePtr) {
        if (*sequenceNumber < *(uint*)(packetQueuePtr + 0xc)) {
            sendPacketInternal(thisPtr, outputPacket, 1, sequenceNumber);
            return outputPacket;
        }
    }
    else {
        // Reload queue head (maybe due to pointer indirection? check again)
        packetQueuePtr = *(int*)(thisPtr + 0x1c);
        if ((considerSequence == 0) || (considerSequence != thisPtr)) {
            lockCriticalSection();
        }

        if (remoteSequence == packetQueuePtr) {
            // Check the remote sequence from queue head's next pointer? (pointer at +0x8, then +0xc)
            if (*(uint*)(*(int*)(*(int*)(thisPtr + 0x1c) + 8) + 0xc) < *sequenceNumber) {
                sendPacketInternal(thisPtr, outputPacket, 0, sequenceNumber);
                return outputPacket;
            }
        }
        else {
            // Compare the remote sequence's last received with current sequence number
            bVar3 = *(uint*)(remoteSequence + 0xc) < *sequenceNumber;

            if (*sequenceNumber < *(uint*)(remoteSequence + 0xc)) {
                checkSequenceWindow();
                if (*(uint*)(remoteSequence + 0xc) < *sequenceNumber) {
                    // Check if packet is ready based on some flag at +0x15 of the referenced object
                    if (*(char*)(*(int*)(remoteSequence + 8) + 0x15) == '\0') {
                        sendPacketInternal(thisPtr, outputPacket, 1, sequenceNumber);
                        return outputPacket;
                    }
                    sendPacketInternal(thisPtr, outputPacket, 0, sequenceNumber);
                    return outputPacket;
                }
                bVar3 = *(uint*)(remoteSequence + 0xc) < *sequenceNumber;
            }

            if (bVar3) {
                // Prepare state and check packet readiness
                packetQueuePtr = *(int*)(thisPtr + 0x1c);
                someState = thisPtr;
                updateSequenceState();
                cVar1 = isPacketReady();

                if ((cVar1 != '\0') || (*sequenceNumber < *(uint*)(remoteSequence + 0xc))) {
                    if (*(char*)(*(int*)(remoteSequence + 8) + 0x15) == '\0') {
                        sendPacketInternal(thisPtr, outputPacket, 1, sequenceNumber);
                        return outputPacket;
                    }
                    sendPacketInternal(thisPtr, outputPacket, 0, sequenceNumber);
                    return outputPacket;
                }
            }
        }
    }

    // Build the packet header and copy it to the output buffer
    puVar2 = (undefined4*)buildPacketHeader(thisPtr, &someState, sequenceNumber);
    *outputPacket = *puVar2;
    outputPacket[1] = puVar2[1];
    return outputPacket;
}
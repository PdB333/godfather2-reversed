// FUNC_NAME: NetConnection::processReliableSequence
int NetConnection::processReliableSequence(int* bufferContext, int* segmentState, PacketHeader* packetHeader, int extraFlags) {
    // param_3[2] is packetHeader->type, check if it's invalid type 1 -> return -3
    if (packetHeader->type == 1) {
        return -3;
    }

    // segmentState + 8 flags whether this is the first segment (init phase)
    if (*(int*)(segmentState + 8) == 1) {
        // Allocate 256-byte buffer for packet data (4 x 64)
        void* dataBuffer = _calloc(4, 0x40);
        if (dataBuffer == 0) {
            return -2;
        }

        // Initialize local buffer descriptor
        BufferDescriptor localDesc;
        localDesc.status = 0;            // +0x00
        localDesc.maxPayload = 0x40;     // +0x04, default payload size (64)
        localDesc.usedSize = 0;          // +0x08

        // Serialize packet header into descriptor
        int result = serializePacketHeader(packetHeader, &localDesc);
        if (result != 0) {
            releaseBuffer(&localDesc, (char*)0, 0); // cleanup
            return result;
        }

        result = prepareDataBuffer();
        if (result != 0) {
            freeBufferContext(); // FUN_00665b40
            return result;
        }

        result = compressPayload(); // FUN_006657a0
        if (result != 0) {
            releaseBuffer(&localDesc, (char*)0, 0);
            return result;
        }

        // Recursive call to process next segment in sequence
        result = processReliableSequence(&localDesc, (int*)bufferContext, packetHeader, extraFlags);
        releaseBuffer(&localDesc, (char*)0, 0);
        return result;
    } else {
        // Subsequent segments: get sequence info and decide path
        int sendSeq = getSendSequence();     // FUN_00666800
        int ackCount = getReceivedAck();      // FUN_0066a440
        int ackVal = ackCount * 2;            // some scaling

        // Check conditions to use direct send or delayed send
        if ((packetHeader->sequence < 1) || ((*(byte*)packetHeader->flags & 1) == 0)) {
            if (ackVal == 0) {
                // Fast path: send immediately
                return sendPacketDirect(bufferContext, segmentState, packetHeader, extraFlags);
            }
        }
        // Delayed / retransmission path
        return sendPacketDelayed(bufferContext, segmentState, packetHeader, extraFlags, ackVal);
    }
}
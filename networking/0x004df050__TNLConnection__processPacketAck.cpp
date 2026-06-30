// FUNC_NAME: TNLConnection::processPacketAck
bool TNLConnection::processPacketAck(int ackSequence) {
    GlobalPacketState* packetState = GetGlobalPacketState(); // FUN_004e0d30 - returns packet state pointer
    int currentAckSeq = 0;
    if (packetState != nullptr) {
        currentAckSeq = packetState->lastAckedSequence; // field at offset 0
    }

    if (currentAckSeq == ackSequence) {
        // Acknowledged sequence matches current, reset or update
        EnterPacketLock(); // FUN_004e0c20
        PacketHistory* history = GetPacketHistory(); // FUN_004e0f60 - returns history pointer
        if (history != nullptr) {
            if (history->lastRemovedSequence == ackSequence) {
                DynamicBuffer* buf = history->buffer; // history->buffer (pointer to buf), +0x4
                if (buf != nullptr) {
                    if (buf->count != 0) { // buf->count at +0x4
                        // Pop the top element from the buffer
                        int* data = buf->data; // buf->data at +0x0
                        history->lastRemovedSequence = data[buf->count - 1]; // data[-4 + count*4]? -> last element
                        buf->count--;
                        return true;
                    }
                    if (buf != nullptr) {
                        ClearPacketBuffer(); // FUN_004df150 - frees the buffer
                        history->buffer->count = 0; // actually reset count via pointer?
                    }
                }
                LeavePacketLock(); // FUN_004e0a20
                return true;
            }

            // Search for ackSequence in history buffer
            DynamicBuffer* buf = history->buffer; // note: code path after first if
            if (buf != nullptr && buf->count > 0) {
                int* data = buf->data;
                int index = buf->count;
                while (true) {
                    index--;
                    if (data[index] == ackSequence) {
                        break;
                    }
                    if (index <= 0) {
                        return true;
                    }
                }
                // Found at index, remove it from history (probably shift elements)
                RemoveFromHistoryAtIndex(index); // FUN_004e14d0
            }
        }
        return true;
    }
    return false;
}
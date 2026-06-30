// FUNC_NAME: PacketQueue::processNextPacket

int PacketQueue::processNextPacket() {
    int* headPtr = *(int**)(this + 0xC);          // +0xC: pointer to front element
    int* tailPtr = *(int**)(this + 0x8);          // +0x8: pointer to next write slot
    int* bufferInfo = *(int**)(this + 0x10);      // +0x10: pointer to buffer descriptor (has +0x20, +0x24 counters)

    // Check if queue is non‑empty and head is valid
    if (headPtr < tailPtr && headPtr != nullptr && *headPtr > 0) {
        int packetDataSize;
        if (*headPtr == 4) {
            // Special packet type 4: data size computed directly
            packetDataSize = headPtr[1] + 0x10;          // +0x10 = offset to payload
        } else {
            packetDataSize = getPacketDataSize(this);     // FUN_00633990 – size from header
            if (packetDataSize == 0) {
                packetDataSize = 0;
            } else {
                packetDataSize = headPtr[1] + 0x10;
            }
            // Check if buffer underflow condition (counters at +0x20, +0x24)
            if (*(uint*)(bufferInfo + 0x20) <= *(uint*)(bufferInfo + 0x24)) {
                flushBuffer();                           // FUN_00627360 – handle overflow
            }
        }
        if (packetDataSize != 0) {
            goto processPacket;                         // jump to the dispatch/process step
        }
        // Invalid packet size – log error
        debugLog("string_00e2a8ac");                    // FUN_00627ac0 – error message
    } else {
        // No packet to process
        packetDataSize = 0;
processPacket:
        if (!dispatchPacket(packetDataSize)) {          // FUN_006290c0 – dispatch to handler
            return 1;                                   // processing failed, keep packet
        }
    }

    // Remove the front packet and shift the queue
    **(int**)(this + 0x8) = 0;                         // Clear the old tail slot
    *(int*)(this + 0x8) = (int)tailPtr + 8;            // Advance tail pointer by 8 bytes

    // Shift remaining entries left by one slot (each entry is 8 bytes)
    int** newTail = *(int***)(this + 0x8);             // Updated tail pointer
    for (int** src = newTail; (int**)((char*)newTail - 4) < src; src = (int**)((char*)src - 2)) {
        *src = src[-2];
        src[1] = src[-1];
    }
    // Copy the last two ints from the new tail to the freed slot
    newTail = *(int***)(this + 0x8);
    newTail[-4] = *newTail;
    newTail[-3] = newTail[1];

    return 2;                                           // packet removed successfully
}
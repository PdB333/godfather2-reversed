// FUNC_NAME: NetPacketBuffer::popPacket

int NetPacketBuffer::popPacket() {
    // this: param_1
    int* readPtr = *(int**)(this + 0x0C); // +0x0C: m_readPtr (pointer to current packet)
    int* writePtr = *(int**)(this + 0x08); // +0x08: m_writePtr (pointer past last packet)

    // Check if there is a packet available
    if (readPtr < writePtr && readPtr != nullptr && *readPtr > 0) {
        int packetType = *readPtr;
        int* packetData = nullptr;

        if (packetType == 4) {
            // Type 4 packet: data offset is at header+4+0x10
            packetData = (int*)(readPtr[1] + 0x10);
        } else {
            // Other packet types: validate and possibly skip
            int result = validatePacket(this); // FUN_00633990
            if (result != 0) {
                packetData = (int*)(readPtr[1] + 0x10);
            } else {
                packetData = nullptr;
            }

            // Check buffer overflow condition
            int* bufferMeta = *(int**)(this + 0x10); // +0x10: m_bufferMeta (pointer to buffer descriptor)
            if (*(uint*)(bufferMeta + 0x20) <= *(uint*)(bufferMeta + 0x24)) {
                handleOverflow(); // FUN_00627360
            }
        }

        if (packetData != nullptr) {
            goto processPacket;
        }
        // Log error: no valid packet data
        logError("string"); // FUN_00627ac0(PTR_s_string_00e2a8ac)
    } else {
        packetData = nullptr;
    }

processPacket:
    int* writePtrBefore = *(int**)(this + 0x08);
    int* readPtrBefore = *(int**)(this + 0x0C);
    int isValid = checkPacketValidity(packetData); // FUN_006290c0

    if (isValid == 0) {
        // Pop the packet from the buffer
        removePacket(this, *(int*)(this + 0x08) - 8, 0xFFFFFFFF); // FUN_006362d0
        // Return number of packets removed (size difference / 8)
        return (*(int*)(this + 0x08) - *(int*)(this + 0x0C) >> 3) - (writePtrBefore - readPtrBefore >> 3);
    }

    // Packet invalid, fallback to allocator
    return allocateFallback(); // FUN_006338a0
}
// FUNC_NAME: NetChannel::buildPacket
/// @brief Builds a network packet header and either queues it for sending or fills additional data.
/// @return Returns 0 on failure (if queue succeeded?) or a vtable offset pointer as int.
int NetChannel::buildPacket()
{
    uint32_t seqNum;
    uint32_t* packetHeader;
    NetChannel* channel;
    int result;

    // Virtual function call at vtable offset 0xA4: probably getNextSequenceNumber()
    // It takes a pointer to a uint32_t to fill with the sequence number.
    (this->vtable->getSequenceNumber)(&seqNum);

    // +0x1C: pointer to the associated channel object
    channel = *(NetChannel**)((char*)this + 0x1C);

    if (channel != nullptr) {
        // +0x10 in channel: pointer to the packet buffer
        packetHeader = (uint32_t*)*(uint32_t*)((char*)channel + 0x10);
    } else {
        packetHeader = nullptr;
    }

    // Build the packet header in the buffer
    // +0x20: pointer to the data payload (stored at this+0x24)
    packetHeader[0x20/4] = (uint32_t)((char*)this + 0x24);
    // +0x24 and +0x28: sequence number (maybe high/low parts)
    packetHeader[0x24/4] = seqNum;
    packetHeader[0x28/4] = seqNum;
    // +0x2C: reserved, zero
    packetHeader[0x2C/4] = 0;
    // +0x48: flag byte (probably "has header")
    *(uint8_t*)((char*)packetHeader + 0x48) = 1;

    // Re-read channel pointer
    channel = *(NetChannel**)((char*)this + 0x1C);

    // Check channel's pending flag at +0x08
    if (*(uint32_t*)((char*)channel + 0x08) != 0) {
        // Channel has pending data: queue this packet for later sending
        // Pass the payload buffer address (this+0x24) to the send function
        int* payloadBuffer = (int*)((char*)this + 0x24);
        return FUN_009f1820(payloadBuffer, 0); // returns 0 or error code
    }

    // No pending data: copy static vtable constants into channel's upper region
    uint32_t vtableBase = *(uint32_t*)this; // vtable pointer
    // +0x100, +0x104, +0x108 in vtable: some constant data (timestamps? keys?)
    // +0x100 in vtable: first dword
    *(uint32_t*)((char*)channel + 0xD0) = *(uint32_t*)(vtableBase + 0x100);
    *(uint32_t*)((char*)channel + 0xD4) = *(uint32_t*)(vtableBase + 0x104);
    *(uint32_t*)((char*)channel + 0xD8) = *(uint32_t*)(vtableBase + 0x108);
    // +0xDC: fixed global constant (e.g., a magic number or CRC seed)
    *(uint32_t*)((char*)channel + 0xDC) = DAT_00e2b1a4;

    // Return the address of the vtable constant region (cast to int)
    return (int)(vtableBase + 0x100);
}
// FUNC_NAME: TNLConnection::buildReliablePacket
// Address: 0x00636050
// Builds a reliable packet from a descriptor, handling buffer space and sequence numbers.

struct PacketDescriptor {
    int type;      // +0x00: Packet type (expected 6 for reliable)
    void* dataPtr; // +0x04: Pointer to data structure
};

struct ReliablePacketData {
    char    unknown0[0x45]; // +0x00-0x44
    uint8_t flags;          // +0x45: Some flag
    uint8_t hasData;        // +0x46: Boolean if data present
    uint8_t bitCount;       // +0x47: Number of bits for data length? (used for alignment)
    uint32_t payload;       // +0x48: Payload data (likely a pointer or size)
};

// Class TNLConnection contains a packet buffer for sending.
class TNLConnection {
    // Packet buffer fields
    int32_t mBufferBase;          // +0x08: Base address of the send buffer
    int32_t mCurrentWritePos;     // +0x0C: Current write position (address)
    int32_t mWriteOffset;         // +0x14: Offset from base where next packet is written
    int32_t mBufferEnd;           // +0x18: End of buffer (address)
    int32_t mRemoteSequence;      // +0x1C: Remote sequence number or packet size base
    int32_t mBufferLimit;         // +0x24: Limit (address) for buffer overflow check
    uint16_t mPacketSize;         // +0x2C: Maximum packet size (0x1000 = 4096)
    uint8_t  mFlags;              // +0x30: Bit 0 = send acknowledgment

    // Helper functions (callees we rename)
    int32_t resolvePacketType(PacketDescriptor* desc);
    int32_t allocatePacketSlot();                 // FUN_00635a80
    void    checkBufferSpace();                   // FUN_00635c10
    void    flushSendBuffer();                    // FUN_00633920
    void    writeBits(void* src, int numBits);    // FUN_00635dc0
    void    signalOverflow();                     // FUN_00635c70
    void    setPacketSequence(int seq);           // FUN_00635d00

public:
    int32_t buildReliablePacket(PacketDescriptor* desc);
};

// Reconstructed implementation
int32_t TNLConnection::buildReliablePacket(PacketDescriptor* desc) {
    int32_t retVal;
    int32_t* packetDataPtr;
    int32_t* writePtr;
    int32_t currentWriteAddr;
    int32_t remoteBase;

    // Get the remote sequence number base from +0x1C
    remoteBase = *(int32_t*)((uint8_t*)this + 0x1C);

    // If packet type is not 6 (reliable), try to resolve it
    if (desc->type != 6) {
        desc = (PacketDescriptor*)resolvePacketType(desc);
    }

    // Check if the next write offset would overflow the buffer
    // +0x14 is the current write offset, +0x24 is the buffer limit
    if (*(int32_t*)((uint8_t*)this + 0x14) + 0x18 == *(int32_t*)((uint8_t*)this + 0x24)) {
        // If packet size exceeds maximum (0x1000), allocate a new slot
        if (*(uint16_t*)((uint8_t*)this + 0x2C) > 0x1000) {
            retVal = allocatePacketSlot();
            return retVal;
        }
        // Otherwise, check buffer space and possibly flush
        checkBufferSpace();
        if (*(uint16_t*)((uint8_t*)this + 0x2C) > 0x1000) {
            flushSendBuffer();
        }
    }

    // Check if the data structure has payload (offset +0x46)
    if (*(uint8_t*)((uint8_t*)desc->dataPtr + 0x46) != 0) {
        // Check if there's enough space: bufferEnd - base must be at least 0xA0 (160 bytes)
        if (*(int32_t*)((uint8_t*)this + 0x18) - *(int32_t*)((uint8_t*)this + 0x08) < 0xA1) {
            signalOverflow();
        }

        // Advance write offset by 0x18 (24 bytes) for packet header
        *(int32_t*)((uint8_t*)this + 0x14) = *(int32_t*)((uint8_t*)this + 0x14) + 0x18;

        // Write packet header at new offset
        writePtr = *(int32_t**)((uint8_t*)this + 0x14);
        *writePtr = (int32_t)desc + remoteBase + (8 - remoteBase);

        // Update current write position to the value just written
        currentWriteAddr = **(int32_t**)((uint8_t*)this + 0x14);
        *(int32_t*)((uint8_t*)this + 0x0C) = currentWriteAddr;

        // Set data pointer to base + 0xA0 (payload offset)
        writePtr[1] = *(int32_t*)((uint8_t*)this + 0x08) + 0xA0;
        // Mark packet as used (slot count = 1)
        writePtr[2] = 1;

        // If send acknowledgment flag is set, call setPacketSequence
        if ((*(uint8_t*)((uint8_t*)this + 0x30) & 1) != 0) {
            setPacketSequence(0xFFFFFFFF);
        }

        // Calculate return value: base + (packet size * -8) via virtual call
        retVal = (**(code**)(*(int32_t*)(*(int32_t*)(*(int32_t*)((uint8_t*)this + 0x0C) - 4) + 0x0C)))();
        return *(int32_t*)((uint8_t*)this + 0x08) + retVal * -8;
    }

    // If no payload data, handle differently
    int32_t dataPtrVal = *(int32_t*)((uint8_t*)desc->dataPtr + 0x0C);
    if (*(uint8_t*)(dataPtrVal + 0x46) != 0) {
        // Write bits from segment descriptor
        writeBits(*(uint8_t*)(dataPtrVal + 0x45), desc->dataPtr + 8); // note: desc + 2 ints = offset 8
    }

    // Check for buffer overflow again
    if (*(int32_t*)((uint8_t*)this + 0x18) - *(int32_t*)((uint8_t*)this + 0x08) <=
        (int32_t)((uint32_t)*(uint8_t*)(dataPtrVal + 0x47) * 8)) {
        signalOverflow();
    }

    // Advance write offset by packet header size
    *(int32_t*)((uint8_t*)this + 0x14) = *(int32_t*)((uint8_t*)this + 0x14) + 0x18;

    // Write header at new offset
    writePtr = *(int32_t**)((uint8_t*)this + 0x14);
    *writePtr = (int32_t)desc + remoteBase + (8 - remoteBase);
    currentWriteAddr = **(int32_t**)((uint8_t*)this + 0x14);
    *(int32_t*)((uint8_t*)this + 0x0C) = currentWriteAddr;

    // Compute payload length based on bitCount field
    writePtr[1] = currentWriteAddr + ((uint32_t)*(uint8_t*)(dataPtrVal + 0x47) * 8);
    writePtr[3] = *(int32_t*)(dataPtrVal + 0x0C); // some payload pointer
    writePtr[5] = 0;                               // zero fill
    writePtr[2] = 8;                               // alignment

    // Zero-fill gap between current write position and the computed end
    int32_t currentEnd = *(int32_t*)((uint8_t*)this + 0x08);
    if ((uint32_t)currentEnd < (uint32_t)writePtr[1]) {
        do {
            *(uint32_t*)currentEnd = 0;
            currentEnd += 8;
        } while ((uint32_t)currentEnd < (uint32_t)writePtr[1]);
    }

    // Update write position
    *(int32_t*)((uint8_t*)this + 0x08) = writePtr[1];
    return 0;
}
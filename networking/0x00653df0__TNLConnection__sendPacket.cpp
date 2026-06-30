// FUNC_NAME: TNLConnection::sendPacket
#include <cstdint>

// Global constants (from EA EARS engine)
const float kTimerDisabled = 0.0f; // DAT_00e2b05c
const double kDoubleTwoTo32 = 4294967296.0; // _DAT_00e44708
const double kTimerMultiplier = 0.001; // _DAT_00e448a8 (example: convert ms to s)

// Forward declarations of callees (defined elsewhere in the binary)
int32_t getRandomInt();
void encryptPacket(void* packet);
uint32_t sendDataChannel(uint32_t channelBase, uint32_t packetId, uint32_t dataSize, uint32_t flags);
void sendRawBuffer(uint32_t connectionBase, void* outputBuffer, void* packet, uint32_t bufferSize);

// TNLConnection::sendPacket
// Offsets:
// this+0xCC - float m_rateLimitTimer (rate limiting timer)
// this+0x124 - int32_t m_encryptFlag (non-zero if packet encryption is required)
// this+0x1A4 - uint32_t m_encryptContext (pointer to encryption context)
// this+0x100 - void* m_outBuffer (temporary output buffer for encrypted data)
// this+0xC8 - uint32_t m_outBufferSize (size of output buffer)

// Packet structure (passed in packetPtr)
// +0x0C - uint32_t m_packetId (packet sequence number)
// +0x18 - uint32_t m_dataSize (size of actual data)
// +0x1C - uint8_t[2] unused?
// +0x38 - uint8_t flags
// +0x34 - uint32_t checksum?
// +0x2C - uint32_t m_alignedSize (aligned size for encryption)
// +0x30 - uint32_t m_encryptedSize?

int32_t TNLConnection_sendPacket(void* packetPtr) // this in EDI, packetPtr in EAX
{
    float rateLimitTimer = *(float*)((uint8_t*)this + 0xCC);
    if (rateLimitTimer != kTimerDisabled)
    {
        int32_t randVal = getRandomInt();
        double randDouble = (double)randVal;
        if (randVal < 0)
            randDouble += kDoubleTwoTo32; // convert signed to unsigned double
        double scaled = randDouble * kTimerMultiplier;
        if (scaled < (double)rateLimitTimer)
            return 0; // rate limited: drop packet
    }

    if (*(int32_t*)((uint8_t*)this + 0x124) != 0) // encryption required
    {
        uint32_t originalSize = *(uint32_t*)((uint8_t*)packetPtr + 0x18);
        // Clear encryption-related fields in packet
        *(uint32_t*)((uint8_t*)packetPtr + 0x18) = 0;
        *(uint8_t*)((uint8_t*)packetPtr + 0x1C) = 0;
        *(uint8_t*)((uint8_t*)packetPtr + 0x1D) = 0;
        *(uint8_t*)((uint8_t*)packetPtr + 0x38) = 0;
        *(uint32_t*)((uint8_t*)packetPtr + 0x34) = 0;
        // Align size to next multiple of 8
        *(uint32_t*)((uint8_t*)packetPtr + 0x2C) = (originalSize + 7) & 0xFFFFFFF8;
        *(uint32_t*)((uint8_t*)packetPtr + 0x30) = 0;
        encryptPacket(packetPtr);
        return 0;
    }

    if (*(uint32_t*)((uint8_t*)this + 200) == 0) // no output buffer? send directly
    {
        uint32_t channelBase = *(uint32_t*)((uint8_t*)this + 0x1A4) + 0x5C;
        uint32_t packetId = *(uint32_t*)((uint8_t*)packetPtr + 0x0C);
        uint32_t dataSize = (*(uint32_t*)((uint8_t*)packetPtr + 0x18) + 7) >> 3; // size in 8-byte words
        return sendDataChannel(channelBase, packetId, dataSize, 0);
    }
    else // use internal output buffer
    {
        sendRawBuffer(*(uint32_t*)((uint8_t*)this + 0x1A4),
                      (void*)((uint8_t*)this + 0x100),
                      packetPtr,
                      *(uint32_t*)((uint8_t*)this + 200));
        return 0;
    }
}
// FUNC_NAME: NetConnection::sendPacket

// Function at 0x00653df0 - Sends a packet over the network connection
// Handles rate limiting, packet queueing, and raw sending.

#include <cstdint>

// Forward declarations
int getRandomInt(); // FUN_0065bf40 - provides a random integer (or possibly time-related value)
void resetPacketBuffer(PacketBuffer* buffer); // FUN_00653150 - resets/clears packet buffer
int sendBufferedPacket(void* bufferBase, uint32_t packetType, uint32_t alignedSize, int flags); // FUN_00658230 - sends a fully-formed packet
void queuePacketForSend(void* connectionBuffer, uint32_t headerOffset, PacketBuffer* packet, int queueSize); // FUN_00654f70 - queues a packet for later sending

// Global constants (from data section)
extern const float SEND_RATE_RESET; // DAT_00e2b05c - set to a specific value to bypass rate limit (e.g., zero)
extern const double NEGATIVE_ADJUST; // _DAT_00e44708 - adjustment for negative random values (e.g., 4294967296.0)
extern const double RATE_SCALE; // _DAT_00e448a8 - scaling factor for rate comparison

// Packet structure passed in EAX (this is the packet to send)
struct PacketBuffer {
    uint32_t packetType;       // +0x0C
    // ... remaining fields assumed layout:
    uint32_t size;             // +0x18
    uint8_t flags1;            // +0x1C
    uint8_t flags2;            // +0x1D
    uint32_t alignedSize;      // +0x2C (size rounded up to 8 bytes)
    uint32_t unk30;            // +0x30
    uint32_t unk34;            // +0x34
    uint8_t unk38;             // +0x38
    // Actual data follows
};

// Connection class (partial)
class NetConnection {
public:
    // Fields (offsets relative to this)
    float sendRate;            // +0xCC - rate limiter (time since last send or allowed interval)
    int pendingPacketFlag;     // +0x124 - non-zero if a packet is already pending
    int outgoingQueueSize;     // +0xC8 (200 decimal) - size of outgoing queue / number of pending fragments
    void* sendBuffer;          // +0x1A4 - pointer to a larger buffer (e.g., for building outgoing burst)
    uint8_t headerRegion[0x100]; // +0x100 - used as a destination for header in queuePacketForSend

    int sendPacket(PacketBuffer* packet);  // this function
};

int NetConnection::sendPacket(PacketBuffer* packet) {
    // Check if rate limiting is active (sendRate not equal to the reset sentinel)
    if (sendRate != SEND_RATE_RESET) {
        int randomVal = getRandomInt();
        double adjVal = (double)randomVal;
        if (randomVal < 0) {
            adjVal += NEGATIVE_ADJUST; // handle negative integers
        }
        // Compare rate scaled to sendRate; if scaled random value < sendRate, abort
        if (adjVal * RATE_SCALE < (double)sendRate) {
            return 0; // not allowed to send now
        }
    }

    // If a packet is already pending, we need to discard/override it
    if (pendingPacketFlag != 0) {
        int oldSize = packet->size;
        // Clear header fields and set aligned size
        packet->size = 0;
        packet->flags1 = 0;
        packet->flags2 = 0;
        packet->unk38 = 0;
        packet->unk34 = 0;
        packet->alignedSize = (oldSize + 7) & 0xFFFFFFF8; // align up to 8 bytes
        packet->unk30 = 0;
        resetPacketBuffer(packet);
        return 0;
    }

    // No pending packet: decide between raw send or queue
    if (outgoingQueueSize == 0) {
        // Send directly: buffer is at sendBuffer + 0x5C, use packet type, total size in 8-byte units, flags=0
        uint32_t bufAddr = reinterpret_cast<uint32_t>(sendBuffer) + 0x5C;
        uint32_t type = packet->packetType;
        uint32_t alignedUnits = (packet->size + 7) >> 3; // number of 8-byte words (rounded up)
        return sendBufferedPacket(reinterpret_cast<void*>(bufAddr), type, alignedUnits, 0);
    } else {
        // Queue the packet for later sending (has pending fragments)
        queuePacketForSend(sendBuffer, reinterpret_cast<uint32_t>(&headerRegion), packet, outgoingQueueSize);
        return 0;
    }
}
// FUNC_NAME: NetSession::buildPlayerPacket

// Function at 0x005e25f0: builds a reliable packet for a specific player slot (0-4).
// Uses EA EARS networking layer (TNLConnection derivative).
// Checks connection state, obtains a slot index, optionally generates a packet ID,
// and writes the packet data into a stream.

#include <cstdint>

// Forward declaration of internal functions
static uint32_t getSlotIndex(uint32_t param);
static bool isSlotOperationReady();
static uint32_t generatePacketId();
static void sendPacketToRemote(uint32_t connectionHandle);
static uint32_t serializePacket(uint32_t streamBase, uint32_t connectionHandle, uint32_t messageType, uint32_t dataSize);

class NetSession {
public:
    uint8_t  m_isConnected;        // +0x1744 (byte): 0 = not connected, non-zero = connected
    // Following the connection flag, there is an array of 5 slots, each 0x4A4 bytes.
    // This function operates on that array by indexing with a slot index.

    // Slot structure (each 0x4A4 bytes):
    // +0x000: unknown (but stream starts at +0x004)
    // +0x004: stream buffer (used by serializePacket)
    // +0x490: packet ID (uint32_t)

    uint32_t buildPlayerPacket(uint32_t* outPacketId,
                               uint32_t connectionHandle,
                               uint32_t messageType,
                               uint32_t dataSize);
};

uint32_t NetSession::buildPlayerPacket(uint32_t* outPacketId,
                                       uint32_t connectionHandle,
                                       uint32_t messageType,
                                       uint32_t dataSize)
{
    // Initial return value (low byte from EAX at entry, but we default to 0)
    uint32_t retVal = 0;
    *outPacketId = 0;

    // Only proceed if connection is alive and a valid handle is given
    if (m_isConnected != 0 && connectionHandle != 0) {
        uint32_t slotIndex = getSlotIndex(messageType);

        // Slot index must be in valid range (0-4)
        if (slotIndex < 5) {
            // Compute pointer to this slot (each slot is 0x4A4 bytes)
            uint8_t* slotPtr = reinterpret_cast<uint8_t*>(this) + slotIndex * 0x4A4;

            // Check if the slot can be used for transmission
            bool opReady = isSlotOperationReady();
            if (opReady) {
                uint32_t newPacketId = generatePacketId();
                *outPacketId = newPacketId;
                *reinterpret_cast<uint32_t*>(slotPtr + 0x490) = newPacketId;

                // Send the packet header or prepare the remote connection
                sendPacketToRemote(connectionHandle);

                // Serialize the payload into the slot's stream (offset +0x04)
                uint32_t streamBase = reinterpret_cast<uint32_t>(slotPtr + 4);
                retVal = serializePacket(streamBase, connectionHandle, messageType, dataSize);
                return retVal;
            }
        }

        // Return the slot index in the high 24 bits (low byte cleared)
        retVal = slotIndex & 0xFFFFFF00U;
    }

    return retVal;
}
// FUNC_NAME: NetConnection::sendPacket
// Address: 0x00643090
// Builds and sends different packet types (ACK, Data, Reliable, etc.) using a command structure.
// The function checks a global connection state (gState) for active state (0xB) and retry limits.

#include <cstdint>

// Forward declarations of helper functions (these are in the binary)
void sendAck(uint32_t ackVal);                        // 0x00642d90
uint32_t getSequenceNumber(void);                     // 0x00642f30
uint32_t getWindowIndex(void);                        // 0x00642fc0
void queuePackedPacket(uint32_t packet, uint32_t extra); // 0x006438e0

// Global pointer to a state structure (used as *in_EAX in decompiled output)
extern int* g_pConnectionState; // first int is state ID, second int is some threshold

void __thiscall NetConnection::sendPacket(int thisPtr, uint32_t* packetCmd) {
    uint32_t cmd = packetCmd[0]; // command type (5,6,7,8)

    // Check if we are in active state (0xb) and within retry limit
    if (*g_pConnectionState == 0xb &&
        *(int*)(thisPtr + 0x34) <= g_pConnectionState[1] &&
        g_pConnectionState[1] < 0xfa) {
        // Decrement retry count at this+0x24
        (*(int*)(thisPtr + 0x24))--;
    }

    switch (cmd) {
        case 5: // ACK packet
            sendAck(packetCmd[1]); // ack value
            return; // no further sending

        case 6: // Data packet (non-reliable)
        {
            uint32_t seq = getSequenceNumber();
            uint32_t extra = *(uint32_t*)(*(int*)(thisPtr + 0xc) + 8); // from connection stream buffer
            uint32_t packed = (( (seq << 9 | packetCmd[1]) << 0xf ) | 8);
            queuePackedPacket(packed, extra);
            break;
        }

        case 7: // Reliable packet
        {
            uint32_t seq = getSequenceNumber();
            uint32_t extra = *(uint32_t*)(*(int*)(thisPtr + 0xc) + 8);
            uint32_t packed = (( (seq << 18 | packetCmd[1]) << 6 ) | 7);
            queuePackedPacket(packed, extra);
            break;
        }

        case 8: // Windowed packet (possibly ordered)
        {
            uint32_t windowIdx = getWindowIndex();
            uint32_t extra = *(uint32_t*)(*(int*)(thisPtr + 0xc) + 8);
            uint32_t packed = (( ((packetCmd[1] << 9 | packetCmd[2]) << 9 | windowIdx) << 6 ) | 9);
            queuePackedPacket(packed, extra);
            break;
        }

        default:
            // Unknown command – ignored
            break;
    }

    // Second state check (present in original code, likely a control flow artifact)
    if (*g_pConnectionState == 0xb &&
        *(int*)(thisPtr + 0x34) <= g_pConnectionState[1] &&
        g_pConnectionState[1] < 0xfa) {
        (*(int*)(thisPtr + 0x24))--;
    }
}
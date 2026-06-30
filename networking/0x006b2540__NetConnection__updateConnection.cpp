// FUNC_NAME: NetConnection::updateConnection
// Address: 0x006b2540
// Role: Update loop for a network connection, handling state machine and packet acknowledgment.

#include <cstdint>

// Forward declarations of external functions
void processRemoteObject(uint32_t remoteId); // 0x008c74d0
uint32_t getNextSequenceNumber();            // 0x0084a410
uint32_t getCurrentAckSequence();            // 0x0084a640
void freePacket(uint32_t packetId);          // 0x008c3240
void internalTick(void* self);               // 0x008c3e00

// Offsets for the connection object (this)
// +0x40 : remote object ID (uint32_t)
// +0xC0 : pointer to packet window structure (PacketWindow*)
// +0xC4 : connection state (int)
// PacketWindow structure:
//   +0x00 : packet ID (uint32_t)
//   +0x04 : packet sequence number (int)

struct PacketWindow {
    uint32_t packetId;        // +0x00
    int sequenceNumber;       // +0x04
};

class NetConnection {
public:
    void __fastcall updateConnection();

    // Internal state constants (guessed)
    enum State {
        STATE_CONNECTING = 0,
        STATE_CONNECTED  = 1
    };

private:
    uint32_t remoteId;        // +0x40
    PacketWindow* packetWindow; // +0xC0
    int state;                // +0xC4
};

void __fastcall NetConnection::updateConnection() {
    // Step 1: Process the remote endpoint (e.g., send a heartbeat/ping)
    processRemoteObject(this->remoteId);

    // Step 2: Handle state-specific logic
    if (this->state != STATE_CONNECTING) {
        if (this->state != STATE_CONNECTED) {
            return; // Unknown state, ignore
        }

        // Only for STATE_CONNECTED
        uint32_t seq1 = getNextSequenceNumber();
        if (seq1 != 0) {
            uint32_t seq2 = getNextSequenceNumber();
            if (seq2 != this->remoteId) {
                return; // Mismatch, skip ack processing
            }

            // Read the sequence number from the first packet in the window
            int packetSeq = this->packetWindow->sequenceNumber;
            int ackSeq = getCurrentAckSequence();

            // If the packet sequence is exactly one ahead of the ack, 
            // the packet has been acknowledged and can be freed.
            if (packetSeq - ackSeq == 1) {
                freePacket(this->packetWindow->packetId);
            }
        }
    }

    // Step 3: Perform general internal update
    internalTick(this);
}
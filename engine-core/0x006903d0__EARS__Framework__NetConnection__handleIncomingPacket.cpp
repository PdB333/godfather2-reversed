// FUNC_NAME: EARS::Framework::NetConnection::handleIncomingPacket
// Address: 0x006903d0
// Handles an incoming network packet from a connection. Creates a packet stream,
// optionally processes it (if param_1 indicates pending data), dispatches to virtual handler (vtable+4),
// and sends an acknowledgement.

// Forward declarations for external functions
typedef uint8 PacketStream[8];  // 8-byte opaque stream buffer (implementation in engine)
extern PacketStream createPacketStream();       // FUN_00496470
extern void processPacketStream(PacketStream*); // FUN_00496780
extern void acknowledgePacket(PacketStream, NetConnection*, uint32); // FUN_00497960

class NetConnection {
public:
    // Virtual function table: offset +0x04 => processIncoming (second vtable entry)
    virtual void process(uint32 context, PacketStream stream) = 0; // called with param_2 and local_8
};

void NetConnection::handleIncomingPacket(uint32 param_1, uint32 param_2) {
    if (this == nullptr) return;

    PacketStream stream = createPacketStream();       // allocate/receive raw packet data

    if (param_1 != 0) {
        processPacketStream(&stream);                 // decode/validate if param_1 indicates pending
    }

    // Virtual dispatch: this->process(param_2, stream)
    (this->vtable->process)(param_2, stream);

    // Send back acknowledgment for reliable delivery
    acknowledgePacket(stream, this, param_2);
}
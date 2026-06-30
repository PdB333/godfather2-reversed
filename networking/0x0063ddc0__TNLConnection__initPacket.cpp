// FUNC_NAME: TNLConnection::initPacket
// Address: 0x0063ddc0
// This function initializes a packet header for sending.
// It allocates a data buffer from a memory pool (this+0x1c) and sets header fields.
// PacketHeader layout:
//   +0x00: int headerSize (set to 4)
//   +0x04: int dataBuffer (pointer to allocated buffer)
//   +0x08: int padding (unwritten)
//   +0x0C: int sequence (set to -1 = invalid)
//   +0x10: int ack (set to -1 = invalid)

struct PacketHeader {
    int headerSize;   // +0x00
    int dataBuffer;   // +0x04
    int padding;      // +0x08
    int sequence;     // +0x0C
    int ack;          // +0x10
};

// __thiscall? Decompiler shows in_EAX, but assuming this in EAX/ECX
void TNLConnection::initPacket(void* thisPtr, PacketHeader* outPacket) {
    int allocSize = 4; // size passed as pointer
    // FUN_00642970 likely allocates from a pool; takes pool pointer (this+0x1c) and size pointer
    int* buffer = (int*)FUN_00642970(*(void**)((char*)thisPtr + 0x1c), &allocSize);
    outPacket->headerSize = 4;
    outPacket->dataBuffer = (int)buffer;
    outPacket->sequence = -1;
    outPacket->ack = -1;
}
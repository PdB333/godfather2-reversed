// FUNC_NAME: PacketStream::getWriteBuffer
// Function at 0x006045b0: Returns pointer to the data payload area within a packet buffer.
// Accesses: this+0x20 (pointer to a packet header struct), returns pointer to offset 0x24 within that struct (packet payload start).
// Used during packet building to obtain the writable region after header.

class PacketStream {
public:
    // Returns pointer to the start of the packet payload (after header).
    char* getWriteBuffer() {
        // Pointer to the packet buffer structure is stored at offset +0x20.
        // The payload data begins at offset +0x24 within that structure.
        return (char*)(*(int*)((uint8_t*)this + 0x20) + 0x24);
    }
};
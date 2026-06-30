// FUNC_NAME: PacketStream::writePacketHeader
#define STREAM_VTABLE_SIZE 0x10 // Example offset for write function

// Global vtable pointer for the stream writer class (likely a singleton)
extern StreamWriterVTable* g_streamWriterVTable; // DAT_01205590

struct StreamWriterVTable {
    void (*init)(); // offset 0x10? Actually based on code, vtable+0x10 is the function used
    // ... other functions
};

class PacketStream {
public:
    // Writes a packet header into the buffer starting at this
    // Returns total header size (8 bytes)
    int writeHeader() {
        // Stack data to be written
        uint16_t flags = 2;     // uStack_10 (2 bytes)
        uint32_t magic = 0x802; // local_8 (4 bytes)

        // Call virtual init function on the global stream writer (prepares for writing)
        g_streamWriterVTable->init(); // (**(code **)(*DAT_01205590 + 0x10))();

        // Write flags to offset 2 (2 bytes)
        g_streamWriterVTable->write(this + 2, &flags, 2); // (**(code **)(*DAT_01205590 + 0x10))(in_EAX + 2,&uStack_10,2);

        // Write magic to offset 4 (4 bytes)
        g_streamWriterVTable->write(this + 4, &magic, 4); // (**(code **)(*DAT_01205590 + 0x10))(in_EAX + 4,&puStack_14,4);

        // Return total size of header (8 bytes)
        return 8; // local_4
    }
};
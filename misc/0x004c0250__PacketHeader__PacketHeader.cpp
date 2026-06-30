// FUNC_NAME: PacketHeader::PacketHeader
// Address: 0x004c0250
// Constructor that initializes a packet header by reading 12-byte header from a stream,
// allocating a private buffer and copying the header data into it.

class PacketHeader {
public:
    // Virtual table pointers:
    // +0x00: vtable1 (PTR_FUN_00e35f48)
    // +0x0C: vtable2 (PTR_LAB_00e35f58)
    
    int32_t field4;          // +0x04 = 1
    int32_t field8;          // +0x08 = 0
    int32_t field10;         // +0x10 = 0
    void*   stream;          // +0x14 : source stream object (param_4)
    size_t  bufferSize;      // +0x18 : size passed to constructor (param_3)
    void*   buffer;          // +0x1C : allocated buffer
    int32_t field20;         // +0x20 = 0
    int32_t field24;         // +0x24 = 0
    int32_t field28;         // +0x28 = 0
    uint16_t field2C;        // +0x2C = 0
    uint16_t field2E;        // +0x2E = 0
    int32_t field30;         // +0x30 = 0
    int32_t field34;         // +0x34 = 0

    // Constructor (__thiscall)
    void* __thiscall ctor(void* unusedParam, size_t size, void* sourceStream) {
        // Initialize fields
        field4 = 1;
        field8 = 0;
        // Set first vtable pointer
        *(void**)this = (void*)&PTR_FUN_00e35f48;
        // Set second vtable pointer (initial, then overwritten)
        *(void**)((char*)this + 0x0C) = (void*)&PTR_FUN_00e32808;
        field10 = 0;
        stream = sourceStream;
        // Overwrite second vtable pointer final
        *(void**)((char*)this + 0x0C) = (void*)&PTR_LAB_00e35f58;
        bufferSize = size;
        buffer = nullptr;
        field20 = 0;
        field24 = 0;
        field28 = 0;
        field2C = 0;
        field2E = 0;
        field30 = 0;
        field34 = 0;

        // Call virtual function at offset 8 on the source stream (likely "prefetch" or "preRead")
        ((void(*)(void*))(*(void***)sourceStream)[2])(); // vtable+8

        // Temporary local buffer (12 bytes) for header reading
        char localBuffer[12] = {0};

        // Call the first virtual function (vtable+0) on the source stream.
        // It reads data into localBuffer and returns a pointer to the allocated buffer.
        void* allocatedBuffer = ((void*(*)(void*, size_t, char*))(*(void***)sourceStream)[0])(size, localBuffer);
        buffer = allocatedBuffer;

        // Copy the header data from the temporary buffer to the allocated buffer
        memcpy(allocatedBuffer, localBuffer, size);

        return this;
    }
};
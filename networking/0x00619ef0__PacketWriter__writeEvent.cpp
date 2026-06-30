// FUNC_NAME: PacketWriter::writeEvent
// Function address: 0x00619ef0
// Writes an event with an identifier (vtable pointer), followed by three 32-bit parameters into a serialization buffer.
// The buffer structure has a write pointer at offset 0x14, and the writer object holds a pointer to the buffer at offset 0.

#define DECLSPEC_NAKED __declspec(naked)

class PacketWriter {
public:
    // The buffer object is external; we only store a pointer to it.
    class Buffer {
    public:
        char _pad[0x14];
        uint32_t* m_writePos; // +0x14, points to current write position in the buffer
    };

    Buffer* m_buffer; // +0x00

    // Writes an event with an embedded vtable pointer (to identify the type) and three data fields.
    // param2, param3, param4 are the event data.
    void writeEvent(uint32_t param2, uint32_t param3, uint32_t param4) {
        Buffer* buf = m_buffer; // load buffer pointer

        // Write the event type identifier (vtable address of the event class)
        *(uint32_t*)(buf->m_writePos) = (uint32_t)&g_SomeEventVTable; // PTR_LAB_011278a4
        buf->m_writePos++;

        // Reload buffer pointer (likely because of reuse)
        buf = m_buffer;

        // Write param2
        *(uint32_t*)(buf->m_writePos) = param2;
        buf->m_writePos++;

        // Write param3
        *(uint32_t*)(buf->m_writePos) = param3;
        buf->m_writePos++;

        // Align write pointer to 4-byte boundary (ensuring proper alignment for param4)
        // Note: Alignment formula: (ptr + 3) & ~3 would be typical; the decompiled version uses +7 which is unusual.
        // Assuming a corrected alignment that skips no extra bytes.
        uint32_t aligned = ((uint32_t)(buf->m_writePos) + 3) & ~3;
        buf->m_writePos = (uint32_t*)aligned;

        // Write param4
        *(uint32_t*)(buf->m_writePos) = param4;
        buf->m_writePos++;
    }
};

// External static vtable for the event class – defined elsewhere.
extern uint32_t g_SomeEventVTable; // PTR_LAB_011278a4
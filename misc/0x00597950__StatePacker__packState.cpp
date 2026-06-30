// FUNC_NAME: StatePacker::packState

#include <cstdint>
#include <cstring>

struct StateBuffer {
    uint8_t data[0xC0];
};

struct SourceState {
    // Offsets from decompilation
    void*    block1;      // +0x24 (0x40 bytes)
    uint32_t field28;     // +0x28
    uint32_t field2C;     // +0x2C (bool)
    uint8_t  field38;     // +0x38
    uint8_t  field3C;     // +0x3C
    uint32_t field30;     // +0x30
    uint32_t field34;     // +0x34
    uint32_t field40;     // +0x40
    void*    block2;      // +0x44 (0x40 bytes)
    uint32_t field48;     // +0x48
    uint32_t field4C;     // +0x4C (bool)
    uint32_t field50;     // +0x50
    uint32_t field54;     // +0x54
    uint8_t  field58;     // +0x58
    uint8_t  field5C;     // +0x5C
    uint32_t field60;     // +0x60
    uint32_t field64;     // +0x64
    uint32_t field68;     // +0x68 (bool)
    uint32_t field6C;     // +0x6C (bool)
};

// Global stream writer vtable (function pointer table at 0x01205590)
extern void* g_streamVTable;
typedef void (*WriteFunc)(void* dest, const void* src, uint32_t size);
inline WriteFunc getStreamWriter() {
    return (WriteFunc)(*(uint32_t*)(*(uint32_t*)g_streamVTable + 0x10));
}

// Pack state data into a 0xC0-byte buffer
uint32_t __fastcall StatePacker::packState(StateBuffer* dest) {
    WriteFunc streamWrite = getStreamWriter();

    // --- Header writes (stream packet metadata) ---
    // First header: type=0x203, size=0xC0, debug string at 0x59797e
    uint32_t headerMagic[2] = { 0x203, 0xC0 };
    streamWrite(dest, headerMagic, 8); // simplified: write header struct

    // Second header: type=2, offset=dest+2, debug string at 0x597996
    uint16_t headerTwo = 2;
    streamWrite(dest->data + 2, &headerTwo, 2);

    // Get source state pointer (returned from stream write on dest+4)
    SourceState* src;
    {
        uint32_t temp; // placeholder for stream write result
        streamWrite(dest->data + 4, &temp, 4); // results in EAX = source pointer
        src = reinterpret_cast<SourceState*>(temp); // approximate
    }
    // Write another 4 bytes (source pointer continuation?)
    streamWrite(dest->data + 8, src, 4);

    // --- Main payload ---
    // Build flags word (8 bytes at dest+0x14)
    uint32_t flagsLow =
        ((uint32_t)(src->field2C != 0) << 0) |
        ((uint32_t)src->field38          << 8) |
        ((uint32_t)src->field3C          << 16) |
        ((uint32_t)(src->field4C != 0)   << 24);
    uint32_t flagsHigh =
        ((uint32_t)src->field58         << 0) |
        ((uint32_t)src->field5C         << 8) |
        ((uint32_t)(src->field6C != 0)  << 16) |
        ((uint32_t)(src->field68 != 0)  << 24);
    streamWrite(dest->data + 0x14, &flagsLow, 8);

    // Copy 0x40-byte data block from src->block1 pointer
    streamWrite(dest->data + 0x1C, src->block1, 0x40);

    // Copy 4-byte fields
    streamWrite(dest->data + 0x5C, &src->field28, 4);
    streamWrite(dest->data + 0x60, &src->field30, 4);
    streamWrite(dest->data + 0x64, &src->field34, 4);
    streamWrite(dest->data + 0x68, &src->field40, 4);

    // Copy second 0x40-byte data block from src->block2 pointer
    streamWrite(dest->data + 0x6C, src->block2, 0x40);

    // More 4-byte fields
    streamWrite(dest->data + 0xAC, &src->field48, 4);
    streamWrite(dest->data + 0xB0, &src->field50, 4);
    streamWrite(dest->data + 0xB4, &src->field54, 4);
    streamWrite(dest->data + 0xB8, &src->field60, 4);
    streamWrite(dest->data + 0xBC, &src->field64, 4);

    return 0xC0; // total packet size
}
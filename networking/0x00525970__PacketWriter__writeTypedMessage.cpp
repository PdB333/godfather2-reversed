// FUNC_NAME: PacketWriter::writeTypedMessage
#include <cstring> // for memcpy

// Helper structure representing the internal buffer state
// The actual class definition would have a pointer to this at offset 0x0
struct StreamBuffer {
    // ... other members ...
    uint8_t* currentPos; // +0x14
};

// __thiscall – the first parameter (param_1) is the 'this' pointer
void __thiscall PacketWriter::writeTypedMessage(
    PacketWriter* this,
    uint32_t param_2,
    uint32_t param_3,
    uint32_t param_4,
    uint32_t param_5,
    uint8_t  param_6,
    void*    param_7)
{
    // The PacketWriter object's first member (offset 0x0) is a pointer to a StreamBuffer
    StreamBuffer* buffer = *reinterpret_cast<StreamBuffer**>(this);

    // Get a reference to the current write position
    uint8_t*& curr = buffer->currentPos;

    // --- Write the vtable pointer (message type identifier) ---
    *reinterpret_cast<uint32_t*>(curr) = reinterpret_cast<uint32_t>(&PTR_FUN_011251d0);
    curr += 4;

    // Align to 4-byte boundary
    curr = reinterpret_cast<uint8_t*>((reinterpret_cast<uintptr_t>(curr) + 3) & ~3);

    // --- Write two 64-bit values (parameters 2/3 and 4/5) ---
    uint64_t val1 = (static_cast<uint64_t>(param_3) << 32) | param_2;
    uint64_t val2 = (static_cast<uint64_t>(param_5) << 32) | param_4;

    *reinterpret_cast<uint64_t*>(curr) = val1;
    curr += 8;

    *reinterpret_cast<uint64_t*>(curr) = val2;
    curr += 8;

    // --- Write a single byte (stored as a 32‑bit value, only low byte used) ---
    *reinterpret_cast<uint32_t*>(curr) = param_6; // upper bytes are zero
    curr += 4;

    // Align to 16-byte boundary
    curr = reinterpret_cast<uint8_t*>((reinterpret_cast<uintptr_t>(curr) + 0x23) & 0xFFFFFFF0);

    // --- Copy the 0x40 (64) byte payload ---
    std::memcpy(curr, param_7, 0x40);
    curr += 0x40;

    // Update the buffer's current position (already done via reference)
}
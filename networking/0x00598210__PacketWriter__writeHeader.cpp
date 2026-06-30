// FUNC_NAME: PacketWriter::writeHeader
// Function address: 0x00598210
// This function appears to initialize and write a packet header structure.
// It uses a virtual function at vtable offset 0x10 (likely a write/serialize method).
// The header structure is 12 bytes (0xC) and contains:
//   +0x00: size field? (0x800)
//   +0x04: type field? (0xC)
//   +0x08: flag field? (2)
// The function writes these fields to the object's buffer at offsets 2, 4, 8.

#include <cstdint>

class PacketWriter {
public:
    // Virtual table pointer at offset 0x00
    // Virtual function at offset 0x10: write(void* data, uint32_t size) or similar

    // Writes a header structure to the internal buffer.
    // Returns the size of the header (0xC).
    uint32_t writeHeader() {
        // Local variables representing the header fields
        uint32_t sizeField = 0x800;      // +0x00: size or count
        uint32_t typeField = 0xC;        // +0x04: type or identifier
        uint32_t flagField = 2;          // +0x08: flags or mode

        // Pointer to the header structure (sizeField and typeField are adjacent)
        uint32_t* headerPtr = &sizeField;

        // First virtual call: possibly writes the entire header or initializes something
        // The decompiler shows a call with no explicit arguments, but it might be
        // a call to a base class method or a different virtual function.
        // For now, we assume it's a write with implicit 'this'.
        // (**(code **)(*vtable + 0x10))();

        // Write flagField at offset 2 from the buffer start
        (*(void (__thiscall**)(PacketWriter*, void*, uint32_t))((uint32_t*)this[0] + 0x10 / 4))(
            this, reinterpret_cast<void*>(reinterpret_cast<uint8_t*>(this) + 2), &flagField);

        // Write headerPtr (pointer to sizeField) at offset 4
        (*(void (__thiscall**)(PacketWriter*, void*, uint32_t))((uint32_t*)this[0] + 0x10 / 4))(
            this, reinterpret_cast<void*>(reinterpret_cast<uint8_t*>(this) + 4), &headerPtr, 4);

        // Write flagField again? Actually writes the value 2 at offset 8
        uint32_t anotherFlag = 2;
        (*(void (__thiscall**)(PacketWriter*, void*, uint32_t))((uint32_t*)this[0] + 0x10 / 4))(
            this, reinterpret_cast<void*>(reinterpret_cast<uint8_t*>(this) + 8), &anotherFlag, 4);

        return 0xC; // Size of the header
    }
};
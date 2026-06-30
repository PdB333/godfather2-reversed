// FUNC_NAME: PacketStream::writeAlignedData
// Address: 0x005085d0
// Role: Packs six fixed-size fields (a,b:uint32, c,d:uint64, e:uint32, f:uint64) into a byte buffer pointed to by member at +0x14, with 4-byte alignment between groups.

#include <cstdint>

class PacketStream {
public:
    void writeAlignedData(uint32_t a, uint32_t b, uint64_t c, uint64_t d, uint32_t e, uint64_t f);
private:
    // Assume 'writePtr' is at offset +0x14
    uint8_t* writePtr; // +0x14
};

// Helper to align pointer to next 4-byte boundary
inline uint8_t* alignTo4(uint8_t* p) {
    return reinterpret_cast<uint8_t*>(
        (reinterpret_cast<uintptr_t>(p) + 7) & ~3
    );
}

void PacketStream::writeAlignedData(uint32_t a, uint32_t b, uint64_t c, uint64_t d, uint32_t e, uint64_t f) {
    // Write first 4-byte value
    *reinterpret_cast<uint32_t*>(writePtr) = a;
    writePtr = alignTo4(writePtr + 4); // Align for next 4-byte write

    // Write second 4-byte value
    *reinterpret_cast<uint32_t*>(writePtr) = b;
    writePtr = alignTo4(writePtr + 4); // Align to start of group block

    // Write group: two 8-byte values followed by one 4-byte value (contiguous, then align)
    uint8_t* groupBase = writePtr; // Start of this group (already 4-byte aligned)
    *reinterpret_cast<uint64_t*>(groupBase) = c;
    *reinterpret_cast<uint64_t*>(groupBase + 8) = d;
    *reinterpret_cast<uint32_t*>(groupBase + 16) = e;

    // Advance pointer past the group (20 bytes) and align to next 4-byte boundary
    writePtr = alignTo4(groupBase + 23); // Equivalent to groupBase + 20 (since 20 is already aligned)

    // Write final 8-byte value
    *reinterpret_cast<uint64_t*>(writePtr) = f;
    writePtr += 8; // No alignment needed after last write
}
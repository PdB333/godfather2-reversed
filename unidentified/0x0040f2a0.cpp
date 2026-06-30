// Reconstructed function at 0x0040f2a0
// The decompiled body is a simple thiscall member helper that stores four
// 32-bit values into the object at offsets 0x0, 0x4, 0x8, and 0xC.
//
// There is no surrounding type information in the export, so this is modeled
// as a small 16-byte POD-style structure with a setter/initializer method.

#include <cstdint>

struct FourDwordBlock {
    uint32_t value0;
    uint32_t value1;
    uint32_t value2;
    uint32_t value3;

    // Copies four caller-supplied dwords into the object.
    // This matches the original thiscall implementation exactly.
    void __thiscall Set(uint32_t v0, uint32_t v1, uint32_t v2, uint32_t v3) {
        value0 = v0;
        value1 = v1;
        value2 = v2;
        value3 = v3;
    }
};


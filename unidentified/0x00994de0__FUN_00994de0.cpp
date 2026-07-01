// FUNC_NAME: UnknownClass::operator=
// Address: 0x00994de0
// Reconstructed copy assignment operator for a class with two subobjects at offsets 0x10 and 0x60.

#include <cstdint>

// Helper function: likely copies a subobject from source to the corresponding subobject in 'this'.
// Called with pointers to subobject data at offset 0x10 and 0x60.
void copySubobject(const void* source);

class UnknownClass {
    // +0x00: first 4 bytes
    uint32_t field00;
    // +0x04: next 4 bytes
    uint32_t field04;
    // +0x08: next 4 bytes
    uint32_t field08;
    // Subobject at offset 0x10 (size unknown)
    // +0x50: some field
    uint32_t field50;
    // Subobject at offset 0x60 (size unknown)
    // Fields at +0xA0, +0xA4, +0xA8, +0xAC, +0xB0, +0xB4
    uint32_t fieldA0;
    uint32_t fieldA4;
    uint32_t fieldA8;
    uint32_t fieldAC;
    uint32_t fieldB0;
    uint32_t fieldB4;

public:
    UnknownClass& operator=(const UnknownClass& other) {
        // Copy first 12 bytes (offsets 0x00, 0x04, 0x08)
        field00 = other.field00;
        field04 = other.field04;
        field08 = other.field08;

        // Copy subobject at offset 0x10
        copySubobject(reinterpret_cast<const uint8_t*>(&other) + 0x10);

        // Copy field at offset 0x50
        field50 = other.field50;

        // Copy subobject at offset 0x60
        copySubobject(reinterpret_cast<const uint8_t*>(&other) + 0x60);

        // Copy six uint32s from offsets 0xA0 to 0xB4
        fieldA0 = other.fieldA0;
        fieldA4 = other.fieldA4;
        fieldA8 = other.fieldA8;
        fieldAC = other.fieldAC;
        fieldB0 = other.fieldB0;
        fieldB4 = other.fieldB4;

        return *this;
    }
};
// FUNC_NAME: UnknownClass::computeIndexedOffset

// Reconstructed C++ function at 0x006b2320.
// Computes an offset based on two integer members at offsets +0x88 and +0xa0.
// Return value: (field_88 + field_a0) * 20 + 96
// Possible use: index into an array of 20-byte structures with base offset 0x60.

class UnknownClass {
public:
    int field_0x88;
    int field_0xa0;

    int __fastcall computeIndexedOffset() {
        return (field_0x88 + field_0xa0) * 0x14 + 0x60;
    }
};
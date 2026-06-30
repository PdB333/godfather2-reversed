// FUNC_NAME: TripleData::TripleData
// Function address: 0x004a3d40
// Role: Constructor for a small struct containing two 32-bit values and one 8-bit value.
// Offsets: +0x00 (uint32_t), +0x04 (uint32_t), +0x08 (uint8_t)

struct TripleData {
    uint32_t field0;  // +0x00
    uint32_t field4;  // +0x04
    uint8_t field8;   // +0x08

    // Constructor: initializes the three fields.
    __thiscall TripleData(uint32_t arg1, uint32_t arg2, uint8_t arg3) {
        field0 = arg1;
        field4 = arg2;
        field8 = arg3;
    }
};
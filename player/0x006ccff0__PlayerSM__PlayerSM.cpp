// FUNC_NAME: PlayerSM::PlayerSM
// Constructor at 0x006ccff0 for PlayerSM (likely a state machine with multiple inheritance vtable pointers)
// Initializes base class with argument, sets up multiple vtable pointers, and fills debug magic numbers.

class SomeBase {
public:
    SomeBase(int arg); // called via FUN_00473840
};

class PlayerSM : public SomeBase {
public:
    PlayerSM(int arg);
    // vtable pointer at +0x00: &PTR_FUN_00d5f134
    // vtable at +0x3C (0x0F * 4): &PTR_LAB_00d5f124
    // vtable at +0x48 (0x12 * 4): &PTR_LAB_00d5f120
    // vtable at +0x50 (0x14 * 4): &PTR_LAB_00d5f11c
    // ... further magic fields
};

PlayerSM::PlayerSM(int arg) : SomeBase(arg) {
    // Virtual table pointers (multiple inheritance)
    this->vtable = &PTR_FUN_00d5f134;                // +0x00
    this->vtable2 = &PTR_LAB_00d5f124;               // +0x3C (offset 0x0F)
    this->vtable3 = &PTR_LAB_00d5f120;               // +0x48 (offset 0x12)
    this->vtable4 = &PTR_LAB_00d5f11c;               // +0x50 (offset 0x14)

    // Debug/identification magic numbers
    this->magic1 = 0xbadbadba;                       // +0x58 (offset 0x16)
    this->magic2 = 0x91100911;                       // +0x64 (offset 0x19)
    this->magic3 = 0xbeefbeef;                       // +0x5C (offset 0x17)
    this->magic4 = 0xeac15a55;                       // +0x60 (offset 0x18)
    this->magic5 = 0x91100911;                       // +0x74 (offset 0x1D)
    this->magic6 = 0xbadbadba;                       // +0x68 (offset 0x1A)
    this->magic7 = 0xbeefbeef;                       // +0x6C (offset 0x1B)
    this->magic8 = 0xeac15a55;                       // +0x70 (offset 0x1C)

    // Clear fields
    this->field_1E = 0;                              // +0x78 (offset 0x1E)
    this->field_1F = 0;                              // +0x7C (offset 0x1F)
    this->field_20 = 0;                              // +0x80 (offset 0x20)
    this->field_21 = 0;                              // +0x84 (offset 0x21)
    this->field_22 = 0;                              // +0x88 (offset 0x22)
    this->field_23 = 0;                              // +0x8C (offset 0x23)

    // Field from global data
    this->field_24 = DAT_00d5d740;                   // +0x90 (offset 0x24)
    this->field_25 = 0x21;                           // +0x94 (offset 0x25)
    // Note: Return this pointer implicit
}
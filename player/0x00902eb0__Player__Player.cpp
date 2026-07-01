// FUNC_NAME: Player::Player
// Address: 0x00902eb0
// Role: Constructor for Player class. Initializes vtable pointers, sentinel markers for memory integrity, and global data.

void __thiscall Player::Player(int32_t param_2) {
    // Call base class constructor (likely Entity or Sentient)
    FUN_0046c590(param_2); // TODO: rename to appropriate base constructor

    // Set virtual function table pointers
    // vtable at offset 0x00
    this->vtable = (void*)0x00d81f20; // base vtable
    // additional vtable at offset 0x3C (index 0xF)
    this->vtable2 = (void*)0x00d81f10;
    // additional vtable at offset 0x48 (index 0x12)
    this->vtable3 = (void*)0x00d81f0c;

    // Sentinel markers for memory corruption detection
    // First sentinel block at offset 0x50-0x5C
    *(uint32_t*)((uint8_t*)this + 0x50) = 0xbadbadba;
    *(uint32_t*)((uint8_t*)this + 0x54) = 0x91100911;
    *(uint32_t*)((uint8_t*)this + 0x58) = 0xbeefbeef;
    *(uint32_t*)((uint8_t*)this + 0x5C) = 0xeac15a55;

    // Second sentinel block at offset 0x60-0x6C
    *(uint32_t*)((uint8_t*)this + 0x60) = 0xbadbadba;
    *(uint32_t*)((uint8_t*)this + 0x64) = 0xbeefbeef;
    *(uint32_t*)((uint8_t*)this + 0x68) = 0xeac15a55;
    *(uint32_t*)((uint8_t*)this + 0x6C) = 0x91100911;

    // Zero out fields at offset 0x70-0x80 (indices 0x1C to 0x20)
    for (int i = 0; i < 5; i++) {
        *(uint32_t*)((uint8_t*)this + 0x70 + i*4) = 0;
    }

    // Zero out halfword pairs (likely arrays of shorts)
    // Pair at offset 0x84-0x87
    *(uint16_t*)((uint8_t*)this + 0x84) = 0;
    *(uint16_t*)((uint8_t*)this + 0x86) = 0;
    // Word at offset 0x88 (index 0x22)
    *(uint32_t*)((uint8_t*)this + 0x88) = 0;
    // Pair at offset 0x8C-0x8F
    *(uint16_t*)((uint8_t*)this + 0x8C) = 0;
    *(uint16_t*)((uint8_t*)this + 0x8E) = 0;
    // Word at offset 0x90 (index 0x24)
    *(uint32_t*)((uint8_t*)this + 0x90) = 0;
    // Pair at offset 0x94-0x97
    *(uint16_t*)((uint8_t*)this + 0x94) = 0;
    *(uint16_t*)((uint8_t*)this + 0x96) = 0;

    // Assign global data
    // DAT_00d5e288 is likely a singleton or manager pointer
    *(uint32_t*)((uint8_t*)this + 0x98) = DAT_00d5e288; // offset 0x98 (index 0x26)
    *(uint32_t*)((uint8_t*)this + 0x9C) = 0;            // offset 0x9C (index 0x27)

    // Additional state fields
    *(uint32_t*)((uint8_t*)this + 0xA0) = 1;            // offset 0xA0 (index 0x28) initialized to 1
    *(uint32_t*)((uint8_t*)this + 0xA4) = 0;            // offset 0xA4 (index 0x29)
    *(uint32_t*)((uint8_t*)this + 0xA8) = DAT_00d5cf70; // offset 0xA8 (index 0x2A)
    *(uint32_t*)((uint8_t*)this + 0xAC) = 0;            // offset 0xAC (index 0x2B)
}
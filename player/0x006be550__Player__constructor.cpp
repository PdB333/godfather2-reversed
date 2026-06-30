// FUNC_NAME: Player::constructor
// Address: 0x006be550
// Role: Constructor for a Player object. Initializes vtable, sets function pointers, and zeroes fields.

void* __thiscall Player::constructor(Player* this, void* initData) {
    // Call base class constructor (likely Entity or Sentient)
    FUN_0046c590(initData);

    // Set vtable pointer (offset 0x00)
    this->vtable = &PTR_FUN_00d5eb60;

    // Set function pointers at offsets 0x3C and 0x48
    this->field_0x3C = &PTR_LAB_00d5eb50;  // +0x3C
    this->field_0x48 = &PTR_LAB_00d5eb4c;  // +0x48

    // Zero out fields from offset 0x50 to 0x6E
    this->field_0x50 = 0;                  // +0x50
    this->field_0x58 = 0;                  // +0x58
    *(uint16_t*)((uint8_t*)this + 0x5C) = 0; // +0x5C (16-bit)
    *(uint16_t*)((uint8_t*)this + 0x5E) = 0; // +0x5E (16-bit)
    this->field_0x60 = 0;                  // +0x60
    *(uint16_t*)((uint8_t*)this + 0x64) = 0; // +0x64 (16-bit)
    *(uint16_t*)((uint8_t*)this + 0x66) = 0; // +0x66 (16-bit)
    this->field_0x68 = 0;                  // +0x68
    *(uint16_t*)((uint8_t*)this + 0x6C) = 0; // +0x6C (16-bit)
    *(uint16_t*)((uint8_t*)this + 0x6E) = 0; // +0x6E (16-bit)

    return this;
}
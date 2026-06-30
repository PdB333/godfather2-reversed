// FUNC_NAME: Sentient::Sentient
void Sentient::Sentient() {
    // Zero-initialize base fields
    this->field_0x00 = 0;          // +0x00
    this->field_0x04 = 0;          // +0x04
    this->field_0x10 = 0;          // +0x10
    this->field_0x08 = 0;          // +0x08
    this->field_0x0C = 0;          // +0x0C

    // Set vtable pointer at +0x18
    this->vtable = (void*)&PTR_FUN_00e3e7d4; // +0x18

    // Zero more fields
    this->field_0x54 = 0;          // +0x54
    this->field_0x4C = 0;          // +0x4C
    this->field_0x50 = 0;          // +0x50
    this->field_0x58 = 0;          // +0x58

    // Default max health
    this->maxHealth = 1000;        // +0x5C

    this->field_0x64 = 0;          // +0x64
    this->isAlive = 1;             // byte at +0x60

    // Additional fields
    this->field_0x20 = 0;          // +0x20
    this->field_0x24 = 0;          // +0x24
    this->byteAt0x28 = 0;          // byte at +0x28
    this->isEnabled = 1;           // byte at +0x48

    // Function pointers (likely behavior or state machine)
    this->someFuncPtr1 = &PTR_LAB_00e3e8c8; // +0x68
    this->field_0x78 = 0;          // +0x78
    this->field_0x70 = 0;          // +0x70
    this->field_0x74 = 0;          // +0x74
    this->someFuncPtr2 = &PTR_FUN_00e3e880; // +0x6C
    this->field_0x84 = 0;          // +0x84
    this->field_0x7C = 0;          // +0x7C
    this->field_0x80 = 0;          // +0x80
    this->byteAt0xC0 = 1;          // byte at +0xC0
}
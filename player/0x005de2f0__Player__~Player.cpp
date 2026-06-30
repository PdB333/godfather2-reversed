//FUNC_NAME: Player::~Player
void __thiscall Player::~Player() {
    // Call virtual destructors for each base class (second virtual function in each vtable)
    // Primary vtable at +0x00
    (**(code**)(this->vtable + 4))(); // vtable[1] (destructor)
    // Secondary vtable at +0x38 (offset 0xe * 4)
    (**(code**)(this->base2_vtable + 4))(); // vtable[1] (destructor)
    // Tertiary vtable at +0x70 (offset 0x1c * 4)
    (**(code**)(this->base3_vtable + 4))(); // vtable[1] (destructor)

    // Free a dynamically allocated pointer at +0xA8 (offset 0x2a * 4)
    if (this->field_0xA8 != 0) {
        operatorDelete(this->field_0xA8); // FUN_009c8f10
    }

    // Reset vtable pointers to base class vtables and call base destructors (reverse order)
    this->base3_vtable = &PTR_FUN_00e3f2d8; // +0x70
    callBaseDestructor(); // FUN_004de130
    this->base2_vtable = &PTR_FUN_00e3f2d0; // +0x38
    callBaseDestructor(); // FUN_004de130
    this->vtable = &PTR_FUN_00e3f2c8; // +0x00
    callBaseDestructor(); // FUN_004de130
}
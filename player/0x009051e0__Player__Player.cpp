//FUNC_NAME: Player::Player
// Address: 0x009051e0
// Constructor for Player class (size 0x230)
// Sets up multiple vtable pointers for multiple inheritance (base classes/interfaces)

Player* __thiscall Player::Player(Player* this, byte allocFlag) {
    // Main vtable pointer at offset 0
    this->vtable = (PlayerVTable*)&PTR_FUN_00d82440;

    // Additional vtable pointers for base classes/interfaces
    this->field_0x3C = &PTR_LAB_00d82430;   // +0x3C (offset 0x3C)
    this->field_0x48 = &PTR_LAB_00d8242c;   // +0x48 (offset 0x48)
    this->field_0x50 = &PTR_LAB_00d82428;   // +0x50 (offset 0x50)
    this->field_0x54 = &PTR_LAB_00d823c8;   // +0x54 (offset 0x54)
    this->field_0x58 = &PTR_LAB_00d82360;   // +0x58 (offset 0x58)

    // Call base class constructor (likely Sentient or Entity)
    Sentient::Sentient((Sentient*)this);

    // If allocFlag & 1 is set, the object was allocated with operator new.
    // In case of construction failure (exception), free the memory.
    // (Decompiled code shows this call after base constructor; likely exception handling.)
    if (allocFlag & 1) {
        operator delete(this, 0x230);
    }

    return this;
}
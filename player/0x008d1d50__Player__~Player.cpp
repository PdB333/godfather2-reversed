// FUNC_NAME: Player::~Player
void __thiscall Player::~Player(Player* this) {
    // set base class vtables (multiple inheritance)
    this->vtablePrimary = &PTR_FUN_00d7d370;      // +0x00 primary vtable
    this->vtableBase2 = &PTR_LAB_00d7d360;        // +0x3C second base
    this->vtableBase3 = &PTR_LAB_00d7d35c;        // +0x48 third base

    // destroy sub-object at offset 0x50 if it exists
    if (this->subObject != NULL) {                 // +0x50
        releaseSubObject(&this->subObject);        // FUN_004086d0 – release/sub-destructor
        freeSubObjectMemory(&this->subObject);     // FUN_00408310 – deallocate sub-object
    }

    deallocateMemory();                            // FUN_0046c640 – free this instance
}
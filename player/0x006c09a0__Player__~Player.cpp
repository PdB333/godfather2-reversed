// FUNC_NAME: Player::~Player
void __thiscall Player::~Player(Player *this)
{
    // Set vtable pointers to base class vtables for proper virtual dispatch during destruction
    this->vtable1 = &PTR_FUN_00d5ef34;   // +0x00: first base class vtable
    this->vtable2 = &PTR_LAB_00d5ef2c;   // +0x08: second base class vtable

    // Clean up the component pointer at offset 0xE8 if it exists
    if (this->componentPtr != nullptr) {
        // &this->componentPtr passed to a safe-delete function (FUN_004daf90)
        safeDelete(&this->componentPtr);
    }

    // Call global cleanup / finalization (FUN_006c9820)
    gameCleanup();
}
// FUNC_NAME: Player::Player
Player * __thiscall Player::Player(Player *this, byte flags) {
    int *allocator;

    this->vtable = &Player_vtable_00d737b4;
    Sentient::Sentient(this); // FUN_0082a730
    this->field_0x30 = &WeaponComponent_vtable_00d7343c;
    if (this->field_0x8C != 0) {
        cleanupSubObject((void **)(this + 0x8C)); // FUN_004daf90 – frees and nulls the pointer
    }
    this->field_0x30 = &Player_vtable_00e32854; // final vtable override
    initPlayer(this); // FUN_00821f60 – additional initialization
    if ((flags & 1) != 0) {
        allocator = (int *)getAllocator(); // FUN_009c8f80
        allocator[0]->deallocate(this, 0xC0); // (**(code **)(*allocator + 4))(this, 0xC0)
    }
    return this;
}
// FUNC_NAME: Entity::Entity

Entity * __thiscall Entity::Entity(Entity *this, void *initParam) {
    // Delegate to base initializer (FUN_0046c590)
    initializeBase(initParam);

    // Install vtable and secondary interface tables
    this->vtable = &ENTITY_VTABLE;            // +0x00
    this->vtable2 = &ENTITY_VTABLE2;          // +0x3C (offset 0xF)
    this->vtable3 = &ENTITY_VTABLE3;          // +0x48 (offset 0x12)

    // Zero initialise fields
    this->field_0x50 = 0;                     // +0x50 (int)
    *(short *)((int)this + 0x54) = 0;         // +0x54 (short)
    *(short *)((int)this + 0x56) = 0;         // +0x56 (short)
    this->field_0x58 = 0;                     // +0x58 (int)
    this->field_0x5C = 0;                     // +0x5C (int)
    this->field_0x60 = 0;                     // +0x60 (int)
    this->field_0x64 = 0;                     // +0x64 (int)

    return this;
}
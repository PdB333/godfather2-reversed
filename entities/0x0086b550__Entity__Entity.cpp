// FUNC_NAME: Entity::Entity
Entity* __thiscall Entity::Entity(Entity* this, byte flags) {
    // Set vtable pointer
    this->vtable = &PTR_FUN_00d75e5c;
    // Initialize fields at offsets +0x3C and +0x48
    this->field_0x3C = &PTR_LAB_00d75e4c; // +0x3C
    this->field_0x48 = &PTR_LAB_00d75e48; // +0x48
    // Call base class constructor (likely Entity base or similar)
    FUN_0046c640(); // BaseClass::BaseClass()
    // If flag bit 0 is set, deallocate the object (e.g., for placement new cleanup)
    if (flags & 1) {
        operator delete(this, 0x50);
    }
    return this;
}
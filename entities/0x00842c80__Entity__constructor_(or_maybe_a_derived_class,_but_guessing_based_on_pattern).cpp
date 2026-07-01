// FUNC_NAME: Entity::constructor (or maybe a derived class, but guessing based on pattern)
undefined4* __thiscall Entity::constructor(Entity* this, byte flags) {
    // +0x00: vtable pointer for this class (derived)
    // +0x04: vtable pointer for base class (e.g., GameObject)
    undefined4* vtableSlot = (this != nullptr) ? &this->baseVtable : nullptr;
    *vtableSlot = &PTR_LAB_00d748f8;   // derived class vtable
    *this = &PTR_LAB_00d74620;         // base class vtable

    if ((flags & 1) != 0) {
        // If flag indicates self-destruction, call operator delete or destructor
        FUN_00840230(this);
    }
    return this;
}
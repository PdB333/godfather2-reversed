// FUNC_NAME: Component::Component
void __thiscall Component::Component(Component *this, Component *parent) {
    // Initialize vtable pointer and zero out fields
    this->vtable = &ComponentVTable;            // +0x00
    this->field_4 = 0;                          // +0x04
    this->subObjectDelta = 0;                   // +0x08 (relative offset, becomes absolute if non-zero)
    this->subObjectBase = 0;                    // +0x0C (will point to parent + 0x38)
    this->parent = 0;                           // +0x10
    this->field_14 = 0;                         // +0x14
    this->field_18 = 0;                         // +0x18 (byte)

    // Adjust subObjectDelta from relative to absolute if it was non-zero
    if (this->subObjectDelta != 0) {
        this->subObjectDelta = (int)this + this->subObjectDelta;
    }

    // If a parent is provided and its type at +0x20 equals 0xF (e.g., a component type identifier)
    if (parent != 0 && *(int *)(this->subObjectDelta + 0x20) == 0xF) {
        FUN_005dde90();                          // Register or finalize attachment
        this->subObjectBase = this->subObjectDelta + 0x38;
        this->parent = parent;
    }
}
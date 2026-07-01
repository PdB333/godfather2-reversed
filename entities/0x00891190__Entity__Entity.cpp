//FUNC_NAME: Entity::Entity
// Address: 0x00891190
// Constructor for Entity class with multiple inheritance (vtable at +0x00, +0x3C, +0x48)
// Subobject at +0x14 initialized via two calls, then global init, then optional deallocation if flag bit 0 set

Entity* __thiscall Entity::Entity(Entity* this, byte flags) {
    // Set vtable pointers for base classes
    this->vtable = &PTR_FUN_00d7775c;          // +0x00: main vtable
    this->field_0x3C = &PTR_LAB_00d7774c;      // +0x3C: second vtable (offset 0xf)
    this->field_0x48 = &PTR_LAB_00d77748;      // +0x48: third vtable (offset 0x12)

    // Initialize subobject at offset 0x14 (likely another base class or member)
    FUN_004086d0(this + 0x14);                 // subobject constructor
    FUN_00408310(this + 0x14);                 // subobject initialization

    // Global/static initialization (e.g., reference counting, singleton)
    FUN_0046c640();

    // If the object was heap-allocated (flags & 1), call sized deallocation
    // Note: This is unusual – might be a custom allocator cleanup or error path
    if ((flags & 1) != 0) {
        FUN_0043b960(this, 0x5c);              // operator delete(this, size 0x5c)
    }

    return this;
}
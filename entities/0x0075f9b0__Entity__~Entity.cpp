// FUNC_NAME: Entity::~Entity
// Function address: 0x0075f9b0
// Role: Destructor for Entity class. Sets vtable to base class, destroys subobject at offset +0x60, then calls global cleanup.

void __thiscall Entity::~Entity() {
    // Set vtable pointer to base class vtable (global table at 0x00d65334)
    *(void**)this = *&PTR_LAB_00d65334;

    // Destroy subobject at offset +0x60 (this[0x18]) if not null
    if (this->field_0x60 != nullptr) {
        FUN_004daf90(&(this->field_0x60));
    }

    // Global cleanup function (likely frees engine resources)
    FUN_004ac1e0();
}
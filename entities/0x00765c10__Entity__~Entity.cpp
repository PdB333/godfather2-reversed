// FUNC_NAME: Entity::~Entity
void __fastcall Entity::~Entity(int* this) {
    // Set vtable pointer to base class vtable (destructor phase)
    *this = (int)&PTR_LAB_00d63090;  // +0x00: vtable pointer

    // Release sub-object at offset +0x68 (0x1a * 4)
    if (this[0x1a] != 0) {
        FUN_004daf90(this + 0x1a);  // Likely deallocates/releases a pointer member
    }

    // Global cleanup (memory manager or similar)
    FUN_0080ea60();
}
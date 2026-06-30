// FUNC_NAME: Entity::Entity
// Reconstructed constructor for Entity (base object) at 0x006a77c0
void* __thiscall Entity::Entity(void* this, byte flags) {
    // Set vtable pointers for multiple inheritance
    *(void***)this = (void**)&PTR_FUN_00d5d840;              // +0x00 main vtable
    *(void***)((char*)this + 0x3C) = (void**)&PTR_LAB_00d5d830; // +0x3C secondary vtable
    *(void***)((char*)this + 0x48) = (void**)&PTR_LAB_00d5d82c; // +0x48 secondary vtable

    // Call base class constructor (likely Object or BaseEntity)
    EntityBase::EntityBase(); // FUN_0046c640

    // If allocated with new (flag bit 0 set), call operator delete on failure?
    // Pattern observed in EARS constructors: if flag & 1, deallocate on construction failure
    if (flags & 1) {
        operator delete(this, 0x90); // FUN_0043b960 - size matches Entity (144 bytes)
    }
    return this;
}
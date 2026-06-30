// FUNC_NAME: Entity::Entity
void __thiscall Entity::Entity(Entity *this) {
    // Set vtable pointer (first virtual function table)
    this->vtable = (EntityVTable *)&PTR_FUN_00d5f758;
    // Set additional vtable or interface pointers at known offsets
    this->field_0x3C = &PTR_LAB_00d5f748;  // offset 0x3C (15 * 4)
    this->field_0x48 = &PTR_LAB_00d5f744;  // offset 0x48 (18 * 4)
    this->field_0x50 = &PTR_LAB_00d5f740;  // offset 0x50 (20 * 4)
    // If the sub-object pointer at offset 0x68 (0x1a * 4) is non-null, call its destructor/release
    if (this->subObject != nullptr) {
        FUN_004daf90(this->subObject);  // likely a destructor or release function
    }
    // Call some global initialization function (e.g., update manager reference count)
    FUN_00473880();
}
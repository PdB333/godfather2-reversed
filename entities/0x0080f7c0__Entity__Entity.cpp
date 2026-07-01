// FUNC_NAME: Entity::Entity

void __thiscall Entity::Entity(Entity* this)
{
    // Set the primary vtable (offset 0x0)
    *(void**)this = (void*)&PTR_FUN_00d72e2c;

    // Set secondary vtable pointers for multiple inheritance
    this->field_0x3C = &PTR_LAB_00d72e1c;  // +0x0F * 4 = +0x3C
    this->field_0x48 = &PTR_LAB_00d72e18;  // +0x12 * 4 = +0x48
    this->field_0x50 = &PTR_LAB_00d72e14;  // +0x14 * 4 = +0x50

    // Initialize sub-objects at offsets +0xA8 and +0xB0
    FUN_004086d0(&this->subObjAt0xA8);   // sub-object at parameter offset 0x2A
    FUN_00408310(&this->subObjAt0xA8);
    FUN_00408310(&this->subObjAt0xB0);   // sub-object at parameter offset 0x2C

    // General initialization
    FUN_00810050(this);

    // If a child object exists at offset +0x11C, invoke a method on it via vtable at +0x128
    if (this->childObject != nullptr) {
        (*(void (__thiscall**)(void*))((uint8_t*)this->childObject + 0x128))(this->childObject); // call child method at offset 0x4A words
    }

    // Overwrite the vtable at offset +0x50 with a new pointer (likely final vtable)
    this->field_0x50 = &PTR_LAB_00e32854;

    // Global engine initialization
    FUN_0046c640();
}
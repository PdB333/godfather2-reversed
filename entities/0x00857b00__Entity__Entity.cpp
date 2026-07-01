// FUNC_NAME: Entity::Entity
// Function address: 0x00857b00
// Role: Constructor for Entity class, sets vtable and second pointer, then calls base initialization.

void __thiscall Entity::Entity(Entity *this)
{
    // Set vtable pointer at offset 0x00
    this->vtable = (void *)&PTR_LAB_00d751fc;
    // Set second pointer at offset 0x04 (likely class descriptor or base vtable)
    this->field_4 = (void *)&PTR_LAB_00d751e8;
    // Call base class constructor or common initialization routine
    FUN_0055a2a0();
}
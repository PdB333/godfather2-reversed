// FUNC_NAME: Entity::Entity
undefined4 * __thiscall Entity::Entity(Entity *this, undefined4 param_2)
{
    // +0x00: vtable pointer (set twice: first to base vtable, then to derived)
    this->vtable = &PTR_FUN_00d80570;       // +0x00: Base class vtable
    this->field_4 = 0;                      // +0x04: some flag or pointer, initialized to 0

    // Call base class constructor (likely Entity base or Object)
    FUN_0046c590(param_2);                  // Base::Base(param_2)

    // Set derived class virtual table and other member pointers
    this->field_8 = &PTR_LAB_00d8059c;      // +0x08: secondary vtable or interface pointer
    this->vtable = &PTR_FUN_00d80590;       // +0x00: override vtable to derived class
    this->field_0x44 = &PTR_LAB_00d80580;   // +0x44: function pointer or event handler
    this->field_0x50 = &PTR_LAB_00d8057c;   // +0x50: another pointer/offset
    this->field_0x58 = 0;                   // +0x58: integer, initialized to 0
    this->field_0x5c = 5;                   // +0x5c: default type/ID (e.g., entity type 5)

    return this;
}
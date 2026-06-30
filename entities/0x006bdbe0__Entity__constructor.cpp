// FUNC_NAME: Entity::constructor
// Address: 0x006bdbe0
// Role: Base constructor for Entity class with optional initialization of a 0xE0 byte member block
// Notes: Calls base constructor (FUN_006bd9a0, likely EARS::Framework::Object::Object)
// Then if flags bit 0 is set, calls FUN_0043b960 to initialize a block of size 0xE0
// This could be a dynamic allocation or zeroing of a component (e.g., Havok physics or collision mesh)

undefined4 __thiscall Entity::constructor(Entity *this, byte flags) {
    // Call base class constructor (likely EARS::Framework::Object or similar)
    // FUN_006bd9a0 is assumed to be BaseClass::BaseClass()
    BaseClass::constructor();

    // If flag bit 0 is set, initialize extra member block at offset?
    // FUN_0043b960 may perform zeroing or allocation of 0xE0 bytes relative to 'this'
    if ((flags & 1) != 0) {
        initializeMemberBlock(this, 0xe0); // FUN_0043b960(this, 0xe0)
    }

    return (undefined4)this;
}
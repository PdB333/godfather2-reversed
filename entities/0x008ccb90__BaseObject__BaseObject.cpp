// FUNC_NAME: BaseObject::BaseObject
// Address: 0x008ccb90
// Role: Constructor with optional memory allocation (flag bit 0 enables allocator registration)

BaseObject* __thiscall BaseObject::BaseObject(BaseObject* this, byte flags) {
    // Call base class constructor (likely Object or root class)
    FUN_00416bf0();

    // If the low bit of 'flags' is set, register this object with the global allocator
    // The allocator's vtable at offset +4 is called (i.e., second entry) with 'this' and size 0x80
    if ((flags & 1) != 0) {
        // Retrieve global allocator instance (static singleton)
        class Allocator* alloc = (class Allocator*)FUN_009c8f80();
        // Call alloc->registerObject(this, 0x80) or similar method at vtable+4
        (**(code**)(*(int*)alloc + 4))(this, 0x80);
    }

    return this;
}
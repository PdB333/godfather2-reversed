// FUNC_NAME: Entity::Entity
// Function address: 0x008421a0
// Role: Constructor for Entity class (or derived class) with two vtable pointers and optional cleanup.
// Offsets: +0x00: vtable1, +0x04: vtable2, +0x60 (0x180): pointer to sub-object (released if non-null)

undefined4* __thiscall Entity::Entity(undefined4* this, byte flags) {
    undefined4* vtablePtr;

    // If sub-object pointer at offset 0x60 is non-null, release it
    if (this[0x60] != 0) {
        FUN_004daf90(this + 0x60); // likely releaseSubObject or destructor
    }

    // Set vtable pointers for multiple inheritance (two base classes)
    if (this == (undefined4*)0x0) {
        vtablePtr = (undefined4*)0x0;
    } else {
        vtablePtr = this + 4; // second vtable at offset 4
    }
    *vtablePtr = &PTR_LAB_00d74760; // second vtable
    *this = &PTR_LAB_00d74620;      // first vtable

    // If flags bit 0 is set, call cleanup/destructor function
    if ((flags & 1) != 0) {
        FUN_00840230(this); // likely deallocate or final cleanup
    }

    return this;
}
// FUNC_NAME: Entity::Entity
// Function at 0x006A9F80 - Entity constructor (size 0x150)
// Sets multiple vtable pointers, cleans up existing subobject, then optionally deallocates memory.
// param_2: byte flags (bit0 = free memory flag)
undefined4* __thiscall Entity::Entity(byte param_2) {
    // Set vtable pointers for this class and base classes/subobjects
    this->vtable = &Entity_vtable;                     // +0x00
    this->someSubObject1.vtable = &SubObject1_vtable;  // +0x3C
    this->someSubObject2.vtable = &SubObject2_vtable;  // +0x48
    this->someSubObject3.vtable = &SubObject3_vtable;  // +0x50

    // If a subobject at offset +0x50 already exists (non-null pointer), destroy it
    if (this->someSubObject3.somePointer != 0) {
        destroySubObject(&this->someSubObject3); // FUN_004daf90
    }

    // Global initialization (likely engine-wide)
    globalInit(); // FUN_00474090

    // If dynamic allocation flag is set, free this object's memory
    if ((param_2 & 1) != 0) {
        operatorDelete(this, 0x150); // FUN_0043b960
    }

    return this;
}
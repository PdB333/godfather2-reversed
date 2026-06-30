// FUNC_NAME: EARSGameObject::EARSGameObject
// Class: EARSGameObject, constructor with optional deletion
// Address: 0x0047ea00
// Initializes vtable at offset 0, interface vtables at +0x3C and +0x48, and sub-object at +0x50.

EARSGameObject* __thiscall EARSGameObject::EARSGameObject(EARSGameObject* this, byte deleteFlag) {
    // Set main vtable
    this->vtable = (void**)&PTR_FUN_00e3329c;
    // Set additional interface vtables (likely for multiple inheritance)
    *(void**)((uintptr_t)this + 0x3C) = &PTR_LAB_00e332bc;  // +0x3C: interface vtable A
    *(void**)((uintptr_t)this + 0x48) = &PTR_LAB_00e332cc;  // +0x48: interface vtable B
    // Initialize sub-object at offset +0x50
    FUN_004086d0(this + 0x14);  // likely string or container constructor
    FUN_00408310(this + 0x14);  // further initialization
    // Global initialization call
    FUN_0046c640();
    // If deleteFlag bit 0 set, call scalar deleting destructor (with flag 0 = no deallocation)
    if ((deleteFlag & 1) != 0) {
        (*(void(__thiscall**)(EARSGameObject*, int))(**(int**)(DAT_01223410 + 0x2d4))[1])(this, 0);
    }
    return this;
}
// FUNC_NAME: Entity::Entity
// Function address: 0x008018b0
// Purpose: Constructor for Entity base class. Initializes object with optional sub-component creation.
// Fields (offsets from this):
//   +0x00: vtable pointer (first for base, then overwritten with derived)
//   +0x14 (offset 5): pointer to internal list at this+0x28 (field 10)
//   +0x18 (offset 6): some count/flag, initialized to 0
//   +0x24 (offset 9): bool flag, initialized to 1
//   +0x28 (offset 10): vtable pointer for sub-object (PTR_LAB_00d71d1c)
//   +0x30 (offset 0xc): function pointer (LAB_007fa6c0) – likely a callback
//   +0x34 (offset 0xd): another flag/pointer, initialized to 0

Entity* __thiscall Entity::Entity(Entity* this, int createSubObject) {
    undefined4 subObj;
    
    if (createSubObject == 0) {
        subObj = 0;
    }
    else {
        subObj = FUN_00481610(); // Create internal sub-object (e.g., component)
    }
    
    FUN_0064d390(1, 1); // Initialize some global state/settings
    this->vtable = &PTR_LAB_00e317dc; // Set base vtable
    this->field_6 = 0; // offset +0x18
    FUN_00454a10(subObj); // Initialize with sub-object
    this->field_9 = 1; // offset +0x24
    this->vtable = &PTR_LAB_00d71e80; // Override with derived vtable
    this->subObjectVtable = &PTR_LAB_00d71d1c; // offset +0x28 (vtable for sub-object)
    this->callbackFunc = &LAB_007fa6c0; // offset +0x30
    this->field_d = 0; // offset +0x34
    this->internalList = &this->subObjectVtable; // offset +0x14 points to this+0x28
    return this;
}
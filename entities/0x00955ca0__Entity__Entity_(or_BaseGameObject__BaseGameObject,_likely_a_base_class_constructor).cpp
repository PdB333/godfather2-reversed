// FUNC_NAME: Entity::Entity (or BaseGameObject::BaseGameObject, likely a base class constructor)
// Address: 0x00955ca0
// Role: Constructor for an entity/game object with multiple vtable sub-components.
// Structure offsets:
//   +0x00: main vtable pointer (set to PTR_FUN_00d8c088)
//   +0x08: function table pointer (set to PTR_LAB_00d8c080)
//   +0x60: function table pointer (set to PTR_LAB_00d8c070)
// Calls base constructors at 0x004083d0 and 0x00473a60.
// If param_2 (needsRegistration) is set, calls a registration function via an allocator vtable.

typedef void* (__thiscall *AllocatorVtableFunc)(void*, int);

Entity* __thiscall Entity::Entity(Entity* this, byte needsRegistration) {
    int* piVar1;

    // Set the main vtable
    this->vtable = &PTR_FUN_00d8c088;
    // Set secondary function table at offset +0x08
    this->field_0x08 = &PTR_LAB_00d8c080;
    // Set another function table at offset +0x60
    this->field_0x60 = &PTR_LAB_00d8c070;

    // Call base class constructors
    BaseClassA::constructor();      // 0x004083d0
    BaseClassB::constructor();      // 0x00473a60

    // If the object requires registration with an allocator or manager
    if ((needsRegistration & 1) != 0) {
        piVar1 = GetAllocatorVtable();                     // 0x009c8f80
        ((AllocatorVtableFunc)(piVar1[1]))(this, 0x80);    // call function at vtable+4 with size 0x80
    }

    return this;
}
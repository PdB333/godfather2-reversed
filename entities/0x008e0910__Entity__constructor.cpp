// FUNC_NAME: Entity::constructor
// Function address: 0x008e0910
// This is a constructor for the Entity class. It calls a base class constructor (FUN_008ded10)
// with the given parameter, then sets up its vtable pointer and several additional function pointers
// at specific offsets (likely secondary vtables for interface implementations). It also initializes
// a member at offset 0x210 to -1 (likely an invalid handle or sentinel).

void* __thiscall Entity::constructor(Entity* this, int initParam) {
    // Call base class constructor
    FUN_008ded10(initParam);

    // Set vtable pointer at offset 0x0
    this->vtable = (VTable*)&PTR_FUN_00d7fd48;

    // Set secondary vtable pointers (offsets in bytes)
    *(void**)(reinterpret_cast<uint8_t*>(this) + 0x3C) = &PTR_LAB_00d7fd38;  // +0x3C
    *(void**)(reinterpret_cast<uint8_t*>(this) + 0x48) = &PTR_LAB_00d7fd34;  // +0x48
    *(void**)(reinterpret_cast<uint8_t*>(this) + 0x50) = &PTR_LAB_00d7fd30;  // +0x50
    *(void**)(reinterpret_cast<uint8_t*>(this) + 0x54) = &PTR_LAB_00d7fcd0;  // +0x54
    *(void**)(reinterpret_cast<uint8_t*>(this) + 0x58) = &PTR_LAB_00d7fc68;  // +0x58

    // Initialize member at offset 0x210 to -1
    *(int*)(reinterpret_cast<uint8_t*>(this) + 0x210) = -1;

    return this;
}
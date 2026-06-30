// FUNC_NAME: Entity::constructor
// Function address: 0x00767bd0
// Entity constructor that initializes base and derived vtables, and sets up a large sub-structure.

__thiscall Entity* Entity::constructor(Entity* this, byte placementFlag)
{
    // Set base class vtable
    this->vtable = &PTR_LAB_00d6599c;

    // Store a global value into a member of a large sub-object pointed to by this+0x5C
    // subObject + 0x220c = DAT_01205228
    *(undefined4*)(this->subObject + 0x220c) = DAT_01205228;

    // Set derived class vtable
    this->vtable = &PTR_LAB_00d63090;

    // If a child pointer at offset 0x68 is valid, release it
    if (this->childObject != NULL) {
        FUN_004daf90(this->childObject);  // Likely component destructor
    }

    // Perform global initialization (e.g., hook into framework)
    FUN_0080ea60();  // GlobalInit()

    // If placementFlag has bit 0 set, delete this instance (placement new case)
    if (placementFlag & 1) {
        FUN_00624da0(this);  // operator delete or custom deallocator
    }

    return this;
}
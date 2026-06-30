// FUNC_NAME: SomeGameObject::~SomeGameObject
// Address: 0x00739310
// Identifier: Scalar deleting destructor for SomeGameObject.
// Sets vtable to base class (likely EARSObject), destroys member at +0x68, then calls global cleanup,
// and optionally calls operator delete() if the deleting flag's lower bit is set.

void __thiscall SomeGameObject::~SomeGameObject(unsigned char deletingFlag)
{
    // Set vtable pointer to base class vtable (PTR_LAB_00d63090)
    // +0x00: vtable pointer
    this->vtable = &PTR_LAB_00d63090;

    // Destroy member at offset 0x68 (*0x1a = 0x68)
    // +0x68: pointer to allocated sub-object (or resource)
    if (this->field_0x68 != 0) {
        FUN_004daf90(&this->field_0x68); // Probably a destructor or free for that member
    }

    // Global cleanup call (e.g., unregistering from a manager)
    FUN_0080ea60();

    // If the deleting flag has bit 0 set, free the memory of this object
    if ((deletingFlag & 1) != 0) {
        FUN_00624da0(this); // operator delete
    }
}
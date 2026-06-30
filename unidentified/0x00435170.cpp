// FUN_00435170: EARSObject::EARSObject (constructor)
//
// Reconstructed constructor for an EARS engine game object.
// Called from the base class constructor at 0x00435150.
// Sets up polymorphic vtables, calls a sub-object virtual function,
// invokes cleanup/release on a child pointer, and updates a global flag.

void __thiscall EARSObject::EARSObject(EARSObject* this)
{
    // Set primary vtable (class-specific)
    // +0x0: vtable pointer
    this->vtable = &PTR_FUN_00e30c00; // class vtable

    // Set secondary vtable (possibly an interface or base class)
    // +0x8: second vtable pointer
    this->field_0x08 = (void*)&PTR_LAB_00e30c0c;

    // Call a virtual function from the object pointed to at offset +0x0C
    // The object at field_0x0C has its own vtable; we call the method at vtable index 3 (0xC/4)
    // This is typical for initializing a composite or aggregated sub-object.
    if (this->field_0x0C != nullptr)
    {
        // vtable of the sub-object, +0xC is the offset to the virtual method
        (**(code**)(*(int*)this->field_0x0C + 0xC))();
    }

    // Set a flag or counter at offset +0x14 to zero
    this->m_flag1 = 0;

    // Call a release/detach function on a child object at offset +0x10
    // This could be a reference-counted pointer release
    FUN_009c8f10(this->m_childObject);

    // Clear the child pointer
    this->m_childObject = nullptr;

    // Set another flag at offset +0x18 to zero
    this->m_flag2 = 0;

    // Switch the second vtable pointer to a different vtable (perhaps derived class final vtable)
    // +0x8: second vtable pointer now points to the final vtable
    this->field_0x08 = (void*)&PTR_LAB_00e30c10;

    // Clear a global flag (likely a singleton or system state)
    DAT_012233ec = 0;

    // Call a global initialization function (e.g., subsystem setup)
    FUN_0049c640();
}
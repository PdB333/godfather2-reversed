// FUNC_NAME: EARSObject::~EARSObject

// Address: 0x008d2680
// Base destructor for EARSObject. Sets vtable to EARSObject's vtable and deletes two dynamically allocated member pointers.
// Called by derived class destructors to perform base destruction.

void __thiscall EARSObject::~EARSObject(EARSObject* this)
{
    // Set vtable to EARSObject's vtable (prevents virtual calls during destruction)
    this->vtable = (void**)&PTR_FUN_00d7d3d8;

    // Delete smart/variable pointer at offset +0x3C (index 0xf)
    if (this->m_pPointer3C != 0) {
        Memory::deallocate(this->m_pPointer3C);  // FUN_009c8f10 – custom deallocation
    }

    // Delete smart/variable pointer at offset +0x28 (index 0xa)
    if (this->m_pPointer28 != 0) {
        Memory::deallocate(this->m_pPointer28);  // FUN_009c8f10
    }

    return;
}
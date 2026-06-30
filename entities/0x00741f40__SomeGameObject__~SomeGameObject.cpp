// FUNC_NAME: SomeGameObject::~SomeGameObject

void __fastcall SomeGameObject::~SomeGameObject(SomeGameObject* this) // ghidra: FUN_00741f40
{
    // Set vtable to base class (likely just before destruction)
    *(int*)this = &PTR_LAB_00d63b48; // base vtable

    if (this->m_pChild != nullptr) // offset +0x50
    {
        // Release child object three times? Possibly decrement reference count
        Release(); // FUN_007f6420
        Release(); // FUN_007f6420
        Release(); // FUN_007f6420

        // Call virtual function at +0x290 on child object (likely a cleanup method)
        (this->m_pChild->vtable->cleanup)(1); // +0x290, argument 1

        // Clear bit 0 in child's flags at offset +0x4a4
        this->m_pChild->flags &= ~0x1; // offset +0x4a4

        // Some finalization call
        Finalize(); // FUN_007ffa80

        // QueryInterface-style check with GUID-like constant
        char result = (this->m_pChild->vtable->queryInterface)(0x369ac561, &stackVar);

        if (result != 0 && this != nullptr && (this->m_flags & 0x2) != 0) // bit 1 of m_flags at +0x60
        {
            // Destroy child-specific resources
            DestroyChildResources(); // FUN_007f9690

            // Release with a specific code 0x4b
            Release(0x4b); // FUN_007f6420 with param 0x4b

            // Clear bit 1 of m_flags
            this->m_flags &= ~0x2;
        }
    }

    // Call base destructor or final memory cleanup
    BaseDestructor(); // FUN_004ac1e0
    return;
}
// FUNC_NAME: SomeClass::~SomeClass
// Address: 0x00875890
// Role: Destructor for a class that holds a reference-counted pointer at offset 0x4.
// Sets vtable to base class pointer after releasing the referenced object.

void __thiscall SomeClass::~SomeClass(void)
{
    // Check if the reference pointer at +0x4 is non-null
    if (this->m_pRefCounted != 0) {
        // Release the referenced object (likely decrement refcount or delete)
        releaseRefCounted(this->m_pRefCounted);
    }
    // Set vtable pointer to base class's vtable (prevents double deletion)
    this->m_vtable = &PTR_LAB_00e2f0c0;
    return;
}
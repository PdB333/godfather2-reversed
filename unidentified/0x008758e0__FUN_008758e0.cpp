// FUNC_NAME: SomeClass::~SomeClass
// address: 0x008758e0
// Destructor for an object with a vtable and an optional owned resource at +0x4.
// Releases the resource if non-null, then resets vtable to a base sentinel.
void __fastcall SomeClass::destructor(SomeClass* this)
{
    // Check if the resource pointer at offset 0x4 is non-null
    if (this->m_pResource != 0) {
        // Release the resource (likely a sub-object or managed allocation)
        FUN_004daf90(&this->m_pResource); // passes address of m_pResource to deallocator
    }
    // Set vtable pointer to a known base vtable (likely for middle destructor chain)
    this->vtable = (VTablePtr)&PTR_LAB_00e2f0c0;
}
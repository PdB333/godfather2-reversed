// FUNC_NAME: SomeClass::~SomeClass
void __fastcall SomeClass::~SomeClass()
{
    // Set vtable pointer to the class's destructor vtable (offset +0x0)
    *reinterpret_cast<void**>(this) = &PTR_LAB_00d63090;

    // Check if the sub-object at offset +0x68 (0x1a * 4) exists
    if (this->m_pointer != nullptr)
    {
        #if 0
        // Destroy the sub-object (likely a managed resource) // +0x68
        FUN_004daf90(&this->m_pointer);
        #else
        subObjectDestructor(&this->m_pointer);
        #endif
    }

    // Perform global cleanup (e.g., unregister from manager)
    someGlobalCleanup();
}
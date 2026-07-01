// FUNC_NAME: RefCounted::~RefCounted
void __fastcall RefCounted::~RefCounted(RefCounted* this)
{
    // Offset +0x20 (param_1[8]) – pointer to a reference-counted child object
    if (this->m_pChild != nullptr)
    {
        int* refCount = &this->m_pChild->m_refCount;
        (*refCount)--;
        if (*refCount == 0)
        {
            // Call virtual destructor of the child via vtable (vtable at offset 0, destructor at offset 4)
            void (*destructor)(void*) = **(void (***)(void*))this->m_pChild + 4;
            destructor(this->m_pChild);
        }
        this->m_pChild = nullptr;
    }
    // Restore base vtable pointer to static value (PTR_LAB_00e3729c)
    this->vtable = &g_vtableBase;  // PTR_LAB_00e3729c is the base vtable
}
// FUNC_NAME: CResourceHandle::~CResourceHandle
void __thiscall CResourceHandle::~CResourceHandle() {
    // Check if the resource pointer at offset +0x4 is non-null
    if (this->m_pResource != nullptr) {
        // Free the resource and null out the pointer (FUN_004daf90)
        FUN_004daf90(&this->m_pResource);
    }
    // Set vtable pointer (offset +0x0) to a static sentinel table
    this->m_vtable = &g_DeletedVTable;
}
// FUNC_NAME: ComponentBase::~ComponentBase
void __fastcall ComponentBase::~ComponentBase(ComponentBase* this) {
    // Check and delete m_pChild1 at offset +0x18 using destructor function pointer at +0x24
    if (this->m_pChild1 != nullptr) {
        (this->m_destroyChild1)(this->m_pChild1);
    }
    // Check and delete m_pChild2 at offset +0x8 using destructor function pointer at +0x14
    if (this->m_pChild2 != nullptr) {
        (this->m_destroyChild2)(this->m_pChild2);
    }
    // Reset vtable to base class (prevents virtual calls after destruction)
    this->m_vtable = &g_BaseVTable;
}
// FUNC_NAME: CoreObject::AttachDelegate
void __thiscall CoreObject::AttachDelegate(int* pDelegate)
{
    // Store delegate pointer at offset 0x34 (m_pDelegate)
    this->m_pDelegate = pDelegate;

    // Call virtual method at vtable[1] (likely onAttached or initialize)
    (this->vtable[1])(this);

    // If either flag at +0x28 (m_bFlag1) or +0x2c (m_bFlag2) is set, perform cleanup
    if (this->m_bFlag1 != 0 || this->m_bFlag2 != 0) {
        CleanupPrevious(0, 0);
    }
}
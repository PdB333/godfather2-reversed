// FUNC_NAME: SmartHandle::destroy
void __fastcall SmartHandle::destroy() {
    // Reset fields to zero and release referenced object
    m_refCount = 0;          // +0x04
    FUN_009c8f10(m_ptr);     // release the object pointed to by m_ptr
    m_ptr = nullptr;         // +0x00
    m_handleId = 0;          // +0x08
}
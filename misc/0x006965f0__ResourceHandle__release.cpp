// FUNC_NAME: ResourceHandle::release
void __fastcall ResourceHandle::release() {
    // Temporary buffer (likely GUID or reference key)
    char buffer[8];
    // Call internal detach/copy helper with buffer, this, object dereference, this, object pointer
    FUN_006961f0(buffer, this, **(int**)m_pObject, this, m_pObject);
    // Release the resource object
    FUN_009c8eb0(m_pObject);
    // Clear pointers and counters
    m_pObject = nullptr;
    m_refCountOrIndex = 0;
}
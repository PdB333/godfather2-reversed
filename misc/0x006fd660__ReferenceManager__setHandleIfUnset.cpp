// FUNC_NAME: ReferenceManager::setHandleIfUnset
void __thiscall ReferenceManager::setHandleIfUnset(uint32 newHandle) {
    if (m_handle == -1) {                                    // +0x208: handle/id, -1 = uninitialized
        m_handle = newHandle;                                // +0x208: set the handle
        FUN_005e6620(&LAB_006fd640);                         // initialize with hardcoded data (string or callback)
        m_flags = 0;                                         // +0x210: clear flags/counter
    }
}
// FUNC_NAME: MemoryManager::initObject
void __thiscall MemoryManager::initObject(void) {
    // +0x04: vtable
    // +0x08: m_pMemoryHint
    undefined4 localBuf[3]; // stack fallback

    void* hint = this->m_pMemoryHint; // offset +0x08
    if (hint == nullptr) {
        localBuf[0] = 0;
        localBuf[1] = 0;
        localBuf[2] = 0;
        hint = localBuf;
    }

    // Call vtable[0] which acts like a placement new: returns the given hint pointer
    // with the object of size 0x28 constructed there.
    undefined4* obj = ((undefined4*(__fastcall*)(int, void*))this->m_pVtable[0])(0x28, hint);

    if (obj != nullptr) {
        obj[0] = 0; // +0x00
        obj[1] = 0; // +0x04
        obj[2] = 0; // +0x08
    }

    // These checks are always true in practice; they are kept for fidelity.
    if (obj + 1 != nullptr) {
        obj[1] = 0;
    }
    if (obj + 2 != nullptr) {
        obj[2] = 0;
    }

    // +0x24 (byte) = 1  -> active flag or state
    ((uint8_t*)obj)[0x24] = 1;
    // +0x25 (byte) = 0
    ((uint8_t*)obj)[0x25] = 0;
}
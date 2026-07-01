// FUNC_NAME: BaseHandle::constructor
BaseHandle* __thiscall BaseHandle::constructor(BaseHandle* this, IUnknown* pObject, int handle) {
    this->m_pObject = pObject; // +0x00
    if (pObject) {
        pObject->AddRef(); // vtable+0x08
    }
    if (handle != 0) {
        this->m_handle = FUN_004265d0(handle, this->m_pObject); // +0x04
    } else {
        this->m_handle = 0; // +0x04
    }
    return this;
}
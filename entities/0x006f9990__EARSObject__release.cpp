// FUNC_NAME: EARSObject::release

int* EARSObject::release(byte flags) {
    // Release owned sub-object if present (offset +0x10)
    if (this->m_subObject != 0) {
        this->releaseSubObject(this->m_subObject);
    }
    // Call release function on the interface pointer (offset +0x00)
    if (this->m_pInterface != 0) {
        ((void (__cdecl *)(void*))(this->m_releaseFunc))(this->m_pInterface);
    }
    // If the low bit of flags is set, deallocate this object
    if ((flags & 1) != 0) {
        this->freeObject(this);
    }
    return this;
}
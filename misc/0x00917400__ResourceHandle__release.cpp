//FUNC_NAME: ResourceHandle::release
void __fastcall ResourceHandle::release(ResourceHandle *this)
{
    // +0x04: reference count
    this->m_nRefCount = 0;
    // Release the underlying resource (e.g., decrement refcount or free)
    FUN_009c8f10(this->m_pResource);
    // +0x00: resource pointer
    this->m_pResource = nullptr;
    // +0x08: flags or other state
    this->m_nFlags = 0;
}
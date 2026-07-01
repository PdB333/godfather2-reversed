// FUNC_NAME: ResourceHandle::reset
void __thiscall ResourceHandle::reset(void)
{
    this->m_refCount = 0;
    releaseResource(this->m_pResource);
    this->m_pResource = 0;
    this->m_flags = 0;
    return;
}
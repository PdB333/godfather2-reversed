// FUNC_NAME: EARS::SharedString::operator=
void __thiscall EARS::SharedString::operator=(EARS::SharedString* this, const EARS::SharedString& other)
{
    // Layout:
    // +0x00: m_releaseFunc - pointer to buffer release function (can be NULL)
    // +0x04: m_pData       - pointer to actual string data or embedded buffer
    // +0x18: m_pBuffer     - pointer to shared reference-counted buffer
    // +0x1C: m_flags       - state flags (values 0=null, 3=inline, 4=static, other=shared)

    // If we currently hold a shared buffer (non-null release function) and we are not in a
    // special state (null, inline, static), release our reference before overwriting.
    if ((this->m_releaseFunc != NULL) && (this->m_flags != 4) && (this->m_flags != 0) && (this->m_flags != 3))
    {
        this->m_releaseFunc(this->m_pBuffer, 4, this->m_pData);
    }

    // Avoid self-assignment; then shallow-copy the first two fields (release function and data pointer)
    if (this != &other)
    {
        this->m_releaseFunc = other.m_releaseFunc;
        this->m_pData       = other.m_pData;
    }
}
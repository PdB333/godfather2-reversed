// FUNC_NAME: NetPacket::release
void NetPacket::release(void)
{
    // cleanup internal data (e.g., free buffer)
    internal_cleanup(this->m_pData, this->m_nSize);

    // if still in use, unregister from global manager and mark as destroyed
    if (this->m_nRefCount != 0) {
        // call second vtable function on global manager (registered callback)
        (*(void (__thiscall **)(void*, void*))(*(uint32_t*)DAT_01205868 + 4))(this->m_pData, this->m_pCallback);
        this->m_pData = nullptr;
        this->m_bDestroyed = 1;
    }
}
// FUNC_NAME: StreamManager::shutdownStreamSystem
void StreamManager::shutdownStreamSystem()
{
    // Temporary buffer for stream shutdown notification (path/name?)
    char shutdownBuffer[12];

    // Notify the stream about to be shutdown (call with internal pointers)
    notifyStreamShutdown(shutdownBuffer, this, *(void**)*(int*)(this->m_pStream), this, this->m_pStream);

    // Release the stream object via vtable (method offset 4) with type 0x18
    (this->vtable->releaseStream)(this->m_pStream, 0x18);
    this->m_pStream = 0;               // +0x1c
    this->m_streamSize = 0;            // +0x20

    // If secondary resource exists, release it via m_pInterface
    if (this->m_pSecondaryResource != 0) {
        // Release via m_pInterface vtable (method offset 4) with flag 0
        (this->m_pInterface->vtable->releaseResource)(this->m_pSecondaryResource, 0);
        this->m_pSecondaryResource = 0; // +0x18
    }
    // Finalize the interface (method offset 0xc)
    (this->m_pInterface->vtable->finalize)();

    // Global stream system cleanup
    cleanupGlobalStreamData();
}
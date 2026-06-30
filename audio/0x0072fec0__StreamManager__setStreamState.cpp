// FUNC_NAME: StreamManager::setStreamState
// Function address: 0x0072fec0
// Role: Controls streaming state for loading/unloading assets based on a boolean flag.
// Fields:
// +0x1f3c m_isLoading (int) - flag indicating loading is in progress
// +0x203c m_streamState (StreamState) - sub-object handling stream operations
// +0x2040 m_streamHandle (void*) - pointer to active stream resource

void __thiscall StreamManager::setStreamState(bool enable)
{
    if (enable == false)
    {
        // Attempt to start streaming if not already loading and a stream handle exists
        if (this->m_isLoading == 0 && this->m_streamHandle != nullptr)
        {
            startStream(&this->m_streamState, this, 0); // 0 may indicate normal priority
        }
    }
    else
    {
        // Stop streaming if a stream handle is present
        if (this->m_streamHandle != nullptr)
        {
            stopStream(&this->m_streamState, this);
            return; // Early exit after stop
        }
    }
}
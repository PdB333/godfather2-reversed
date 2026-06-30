// FUNC_NAME: StreamManager::~StreamManager
void StreamManager::~StreamManager(void)
{
    // Set VTable to destructor-specific VTable
    this->m_vtablePtr = &PTR_FUN_00e3f6a4;

    // Release stream manager sub-objects
    if (this->m_pStreamAllocator != nullptr)
    {
        // Call release function via VTable at offset +0x0C
        (**(code **)(*(int *)this->m_pStreamAllocator + 0x0C))(this->m_pStreamAllocator);
    }

    if (this->m_pStreamBuffer1 != nullptr)
    {
        FUN_009c8f10(this->m_pStreamBuffer1); // Deallocate or release
    }

    if (this->m_pStreamBuffer2 != nullptr)
    {
        FUN_009c8f10(this->m_pStreamBuffer2);
    }

    if (this->m_pStreamBuffer3 != nullptr)
    {
        FUN_009c8f10(this->m_pStreamBuffer3);
    }

    // Mark global initialization flag as false
    g_streamManagerInitialized = 0;

    // Set VTable to post-destruction state (likely null or safe pointer)
    this->m_vtablePtr = &PTR_LAB_00e3f6a8;
}
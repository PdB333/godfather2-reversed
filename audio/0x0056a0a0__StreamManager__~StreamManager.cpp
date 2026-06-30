// FUNC_NAME: StreamManager::~StreamManager

void __thiscall StreamManager::~StreamManager(StreamManager *this)
{
    // +0x00 vtable pointer
    // +0x334 (0xcd * 4) m_hThread (HANDLE)
    // +0x33c (0xcf * 4) m_workerData (void*)
    // +0x338 (0xce * 4) m_workerRunning (int)

    // Set vtable to base class during destruction to avoid virtual calls
    this->vtable = (void **)&PTR_FUN_00e3ab30;

    if (this->m_hThread != (HANDLE)0x0)
    {
        CloseHandle(this->m_hThread);
        this->m_hThread = (HANDLE)0x0;

        // Release worker thread data (likely allocated memory or additional handles)
        releaseWorkerData(this->m_workerData);
        this->m_workerData = (void *)0x0;
        this->m_workerRunning = 0;
    }

    // Call base class destructor (likely from EARS::Framework::Object or similar)
    BaseStreamManager::destroy();  // Replace with actual base destructor call if known
}
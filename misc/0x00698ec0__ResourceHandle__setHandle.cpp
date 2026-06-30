// FUNC_NAME: ResourceHandle::setHandle
int* ResourceHandle::setHandle(int newHandle)
{
    if (newHandle == 0) {
        // Release existing handle if non-zero via stored release function at +0x0C
        if (m_handle != 0) {
            m_releaseFunc(m_handle);
        }
        m_handle = 0;
        m_field2 = 0; // +0x04
        m_field3 = 0; // +0x08
        return this;
    }
    if (newHandle != m_handle) {
        // Acquire reference to new handle (FUN_004dbef0)
        int refCountResult = acquireResource(newHandle);
        // Setup new handle (FUN_004dbb10) with parameters (newHandle, 0, refCountResult)
        setupNewHandle(newHandle, 0, refCountResult);
    }
    return this;
}
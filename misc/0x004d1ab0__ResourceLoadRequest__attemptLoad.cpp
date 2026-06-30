// FUNC_NAME: ResourceLoadRequest::attemptLoad
void __thiscall ResourceLoadRequest::attemptLoad(void)
{
    int handle;
    
    handle = allocateLoadHandle();  // FUN_004d0510
    if (handle != 0) {
        // Store the allocated handle at offset 0xC8 (200)
        m_handle = handle;
        // Set load state to 3 (loading) at offset 0xB0 (176)
        m_state = 3;
        // Start async resource load: parameters from this+0xB8, handle+4, this+0xC0
        // flags = 0x20000, callback = loadComplete, userData = this
        Engine::requestResourceLoad(*(uint32_t*)(this + 0xB8),  // param1
                                    *(uint32_t*)(handle + 4),   // param2 from handle
                                    *(uint32_t*)(this + 0xC0),  // param3
                                    0, 0x20000, 0,              // flags, priority, grouping
                                    &loadComplete,              // FUN_004d19a0
                                    this, 0);                  // userData, extra
        return;
    }
    // No handle available -> set state to 2 (error/not ready)
    m_state = 2;
}
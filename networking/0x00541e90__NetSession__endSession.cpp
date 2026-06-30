// FUNC_NAME: NetSession::endSession
void __thiscall NetSession::endSession(NetSession *this, int sessionId) {
    int dataObj;
    
    // Check if the session has a pending termination flag (bit 0 at +0x12c)
    if ((this->flags & 1) != 0) {
        // Possibly a debug or early disconnect handler
        FUN_00541bb0(0);
    }
    
    // Confirm that the provided session ID matches the stored one
    if (sessionId == this->m_sessionId) {
        // Call virtual method at vtable offset 8 (index 2) – likely 'shutdown' or 'release'
        (this->vtable[2])(0);
        
        dataObj = this->m_pData;
        if (*(int *)(dataObj + 0x10) != 0) {
            // Cleanup the inner object and its sub‑structures
            FUN_009f1b20(dataObj);
            FUN_009f1ad0(dataObj + 8);
            FUN_009f01a0();
        }
        // Clear the inner object's reference
        *(int *)(dataObj + 0x10) = 0;
        // Additional cleanup, possibly flushing or deallocation
        FUN_009f01a0();
        // Clear the session ID
        this->m_sessionId = 0;
    }
}
// FUNC_NAME: StreamManager::updateStreamState
void __fastcall StreamManager::updateStreamState(StreamManager* thisPtr) {
    char isReady;
    int currentStreamId;

    // Release the stored stream resource (decrement refcount or close)
    FUN_008c74d0(thisPtr->m_pStream);  // m_pStream at +0x40

    // Check current state: 0=inactive, 1=active, other=error
    if (thisPtr->m_state != 0) {
        if (thisPtr->m_state != 1) {
            return;  // invalid state, bail out
        }
        // State is 1: verify we are the active stream manager instance
        currentStreamId = FUN_0084a410();  // get current active stream ID
        if (currentStreamId != 0) {
            currentStreamId = FUN_0084a410();  // re-acquire (double check)
            if (currentStreamId == thisPtr->m_pStream) {
                isReady = FUN_0084a670();  // check stream readiness flag
                if (isReady != '\0') {
                    // Dereference the buffer pointer and start stream playback
                    FUN_008c2f80(*thisPtr->m_pBufferPtr);  // m_pBufferPtr at +0xc0
                }
            }
        }
    }
    // Perform standard update processing
    FUN_008c3ec0(thisPtr);
}
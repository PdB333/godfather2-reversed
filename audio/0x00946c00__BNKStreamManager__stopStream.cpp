// FUNC_NAME: BNKStreamManager::stopStream
// Address: 0x00946c00
// Stops a bank stream by ID. Returns 1 if stream was active and stopped, 0 if not found.
// Uses member at +0x148 (pointer to active stream instance) and global g_bShuttingDown.

int __thiscall BNKStreamManager::stopStream(int streamId) {
    char isActive = this->isStreamActive(streamId); // FUN_009467b0
    if (isActive != 0) {
        if (*(int*)(this + 0x148) != 0) { // +0x148: m_pActiveStream
            this->releaseStream(*(int*)(this + 0x148)); // FUN_0094b0e0
            bool bShuttingDown = g_bShuttingDown == 0; // DAT_01130638
            *(int*)(this + 0x148) = 0; // Clear active stream pointer
            if (bShuttingDown) {
                this->updateStreamManager(); // FUN_004a8f30
                this->checkPendingOperations(); // FUN_009473d0
            }
        }
        return 1;
    }
    return 0;
}
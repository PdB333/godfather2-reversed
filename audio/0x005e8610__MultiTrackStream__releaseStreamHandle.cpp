// FUNC_NAME: MultiTrackStream::releaseStreamHandle
bool __thiscall MultiTrackStream::releaseStreamHandle(void) {
    char cVar;
    // this+0x1c8: stream handle (audio/dsp handle), -1 means inactive
    int streamHandle = *(int*)(this + 0x1c8);
    if (streamHandle >= 0) {
        // DAT_01223510 points to a global singleton (e.g. AudioDataManager or BNKStreamManager)
        // vtable offset 0x54: release/stop function
        cVar = (*(code**)(*DAT_01223510 + 0x54))(streamHandle);
        if (cVar != 0) {
            *(int*)(this + 0x1c8) = -1; // mark handle as released
            // this+0x1c0: pointer to allocated stream data buffer
            if (*(int*)(this + 0x1c0) != 0) {
                // DAT_01223518+4: another singleton (likely memory manager)
                if (*(int*)(DAT_01223518 + 4) != 0) {
                    // vtable offset 4: release/free function
                    (*(code**)(**(int**)(DAT_01223518 + 4) + 4))(*(int*)(this + 0x1c0), 0);
                }
                // this+0x1c0: buffer pointer, this+0x1c4: buffer size
                *(int*)(this + 0x1c0) = 0;
                *(int*)(this + 0x1c4) = 0;
                return true;
            }
        }
    }
    return false;
}
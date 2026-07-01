// FUN_NAME: AudioStreamManager::updateStream
// Address: 0x008f4650
// Role: Handles audio stream state machine – initial load (if no active stream) or ongoing stream update
void __thiscall AudioStreamManager::updateStream() {
    int streamState = *(int *)(this + 0x18); // +0x18: current stream handle/state pointer (0 means idle)
    if (streamState == 0) {
        // First-time setup: compute timeout from data at +0x20a0+4, multiply by 1000
        *(unsigned long long *)(this + 0x20) = 
            (unsigned long long)*(unsigned int *)(*(int *)(this + 0x20a0) + 4) * 1000;
        // Load stream data: parameters from +0x20a8, *(this+0x20a0)+0xc, +0x20ac
        loadStreamData(*(undefined4 *)(this + 0x20a8),
                       *(undefined4 *)(*(int *)(this + 0x20a0) + 0xc),
                       *(undefined4 *)(this + 0x20ac));
        commonUpdate();          // shared housekeeping
        setStateFlag(2);         // set some state flag (arg=2)
        *(unsigned int *)(this + 0x10) &= 0xFFFFBFFF; // clear bit 14 (0x4000) in flags
        return;
    }
    // Stream already active – continue processing
    commonUpdate();
    resetStream(0);              // argument 0
    processStreamState(streamState); // pass the stream handle
    *(unsigned int *)(this + 0x10) &= 0xFFFFBFFF; // clear same bit
}
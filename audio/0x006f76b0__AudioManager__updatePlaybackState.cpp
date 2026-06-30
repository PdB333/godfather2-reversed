// FUNC_NAME: AudioManager::updatePlaybackState

void __thiscall AudioManager::updatePlaybackState(void)
{
    // +0x2c: playback state (0=idle, 1=playing, 2=finishing, 3=cancelling)
    // +0x28: handle to primary resource (e.g., sound or animation)
    // +0x24: handle to secondary resource (e.g., fade or crossfade)
    int state = *(int *)(this + 0x2c);
    
    if (state == 1) {
        // Playing state: check if we have a valid primary handle and release it
        if (*(int *)(this + 0x28) != 0xFF) {
            releasePrimaryHandle(*(int *)(this + 0x28));
            *(int *)(this + 0x28) = 0xFF; // mark as invalid
        }
        // Schedule a callback to finish the playback after a delay
        scheduleCompletionCallback(&LAB_006f7670, this);
        // Perform cleanup/notify listeners
        finishPlayback(this);
        // Reset state to idle
        *(int *)(this + 0x2c) = 0;
    }
    else if ((unsigned int)(state - 2) < 2) {
        // Finishing or cancelling (states 2 or 3): release secondary handle
        releaseSecondaryHandle(*(int *)(this + 0x24));
        // Reset state to idle
        *(int *)(this + 0x2c) = 0;
    }
    return;
}
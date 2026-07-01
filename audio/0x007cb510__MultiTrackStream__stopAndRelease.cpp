// FUNC_NAME: MultiTrackStream::stopAndRelease
void __thiscall MultiTrackStream::stopAndRelease(int this, int fadeOutTimeMs)
{
    // Deactivate sound system? Possibly a global debugging flag.
    soundSystemReset(0);
    g_bStreamStopped = 1;

    // Retrieve sound manager from global table indexed by this->managerIndex (+0x58)
    int managerTableEntry = *(int*)((int)&g_SoundManagerTable + *(int*)(this + 0x58));
    int streamHandle = *(int*)(this + 0x1b0); // +0x1B0: handle/pointer to stream object

    // Issue stop command with flags: (manager, handle, stopNow=0, fadeOut=1, fadeTime, immediate=0)
    soundControl(managerTableEntry, streamHandle, 0, 1, fadeOutTimeMs, 0);

    if (streamHandle != 0) {
        // Call release method on the stream object (COM-like vtable call)
        (*(void (__stdcall *)(int))(*(int*)streamHandle))(1);
    }

    // Clear the handle
    *(int*)(this + 0x1b0) = 0;
}
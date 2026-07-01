// FUNC_NAME: ResourceManager::cleanup
void __thiscall ResourceManager::cleanup() {
    /*
     * Function at 0x007f7a50. Likely a cleanup routine called during destruction or shutdown.
     * Checks two resource pointers at +0x3b0 and +0x8a0. If non-null, performs specific release operations.
     * First offset may be an audio stream or handle, second a bank or loadable resource.
     * Called from 0x007fed50 (destructor or shutdown sequence).
     */
    if (*(this + 0x3b0) != 0) { // +0x3b0: pointer to some resource (e.g., stream/object)
        StopAudio(); // FUN_00625030 - stops or releases a global audio system
    }
    if (*(this + 0x8a0) != 0) { // +0x8a0: handle to a separate resource (e.g., bank/channel)
        ReleaseStreamHandle(DAT_01205224, DAT_012067e8, *(this + 0x8a0), 0, 0); // FUN_00624eb0 - releases a resource via a manager singleton
        *(this + 0x8a0) = 0; // clear the pointer
    }
}
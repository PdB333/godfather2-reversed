// FUNC_NAME: UIManager::processFrame

// Function at 0x004c2200: Main frame update for UI manager.
// Handles global state flags, movie playback, and dispatches to virtual method.
// Param_2 (eventData) is passed to the virtual handler or to movie-related functions.

int __thiscall UIManager::processFrame(void* eventData)
{
    // Global state at 0x1223480 has a flag at +0x28
    if (*(char*)(g_globalState + 0x28) != '\0') {
        // Check/acquire something via sync object
        int syncResult = checkSyncState(&g_syncObject);
        if (syncResult != -2) {
            g_globalFlag1 = 2; // set global flag to 2
        }
    }

    // Check byte at this+0x71 (flags field?) bit 0x20
    if ((*(byte*)(this + 0x71) & 0x20) == 0) {
        // Normal path: call virtual function at vtable offset 0x158
        // Pass eventData as argument
        (*(void(__thiscall**)(void*, void*))(*(void**)this + 0x158))(this, eventData);
    } else {
        // Special path: movie/overlay handling
        if (g_moviePlayer != 0) {
            char cVar1 = isMoviePlayerActive(g_moviePlayer);
            if (cVar1 == '\0') {
                g_movieFrameCounter++; // increment frame counter
                resetMoviePlayer(g_moviePlayer, 0x8000);
            }
        }
        if (eventData != 0) {
            char cVar1 = processMovieEvent(eventData);
            if (cVar1 == '\0') {
                shutdownMoviePlayback();
                cleanupEvent(eventData);
            }
        }
    }

    // Post-update global state
    if (*(char*)(g_globalState + 0x28) != '\0') {
        finalizeSyncStage(1);
        g_globalFlag2 = 2; // set another global flag to 2
    }
    return 1;
}
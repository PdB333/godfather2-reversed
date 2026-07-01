// FUNC_NAME: GodfatherGameManager::processMainLoopAction
void GodfatherGameManager::processMainLoopAction(void* this, GodfatherGameManager* pManager)
{
    int currentThreadId;
    int mainLoopThreadId;

    // Check if bit 0 of flags at +0x37c is set (e.g., restartRequested)
    if ((pManager->flags & 1) != 0) {
        // Get current thread ID from global engine instance
        currentThreadId = getCurrentThreadId(*(int*)(DAT_0112980c + 4));
        mainLoopThreadId = getThreadIdByName("GameMainLoop");
        if (currentThreadId == mainLoopThreadId) {
            // We are in the main loop thread, perform the action
            if (*(int*)(DAT_0112980c + 4) != 0) {
                performShutdown(); // FUN_0067c920
                pManager->flags |= 2;   // Set bit 1 (actionInProgress)
                pManager->flags &= ~8;  // Clear bit 3 (some other flag)
                return;
            }
        }
        else {
            // Not in main loop thread, but if another global is set, log error
            if (DAT_01129928 != 0) {
                debugPrint(0x11); // FUN_009316e0(0x11)
            }
        }
        // Always set bit 1 and clear bit 3 when request was pending
        pManager->flags |= 2;
    }
    // Clear bit 3 regardless
    pManager->flags &= ~8;
}
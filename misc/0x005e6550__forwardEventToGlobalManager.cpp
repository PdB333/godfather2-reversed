// FUNC_NAME: forwardEventToGlobalManager
void forwardEventToGlobalManager(void* pUnused, uint eventId) {
    // Forward event to global manager (DAT_012234bc) via FUN_005e49d0
    g_pEventManager->processEvent(eventId); // Assume g_pEventManager is the global from DAT_012234bc
}
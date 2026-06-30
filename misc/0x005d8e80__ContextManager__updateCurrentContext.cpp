// FUNC_NAME: ContextManager::updateCurrentContext
void ContextManager::updateCurrentContext(int newContextId) {
    // Check if updates are not ignored or the current context ID is different from new one
    if ((g_ignoreUpdates != 0) || (g_currentContextId != newContextId)) {
        g_currentContextId = newContextId;

        // If the context slot at the current index is non-zero, process it
        int slotIndex = g_currentContextIndex;
        if (*(int *)((char *)g_contextArray + slotIndex * 0xc) != 0) {
            processContext(); // FUN_006063b0
        }
    }
}
// FUNC_NAME: registerCallbackWithLock
void registerCallbackWithLock(int param_1) {
    // Lock a global critical section (likely for thread safety)
    EnterCriticalSection(&g_someCriticalSection); // FUN_004d3bc0

    // Retrieve a callback pair from a global manager instance
    CallbackPair pair = g_someManager->getCallback(param_1); // FUN_005dc3d0

    // If a valid function pointer exists, call it with its associated context
    if (pair.func) {
        pair.func(pair.context);
    }
}
// FUNC_NAME: Manager::processEvent
void __cdecl Manager::processEvent(int eventId) {
    // Initialize some global string/resource (FUN_004d3bc0)
    someInitFunction(&g_strGlobal); // DAT_00e3f4f4 -> g_strGlobal
    
    // Call manager processing function with global manager instance and event ID
    someManagerProcess(g_pManagerInstance, eventId); // DAT_01223508 -> g_pManagerInstance, FUN_005dc3d0 -> someManagerProcess
    
    // The following block is based on decompiled local variables local_10 and local_4.
    // In the decompiled output, local_10 and local_4 are uninitialized.
    // This may be a decompilation artifact; possibly they are return values or parameters not captured.
    int callbackParam;       // local_10
    void (*callback)(int);   // local_4
    
    if (callbackParam != 0) {
        callback(callbackParam);
    }
}
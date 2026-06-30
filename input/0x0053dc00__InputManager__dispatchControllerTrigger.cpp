// FUNC_NAME: InputManager::dispatchControllerTrigger
void __fastcall InputManager::dispatchControllerTrigger(void* pUnused, int triggerLeftValue, int triggerRightValue) {
    // g_controllerManager: global manager instance at 0x0121be9c
    // g_currentControllerIndex: current active controller slot index (0-15) at 0x0121bf30
    // g_triggerHandlerLeft: array of 0x1B-byte structures for left trigger handlers
    // g_triggerHandlerRight: array of 0x1B-byte structures for right trigger handlers
    // Each entry is a non-null callback object to invoke.
    if (*(uint32_t*)((uint8_t*)&DAT_01198ea8 + g_currentControllerIndex * 0x1B) != 0) {
        FUN_0060add0(DAT_0121be9c, 
                     *(uint32_t*)((uint8_t*)&DAT_01198ea8 + g_currentControllerIndex * 0x1B), 
                     triggerLeftValue);
    }
    if (*(uint32_t*)((uint8_t*)&DAT_01198eac + g_currentControllerIndex * 0x1B) != 0) {
        FUN_0060add0(DAT_0121be9c, 
                     *(uint32_t*)((uint8_t*)&DAT_01198eac + g_currentControllerIndex * 0x1B), 
                     triggerRightValue);
    }
}
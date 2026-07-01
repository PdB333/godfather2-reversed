// FUNC_NAME: PresentationManager::registerDebugTextDisplay
// Function address: 0x008b6290
// Registers text rendering callbacks for debug output (callback at 0x008b5f80 and 0x008b5bf0)
void PresentationManager::registerDebugTextDisplay() {
    int *pManager = (int *)FUN_00ad8d40();  // Gets PresentationManager singleton (or similar)
    if (pManager != nullptr) {
        char buffer[480];  // local_200, stack buffer
        FUN_00ae9750(buffer, PTR_s_text_plain_00ef45a8);  // Init buffer with format "text_plain"

        int *pRenderInterface = (int *)(**(code **)(*pManager + 0x2c))();  // Get render interface (vtable offset 0x2c)
        int *pDevice = (int *)(**(code **)(*pRenderInterface + 0x20))();   // Get device/context (vtable offset 0x20)
        (**(code **)(*pDevice + 0x1c))(&PTR_DAT_00ef4cd0, &LAB_008b5f80); // Register first callback

        int *pTimeManager = (int *)(**(code **)(*pManager + 0x2c))();      // Get time manager (reusing same offset)
        int *pTimer = (int *)(**(code **)(*pTimeManager))();               // Get timer object (vtable offset 0x00)
        (**(code **)(*pTimer + 0x10))(&uStack_264, FUN_008b5bf0, uStack_20, 10000); // Register second callback, 10 sec interval

        FUN_00ae97f0();  // Cleanup or pop stack
    }
}
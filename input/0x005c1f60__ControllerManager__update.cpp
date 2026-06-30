// FUNC_NAME: ControllerManager::update
void ControllerManager::update(ControllerManager* thisPtr) {
    // Global initialization flag for controller system
    if (g_controllerManagerInitialized == 0) {
        // Allocate 200 bytes for controller state data
        void* alloc = allocateMemory(200, 0);
        if (alloc == nullptr) {
            g_controllerManagerInitialized = 0;
        } else {
            // Get singleton controller manager instance
            g_controllerManagerInitialized = getControllerManager();
        }
        // Perform additional initialization (e.g., XInput startup)
        initControllerManager();
    }

    // Call virtual function at vtable+4 on the object pointed to by thisPtr->m_pSubsystem (+0x10)
    // This is likely an "update" or "process" method on a subsystem
    int result = (*(int (__thiscall**)(void))(*(int*)((char*)thisPtr + 0x10) + 4))();
    // Process the result (e.g., handle input events)
    processInputResult(result);
}
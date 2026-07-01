// FUNC_NAME: ControllerManager::updateControllerState
void __thiscall ControllerManager::updateControllerState(ControllerManager *this) {
    int controllerSlotPtr;

    // Check if the global input device manager is initialized
    if (g_inputDeviceManager != nullptr) {
        // If there's a pending action in this slot (offset 0x36c), clear it
        if (*(int *)((uintptr_t)this + 0x36c) != 0) {
            FUN_00454310(0); // SetResultToNull
        }
        // If global input device manager still valid, activate device 1
        if (g_inputDeviceManager != nullptr) {
            (*(void (__thiscall **)(InputDeviceManager *, int))(*g_inputDeviceManager))(g_inputDeviceManager, 1); // InputDeviceManager::activateDevice(1)
        }
    }

    // Allocate 8 bytes for a new controller slot structure
    controllerSlotPtr = FUN_009c8e50(8);
    if (controllerSlotPtr != 0) {
        // Get a pointer to the new slot (from some manager)
        controllerSlotPtr = FUN_008b2370();
        if (controllerSlotPtr != 0) {
            // Set the result to point into the allocated slot (offset +4)
            FUN_00454310(controllerSlotPtr + 4);
            return;
        }
    }
    // Failure case: set result to null
    FUN_00454310(0);
    return;
}
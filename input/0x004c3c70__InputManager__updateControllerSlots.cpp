// FUNC_NAME: InputManager::updateControllerSlots
void InputManager::updateControllerSlots(int param_1) {
    // Global input manager singleton pointer (e.g., g_pInputManager = DAT_012233b4)
    // Offset 0x4ec is an array of 16 pointers to controller objects (XInput slots)
    // Each controller object has a vtable; index 6 (0x18/4) is a virtual update/receive function
    // The call passes (4, param_1) — 4 likely indicates input processing reason/code

    InputManager* pManager = reinterpret_cast<InputManager*>(DAT_012233b4);
    if (!pManager) return;

    // 16 controller slots (XInput maximum)
    for (int slotIdx = 0; slotIdx < 16; ++slotIdx) {
        ControllerSlot* pController = pManager->controllerSlots[slotIdx]; // +0x4EC + slot*4
        if (!pController) continue;

        // Call virtual function at vtable offset 6: void __thiscall ControllerSlot::processInput(int reason, int param)
        // reason = 4 (e.g., kReasonTick or kReasonRead)
        pController->vtable->func_processInput(4, param_1);
    }
}
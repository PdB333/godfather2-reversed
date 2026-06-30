// FUN_0046ed10: InputManager::processControllerInput
void InputManager::processControllerInput() {
    // +0x130: pointer to input device (e.g., XInput device)
    if (m_pInputDevice != nullptr) {
        uint32_t uStack_10 = 0;
        // vtable indices: 0x134 = 308, 0x13c = 316
        (this->*vtable[0x134])();
        (this->*vtable[0x13c])();
        // +0x88: bitmask of currently pressed buttons/axes
        uStack_10 = m_inputMask;
        uint32_t uStack_c = ~uStack_10;
        uint8_t uStack_8 = 0;
        // Call on input device: send state with type hash 0x20e5862
        // 0x20e5862 likely represents "ControllerState"
        m_pInputDevice->sendState(0x20e5862, &uStack_10);
        // +0x161: flag indicating if controller is disconnected
        if (m_bControllerDisconnected == '\0') {
            m_pInputDevice->resetState();
            m_pInputDevice->flushEvents();
            (this->*vtable[300])(); // 0x12c
            return;
        }
        // vtable index 0x130 = 304
        (this->*vtable[0x130])();
    }
}
// FUNC_NAME: InputManager::refreshInputModes
// Address: 0x00732130
// Updates active input modes based on a control flag (offset +0x1f54) and the current input device.

void InputManager::refreshInputModes() {
    // Always activate base input mode (0)
    setInputMode(0);

    // If bit 0 of the control flag at offset +0x1f54 is set, activate input mode 1
    if (*(byte*)(this + 0x1f54) & 1) {
        setInputMode(1);
    }

    // Query the current input device ID (0/1/2/3)
    int currentDevice = getCurrentInputDevice();

    if (currentDevice == 2) {
        setInputMode(2);
    } else if (currentDevice == 3) {
        setInputMode(3);
    }
    // For devices 0 or 1, only modes 0 (and possibly 1) are activated.
}
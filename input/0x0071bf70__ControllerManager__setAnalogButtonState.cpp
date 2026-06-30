// FUNC_NAME: ControllerManager::setAnalogButtonState

void __thiscall ControllerManager::setAnalogButtonState(float analogValue, uint32 buttonId)
{
    // Uses global threshold for analog input activation (e.g., trigger/stick deadzone)
    if (g_analogThreshold < analogValue) {
        // Set bit 2 (0x4) to indicate button is active
        *(uint16 *)(this + 0x3c) |= 4;
    } else {
        // Clear bit 2 when below threshold
        *(uint16 *)(this + 0x3c) &= 0xfffb;
    }
    // Store button or slot identifier at offset +0x2c
    *(uint32 *)(this + 0x2c) = buttonId;
    return;
}
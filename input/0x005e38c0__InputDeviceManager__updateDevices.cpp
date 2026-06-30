// FUNC_NAME: InputDeviceManager::updateDevices
bool __fastcall InputDeviceManager::updateDevices(uint currentTime, DeviceContext* context)
{
    // Compute delta time in seconds from previous timestamp
    int rawDelta = currentTime - context->previousTime; // context->previousTime at offset +8
    float deltaSeconds = (float)rawDelta;
    if (rawDelta < 0) {
        // Handle 32-bit timestamp wrap-around (2^32)
        deltaSeconds += 4294967296.0f; // DAT_00e44578
    }
    deltaSeconds *= 0.001f; // Convert milliseconds to seconds (DAT_00e2e210)
    if (deltaSeconds < 0.0f) {
        deltaSeconds = 0.0f - deltaSeconds; // Absolute value (DAT_00e44564 is 0.0)
    }

    // Store current time as previous for next frame
    context->previousTime = currentTime; // offset +8

    // Update keyboard/mouse device
    bool mouseKeyboardUpdated = s_pMouseKeyboardDevice->update(deltaSeconds); // FUN_005dc9b0
    // Update gamepad device
    bool gamepadUpdated = s_pGamepadDevice->update(deltaSeconds); // FUN_005e4700

    // Check if input processing is active (e.g., window in focus)
    if (s_pInputManager->bActive) { // offset +0x1744 from s_pInputManager (DAT_0122350c)
        // Process up to 5 buffered input events
        for (int i = 0; i < 5; ++i) {
            processOneInputEvent(); // FUN_005e86e0
        }
        return (mouseKeyboardUpdated && gamepadUpdated);
    }
    return false;
}
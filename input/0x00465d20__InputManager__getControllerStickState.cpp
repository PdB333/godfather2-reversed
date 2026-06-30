// FUNC_NAME: InputManager::getControllerStickState
void InputManager::getControllerStickState(uint slotIndex, int stickType, float* outX, float* outY)
{
    // Global pointer to array of controller state structures (each 0x44 bytes)
    ControllerState* controllerArray = (ControllerState*)DAT_012233b4;

    // Check if slot is valid (function likely checks platform-specific connection)
    if (!isControllerSlotValid(slotIndex))
    {
        *outX = 0.0f;
        *outY = 0.0f;
        return;
    }

    slotIndex &= 0xFF; // Ensure byte-sized index
    if (slotIndex >= 16) // Only 16 controller slots supported
        return;

    // Access the specific controller structure
    ControllerState* controller = &controllerArray[slotIndex];

    // +0x6a: connection flag (non-zero means connected)
    if (controller->connected == 0)
        return;

    switch (stickType)
    {
    case 0: // Left stick (thumbstick)
        // +0x2c: left X, +0x30: left Y
        *outX = controller->leftStickX;
        *outY = controller->leftStickY;
        break;

    case 1: // Right stick
        // +0x34: right X, +0x38: right Y
        *outX = controller->rightStickX;
        *outY = controller->rightStickY;
        break;

    default:
        break;
    }
}
// Function address: 0x00410280
// Role: Check if a specific button state is active on a controller slot.
// This is a method of the input manager, handling XInput-like controller state arrays.
// The class contains an array of 16 controller structures at offset +0x2c, each 0x44 bytes.
// Each struct has:
//   +0x10: currentButtons (ushort) – buttons currently held down
//   +0x12: previousButtons (ushort) – buttons held down last frame (edge detection)
//   +0x14: releaseDisableMask (ushort) – mask of buttons that are blocked from reporting
//   +0x6a: isConnected (byte) – non-zero if controller is present
// The function returns true if the specified button state matches the given check type.

bool __thiscall InputManager::CheckButtonState(byte controllerIndex, ushort buttonMask, byte checkType)
{
    // controllerIndex must be in range [0, 15] and not equal to 0x12 (18, reserved sentinel)
    if (controllerIndex == 0x12 || controllerIndex >= 16)
        return false;

    // Pointer to the controller structure for this index
    ControllerState* ctrl = &this->controllers[controllerIndex]; // +0x2c base, each 0x44

    // The controller must be connected (non-zero flag at +0x6a)
    if (!ctrl->isConnected)
        return false;

    // Remove any buttons from the mask that are blocked by the releaseDisableMask
    buttonMask = buttonMask & ~ctrl->releaseDisableMask; // +0x14

    // Evaluate the button state based on checkType
    bool result = false;
    switch (checkType)
    {
    case 0: // Not pressed (any of the masked buttons is not held)
        result = (buttonMask & ~ctrl->currentButtons) != 0; // +0x10
        break;
    case 1: // Is pressed (any of the masked buttons is held)
        result = (ctrl->currentButtons & buttonMask) != 0; // +0x10
        break;
    case 2: // Was just pressed this frame (current != previous)
        result = ((~ctrl->previousButtons) & ctrl->currentButtons & buttonMask) != 0; // +0x12, +0x10
        break;
    case 3: // Was just released this frame (previous != current)
        result = ((~ctrl->currentButtons) & ctrl->previousButtons & buttonMask) != 0; // +0x10, +0x12
        break;
    }
    return result;
}
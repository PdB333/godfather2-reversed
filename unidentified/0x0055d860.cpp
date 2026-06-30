// FUN_0055d860: InputDeviceManager::getControllerStatePtr
int __thiscall InputDeviceManager::getControllerStatePtr(int this, char controllerIndex)
{
    // Returns pointer to the controller state at this->controllerStatesArray[controllerIndex] (offset +0x150)
    // Each controller state is 8 bytes (likely two 4-byte fields, e.g., buttons and axes)
    // controllerIndex is a char (0-255) but typically 0-15 for XInput controllers
    return this + 0x150 + controllerIndex * 8;
}
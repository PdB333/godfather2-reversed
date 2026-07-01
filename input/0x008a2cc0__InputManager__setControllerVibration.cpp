// FUNC_NAME: InputManager::setControllerVibration
void InputManager::setControllerVibration(uint32_t controllerIndex, uint32_t vibrationData)
{
    int *pDevice;
    
    pDevice = (int *)InputManager::getDeviceManager();
    if (pDevice != (int *)0x0) {
        pDevice = (int *)(**(code **)(*pDevice + 0x30))(); // Get controller device at index
        if (pDevice != (int *)0x0) {
            (**(code **)(*pDevice + 0x30))(controllerIndex, vibrationData); // Set vibration on device
        }
    }
    return;
}
// FUNC_NAME: InputDeviceManager::updateControllerState
void InputDeviceManager::updateControllerState(void)
{
    // Check if controller input is not yet enabled
    if (s_controllerEnabled != 1) {
        // Call virtual method at vtable offset 0x198 (enableController with arg1=0, arg2=1)
        (*(void (__thiscall **)(InputDeviceManager*, int, int))(*(int*)gInputDeviceManager + 0x198))
            (gInputDeviceManager, 0, 1);
        s_controllerEnabled = 1;
    }
    // Check if vibration is currently enabled
    if (s_controllerVibrationEnabled != 0) {
        // Call virtual method at vtable offset 0x190 (disableVibration with four zero args)
        (*(void (__thiscall **)(InputDeviceManager*, int, int, int, int))(*(int*)gInputDeviceManager + 0x190))
            (gInputDeviceManager, 0, 0, 0, 0);
        s_controllerVibrationEnabled = 0;
    }
}
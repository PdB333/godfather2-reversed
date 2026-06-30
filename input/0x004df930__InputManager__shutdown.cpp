//FUNC_NAME: InputManager::shutdown

void InputManager::shutdown(void)
{
    InputManager* manager = g_inputManager; // DAT_012054c0 - global singleton pointer
    int result = manager->releaseDevices(); // FUN_004e1900 - release input devices
    if (result >= 0) {
        manager->cleanup(); // FUN_004e18a0 - additional cleanup
    }
    // Check if reference count or flag at offset +0x04 is zero
    if (manager->field_4 == 0) {
        manager->field_4 = 0; // redundant assignment
        delete manager->field_0; // FUN_009c8f10 - free pointer at +0x00
        manager->field_0 = 0;
        manager->field_8 = 0; // clear field at +0x08
    }
}
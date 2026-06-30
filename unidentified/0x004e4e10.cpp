// FUN_004e4e10: InputSystem::setControllerConnected
void InputSystem::setControllerConnected(uint controllerIndex, char disconnectedFlag)
{
    // g_controllerConnected is a global array of 17 bytes at 0x01194738
    // Indices 0-16 correspond to controller slots (16 XInput controllers + keyboard?)
    if (controllerIndex < 0x11)
    {
        g_controllerConnected[controllerIndex] = (disconnectedFlag == '\0'); // true if not disconnected
    }
}
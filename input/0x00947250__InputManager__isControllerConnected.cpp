// FUNC_NAME: InputManager::isControllerConnected
uint InputManager::isControllerConnected(void)
{
    int* pInputManager; // pointer to InputManager singleton
    uint result; // return value: 0 or controller mask
    
    pInputManager = (int *)InputManager::getSingleton(); // FUN_00946cc0
    if (pInputManager != (int *)0x0) {
        // vtable+0x10 is likely isControllerConnected(uint controllerId, bool* outConnected)
        // Using controller index 0 and a mask value 0xd7e44d6a as a flag check
        result = 0xd7e44d6a;
        uint local_4 = 0; // local bool for connection status
        char isConnected = (**(code **)(*pInputManager + 0x10))(0xd7e44d6a, &local_4);
        // Return controller mask if connected, else 0
        return -(uint)(isConnected != '\0') & result;
    }
    return 0;
}
// FUNC_NAME: InputDeviceManager::clearButtonFlags
// Address: 0x005e2c60
// Role: Clears specified button flags from the active controller state, if the input system is active.
//       Returns 1 on success, 0 if inactive or no controller state available.

int InputDeviceManager::clearButtonFlags(uint buttonMask)
{
    // Check if input system is active (global singleton flag at +0x1744)
    if (*(char*)(g_pInputManager + 0x1744) != '\0')
    {
        // Get the active controller state pointer (FUN_005e2150)
        void* pControllerState = getActiveControllerState();
        if (pControllerState != nullptr)
        {
            // Clear requested bits from the button mask at offset 0x250
            *(uint*)(pControllerState + 0x250) &= ~buttonMask;
            return 1;
        }
    }
    return 0;
}
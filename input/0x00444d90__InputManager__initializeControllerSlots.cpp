// FUNC_NAME: InputManager::initializeControllerSlots
// Address: 0x00444d90
// Role: Initializes all 16 controller slots (0x10) by calling initControllerSlot() for each.
// The number 16 matches the XInput controller slot count (0x44 bytes per slot).

void InputManager::initializeControllerSlots()
{
    for (uint32_t slotIndex = 0; slotIndex < 16; ++slotIndex)
    {
        initControllerSlot(); // FUN_00444db0 - individual slot initialization
    }
}
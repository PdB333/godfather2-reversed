// FUNC_NAME: ControllerManager::initializeSlots
void __fastcall ControllerManager::initializeSlots(ControllerManager *this)
{
    uint clearIndex;

    // Call base class initializer (likely InputDeviceManager or similar)
    FUN_004e3d40(this);

    // If no active controller slots configured, use default initializer
    if (g_activeSlotCount == 0) {
        FUN_004e1c40();
    } else {
        // Initialize the specific slot entry at offset g_controllerSlots[g_activeSlotCount * 0xC0]
        FUN_004e22a0(g_controllerSlots + g_activeSlotCount * 0xC0);
    }

    // Clear 20 entries (0xA0 bytes / 8 bytes each) of a pad buffer
    clearIndex = 0;
    do {
        *(uint32_t *)((int)g_padStates + clearIndex) = 0;
        clearIndex += 8;
    } while (clearIndex < 0xA0);
}
// FUNC_NAME: ControllerManager::dispatchActiveControllerEvent
void __fastcall ControllerManager::dispatchActiveControllerEvent(uint param_1, uint eventData)
{
    // +0x38: size of each controller slot structure
    // array base: g_controllerSlots (0x11253f4)
    // index: g_activeControllerIndex (0x1125388)
    int slotIndex = g_activeControllerIndex; // 0x1125388
    ControllerSlot* slot = (ControllerSlot*)&g_controllerSlots; // 0x11253f4
    // Each slot structure's first member is a pointer to the device object
    if (slot[slotIndex].devicePtr != 0) {
        processControllerSlotEvent(g_controllerManager, &slot[slotIndex], eventData); // FUN_0060b020
    }
}
// FUNC_NAME: InputManager::activateControllerSlot
// Address: 0x004107d0
// Role: Marks a controller slot as active (index in EAX), initializes it, dispatches a default event, and calls an activation callback.

void __thiscall InputManager::activateControllerSlot(uint slotIndex, void* pContext)
{
    // Ensure slot index is within max 16 controllers
    if (slotIndex < 16)
    {
        // Mark the first byte of the controller slot structure as active (offset 0x6a + index*0x44)
        m_controllerSlots[slotIndex].active = 1;

        // Initialize the controller slot (likely zeroes/resets state)
        initControllerSlot(slotIndex);

        // Prepare an event by copying a global default event and setting a zero flag
        ControllerEvent evt = g_defaultControllerEvent;   // DAT_012069fc
        evt.unknownFlag = 0;
        uint unusedSlotIndex = slotIndex;                  // Possibly used in event

        // Dispatch the event (e.g., to trigger UI updates)
        g_eventDispatcher.dispatch(&evt, 0);
    }

    // If an activation callback is registered, call it with the user context
    if (m_onControllerActivated != nullptr)
    {
        m_onControllerActivated(pContext, 1, pContext, 0);
    }
}